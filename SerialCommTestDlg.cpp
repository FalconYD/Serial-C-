
// SerialCommTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "SerialCommTest.h"
#include "SerialCommTestDlg.h"
#include "afxdialogex.h"


BOOL bSwitching = FALSE;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSerialCommTestDlg ��ȭ ����


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


// CSerialCommTestDlg �޽��� ó����

BOOL CSerialCommTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	bWorking = FALSE;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSerialCommTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSerialCommTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSerialCommTestDlg::OnBnClickedBtnOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		m_Comm->Receive(data, (int)length);                    // length ���� ��ŭ �����͸� ����
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	bWorking = TRUE;
	AfxBeginThread(CommTestThread, this);
}


void CSerialCommTestDlg::OnBnClickedBtnClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItem(IDC_EDIT_RCV_VIEW)->SetWindowText(_T(""));
}


void CSerialCommTestDlg::OnBnClickedBtnStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	bWorking = FALSE;
}
