
// SerialCommTestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SerialCommTest.h"
#include "SerialCommTestDlg.h"
#include "afxdialogex.h"


BOOL bSwitching = FALSE;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSerialCommTestDlg 대화 상자


CSerialCommTestDlg::CSerialCommTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERIALCOMMTEST_DIALOG, pParent)
	, m_strRecvData(_T(""))
	, m_strLight(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialCommTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STC_RECVDATA, m_strRecvData);
	DDX_Text(pDX, IDC_EDIT_LIGHT, m_strLight);
	DDX_Control(pDX, IDC_EDIT_RCV_VIEW, m_edit_rcv_view);
}

BEGIN_MESSAGE_MAP(CSerialCommTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CSerialCommTestDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CSerialCommTestDlg::OnBnClickedBtnClose)
	ON_MESSAGE(WM_MYCLOSE, OnThreadClosed)
	ON_MESSAGE(WM_MYRECEIVE, OnReceive)
	ON_BN_CLICKED(IDC_BTN_TEST, &CSerialCommTestDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_RUN, &CSerialCommTestDlg::OnBnClickedBtnRun)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CSerialCommTestDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_STOP, &CSerialCommTestDlg::OnBnClickedBtnStop)
END_MESSAGE_MAP()


// CSerialCommTestDlg 메시지 처리기

BOOL CSerialCommTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	bWorking = FALSE;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSerialCommTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSerialCommTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSerialCommTestDlg::OnBnClickedBtnOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("COM1");
	//m_Comm = new SerialComm(_T("\\\\.\\" + str), _T("9600"), _T("None"), _T("8 Bit"), _T("1 Bit"));
	if(m_Comm->Create(GetSafeHwnd()) != 0)
	{
		TRACE("Opened!\r\n");
		m_Comm->Clear();
	}
	else
	{
		TRACE("OpenFail\r\n");
	}
}


void CSerialCommTestDlg::OnBnClickedBtnClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_Comm)
	{
		m_Comm->Close();
		m_Comm = NULL;
		bWorking = FALSE;
		Sleep(500);
		TRACE("Closed!\r\n");
	}
}

LRESULT CSerialCommTestDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	bWorking = FALSE;
	((SerialComm*)lpara)->HandleClose();
	delete ((SerialComm*)lpara);
	
	return 0;
}

LRESULT CSerialCommTestDlg::OnReceive(WPARAM length, LPARAM lpara)
{
	CString str;
	char data[20000];
	if (m_Comm)
	{
		m_Comm->Receive(data, (int)length);                    // length 길이 만큼 데이터를 얻음
		data[length] = '\0';
		for (int i = 0; i < (int)length; i++)
		{
			str += data[i];
		}
		m_edit_rcv_view.ReplaceSel(str);
		m_edit_rcv_view.LineScroll(m_edit_rcv_view.GetLineCount());
		//m_RcvData.ReplaceSel(str);
		//TRACE("%s\r\n",str);
		m_strRecvData = str;
		str = "";
		//str = "";
	}
	UpdateData(FALSE);

	return 0;
}

UINT CommTestThread(LPVOID lpData)
{
	UINT32 i = 0;
	CString str = _T("D1");
	int iLight = 0;
	CSerialCommTestDlg* Comm = (CSerialCommTestDlg*)lpData;
	CString strinfo = _T("R1DAT\r\n");
	while (Comm->bWorking)
	{
		if (iLight > 255)
			iLight = 255;
		if (iLight < 0)
			iLight = 0;

		if (iLight >= 255)
			bSwitching = TRUE;
		if (iLight <= 0)
			bSwitching = FALSE;

		str.Format(_T("D1%.3d\r\n"),iLight);
		
// 		Comm->m_Comm->Send(str, str.GetLength());
// 		Comm->m_Comm->Send(strinfo, strinfo.GetLength());
		if (bSwitching)
			iLight--;
		else
			iLight++;
		for (i = 0; i < UINT32_MAX/1024; i++) { }
	}
	TRACE("Thread End \r\n");
	return 0;
}

void CSerialCommTestDlg::OnBnClickedBtnTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_Comm != nullptr)
	{
		UpdateData();
		CString str = _T("D1");
		str += m_strLight;
		str += "\r\n";
		//m_Comm->Send(str, str.GetLength());
		m_strLight = "";
		UpdateData(FALSE);
	}
}


void CSerialCommTestDlg::OnBnClickedBtnRun()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	bWorking = TRUE;
	AfxBeginThread(CommTestThread, this);
}


void CSerialCommTestDlg::OnBnClickedBtnClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_EDIT_RCV_VIEW)->SetWindowText(_T(""));
}


void CSerialCommTestDlg::OnBnClickedBtnStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	bWorking = FALSE;
}
