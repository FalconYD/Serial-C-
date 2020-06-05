// SerialLightDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "SerialCommTest.h"
#include "SerialLightDlg.h"
#include "afxdialogex.h"


// SerialLightDlg 대화 상자
CCriticalSection g_critical;
IMPLEMENT_DYNAMIC(SerialLightDlg, CDialogEx)

SerialLightDlg::SerialLightDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_LIGHT, pParent)
	, m_bAllTrans(FALSE)
	, m_bAttachCR(FALSE)
	, m_bAttachLF(FALSE)
{

}

SerialLightDlg::~SerialLightDlg()
{
}

void SerialLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHK_ALL, m_bAllTrans);
}


BEGIN_MESSAGE_MAP(SerialLightDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BN_OPEN, &SerialLightDlg::OnBnClickedBnOpen)
	ON_BN_CLICKED(IDC_CHK_ALL, &SerialLightDlg::OnBnClickedChkAll)
	ON_BN_CLICKED(IDC_BN_CLOSE, &SerialLightDlg::OnBnClickedBnClose)
	ON_BN_CLICKED(IDC_BN_SEND, &SerialLightDlg::OnBnClickedBnSend)
	ON_MESSAGE(WM_MYCLOSE, OnThreadClosed)
	ON_MESSAGE(WM_MYRECEIVE, OnReceive)
	ON_CBN_DROPDOWN(IDC_CB_PORT, &SerialLightDlg::OnCbnDropdownCbPort)
	ON_BN_CLICKED(IDC_BN_CMDRELOAD, &SerialLightDlg::OnBnClickedBnCmdreload)
	ON_BN_CLICKED(IDC_BN_WIRTE_CMD, &SerialLightDlg::OnBnClickedBnWirteCmd)
	ON_BN_CLICKED(IDC_BN_DEL_CMD, &SerialLightDlg::OnBnClickedBnDelCmd)
	ON_LBN_SELCHANGE(IDC_LIST_CMD, &SerialLightDlg::OnLbnSelchangeListCmd)
	ON_BN_CLICKED(IDC_BN_CMD_SET, &SerialLightDlg::OnBnClickedBnCmdSet)
	ON_BN_CLICKED(IDC_BN_ADD_QUEUE, &SerialLightDlg::OnBnClickedBnAddQueue)
	ON_BN_CLICKED(IDC_BN_DEL_QUEUE, &SerialLightDlg::OnBnClickedBnDelQueue)
	ON_BN_CLICKED(IDC_BN_SEND_QUEUE, &SerialLightDlg::OnBnClickedBnSendQueue)
END_MESSAGE_MAP()


// SerialLightDlg 메시지 처리기


BOOL SerialLightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_fn_Init();
	m_fn_getSerialPort();
	
	int nCbCount = 0;
	nCbCount = ((CComboBox*)GetDlgItem(IDC_CB_PORT))->GetCount();
	if (nCbCount == 0)
	{
		((CComboBox*)GetDlgItem(IDC_CB_PORT))->ResetContent();
		CString strCom;
		for (int nStep = 1; nStep < 10; nStep++)
		{
			strCom.Format(_T("COM%d"),nStep);
			((CComboBox*)GetDlgItem(IDC_CB_PORT))->AddString(strCom);
		}
	}
	((CComboBox*)GetDlgItem(IDC_CB_PORT))->SetCurSel(0);

	m_fn_LoadINI();

	m_fn_EnableButton(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void SerialLightDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


BOOL SerialLightDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetDlgItem(IDC_EDIT_INPUT) == GetFocus())
		{
			OnBnClickedBnSend();
		}
		return FALSE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE)
		return FALSE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return FALSE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

void SerialLightDlg::m_fn_Init()
{
	ZeroMemory(m_strCmdList, sizeof(m_strCmdList[0][0]) * MAX_LIST_ITEM * MAX_LIST_ITEM);
	CString strComport;
	for (int nStep = 1; nStep < MAX_PORT_COUNT; nStep++)
	{
		strComport.Format(_T("COM%d"),nStep);
		((CComboBox*)GetDlgItem(IDC_CB_PORT))->AddString(strComport);
	}
	((CComboBox*)GetDlgItem(IDC_CB_PORT))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("600"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("1200"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("2400"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("4800"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("9600"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("14400"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("19200"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("28800"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("33600"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("38400"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("56000"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("57600"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("115200"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("128000"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->AddString(_T("256000"));
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_CB_PARITY))->AddString(_T("None"));
	((CComboBox*)GetDlgItem(IDC_CB_PARITY))->AddString(_T("Even"));
	((CComboBox*)GetDlgItem(IDC_CB_PARITY))->AddString(_T("Odd"));
	((CComboBox*)GetDlgItem(IDC_CB_PARITY))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_CB_DATABIT))->AddString(_T("7 Bit"));
	((CComboBox*)GetDlgItem(IDC_CB_DATABIT))->AddString(_T("8 Bit"));
	((CComboBox*)GetDlgItem(IDC_CB_DATABIT))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_CB_STOPBIT))->AddString(_T("1 Bit"));
	((CComboBox*)GetDlgItem(IDC_CB_STOPBIT))->AddString(_T("1.5 Bit"));
	((CComboBox*)GetDlgItem(IDC_CB_STOPBIT))->AddString(_T("2 Bit"));
	((CComboBox*)GetDlgItem(IDC_CB_STOPBIT))->SetCurSel(0);

	SetDlgItemInt(IDC_EDIT_SLEEP, 10);
}

void SerialLightDlg::OnBnClickedBnOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_fn_SerialOpen();
	if(m_nSockCount > 0)
		m_fn_EnableButton(1);
}

void SerialLightDlg::m_fn_SerialOpen()
{
	CString strcom, strbaud, strparity, strdatabit, strstopbit;
	((CComboBox*)GetDlgItem(IDC_CB_PORT))->GetLBText(((CComboBox*)GetDlgItem(IDC_CB_PORT))->GetCurSel(), strcom);
	((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->GetLBText(((CComboBox*)GetDlgItem(IDC_CB_BAUDRATE))->GetCurSel(), strbaud);
	((CComboBox*)GetDlgItem(IDC_CB_PARITY))->GetLBText(((CComboBox*)GetDlgItem(IDC_CB_PARITY))->GetCurSel(), strparity);
	((CComboBox*)GetDlgItem(IDC_CB_DATABIT))->GetLBText(((CComboBox*)GetDlgItem(IDC_CB_DATABIT))->GetCurSel(), strdatabit);
	((CComboBox*)GetDlgItem(IDC_CB_STOPBIT))->GetLBText(((CComboBox*)GetDlgItem(IDC_CB_STOPBIT))->GetCurSel(), strstopbit);
	
	//SerialComm Comm;
	//m_pComm = new SerialComm();
	//Comm.SetParameter(_T("\\\\.\\" + strcom), strbaud, strparity, strdatabit, strstopbit);
	if (m_nSockCount < MAX_PORT_COUNT)
	{
		m_Comm[m_nSockCount].SetParameter(_T("\\\\.\\" + strcom), strbaud, strparity, strdatabit, strstopbit);
		if (m_Comm[m_nSockCount].Create(GetSafeHwnd()) != 0)
		{
			TRACE("Opened!\r\n");
			m_Comm[m_nSockCount].Clear();
			m_nSockCount++;
			//Comm.Clear();
			//m_listComm.push_back(Comm);

			m_fn_UpdateCOMList();
			((CListBox*)GetDlgItem(IDC_LIST_CONNECT))->SetCurSel(m_nSockCount-1);
		}
		else
		{
			TRACE("OpenFail\r\n");
		}
	}
}

void SerialLightDlg::m_fn_UpdateCOMList()
{
	//if (m_listComm.size() > 0)
	if(m_nSockCount > 0)
	{
		//std::list<SerialComm>::iterator it;
		((CListBox*)GetDlgItem(IDC_LIST_CONNECT))->ResetContent();
// 		for (it = m_listComm.begin(); it != m_listComm.end(); it++)
// 		{
// 			SerialComm serial = *it;
// 			((CListBox*)GetDlgItem(IDC_LIST_CONNECT))->AddString(serial.m_sComPort);
// 		}
		for (int nStep = 0; nStep < m_nSockCount; nStep++)
		{
			((CListBox*)GetDlgItem(IDC_LIST_CONNECT))->AddString(m_Comm[nStep].m_sComPort);
		}
	}
}

void SerialLightDlg::OnBnClickedChkAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bAllTrans ^= true;
}

void SerialLightDlg::OnBnClickedBnClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strCom;
	((CListBox*)GetDlgItem(IDC_LIST_CONNECT))->GetText(((CListBox*)GetDlgItem(IDC_LIST_CONNECT))->GetCurSel(), strCom);
	for (int nStep = 0; nStep < m_nSockCount; nStep++)
	{
		if (m_Comm[nStep].m_sComPort == strCom)
		{
			m_Comm[nStep].Close();
			m_Comm[nStep].HandleClose();
			
			TRACE("Closed!\r\n");
			for (int nStepT = nStep; nStepT < m_nSockCount; nStepT++)
			{
				memcpy(&m_Comm[nStepT], &m_Comm[nStepT + 1], sizeof(SerialComm));
			}
			m_fn_UpdateCOMList();
			m_nSockCount--;
			break;
		}
	}
	if (m_nSockCount <= 0)
	{
		m_fn_EnableButton(0);
	}
// 	std::list<SerialComm>::iterator it;
// 	for (it = m_listComm.begin(); it != m_listComm.end(); it++)
// 	{
// 		if (it->m_sComPort == strCom)
// 		{
// 			it->Close();
// 			m_listComm.erase(it);
// 			TRACE("Closed!\r\n");
// 			m_fn_UpdateCOMList();
// 			break;
// 		}
// 	}
}

void SerialLightDlg::OnBnClickedBnSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strMsg;
	
	((CEdit*)GetDlgItem(IDC_EDIT_INPUT))->GetWindowText(strMsg);
// 	std::list<SerialComm>::iterator it;
// 	for (it = m_listComm.begin(); it != m_listComm.end(); it++)
// 	{
// 		if (it->m_sComPort == strCom)
// 		{
// 			it->Send(strMsg, strMsg.GetLength());
// 			TRACE("Send!\r\n");
// 			break;
// 		}
// 	}
	m_fn_Send(strMsg, m_bAllTrans);
}

void SerialLightDlg::m_fn_Send(CString strMsg, bool bAllSend)
{
	CString strCom;
	CString str, Temp;
	int nListSel = ((CListBox*)GetDlgItem(IDC_LIST_CONNECT))->GetCurSel();
	char chBuffer[MAXBUF] = { 0, };
	m_bAttachCR = ((CButton*)GetDlgItem(IDC_CHK_CR))->GetCheck();
	m_bAttachLF = ((CButton*)GetDlgItem(IDC_CHK_LF))->GetCheck();
	if (m_bAttachCR)
		strMsg += '\r';
	if (m_bAttachLF)
		strMsg += '\n';

	_in_fn_Uni2Multi(strMsg.GetBuffer(), chBuffer);
	if (nListSel >= 0)
	{
		((CListBox*)GetDlgItem(IDC_LIST_CONNECT))->GetText(nListSel, strCom);
		
		for (int nStep = 0; nStep < m_nSockCount; nStep++)
		{
			if (bAllSend)
			{
				m_Comm[nStep].Send(chBuffer, strMsg.GetLength());
				Temp.Format(_T("[%s][Send] %s ["), m_Comm[nStep].m_sComPort, strMsg);
				str = Temp;

				for (int nStepT = 0; nStepT < strMsg.GetLength(); nStepT++)
				{
					Temp.Format(_T("%02x "), chBuffer[nStepT]);
					str += Temp;
				}
				str += "]";
				m_fn_WriteLog(str);
			}
			else
			{
				if (m_Comm[nStep].m_sComPort == strCom)
				{
					m_Comm[nStep].Send(chBuffer, strMsg.GetLength());
					Temp.Format(_T("[%s][Send] %s ["), m_Comm[nStep].m_sComPort, strMsg);
					str = Temp;

					for (int nStepT = 0; nStepT < strMsg.GetLength(); nStepT++)
					{
						Temp.Format(_T("%02x "), chBuffer[nStepT]);
						str += Temp;
					}
					str += "]";
					m_fn_WriteLog(str);
					TRACE("Send!\r\n");
					break;
				}
			}
		}
	}
	else
	{
		AfxMessageBox(_T("포트를 선택해 주세요."));
	}
}

LRESULT SerialLightDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{


	return 0;
}

LRESULT SerialLightDlg::OnReceive(WPARAM length, LPARAM lpara)
{
	CString str, temp;
	char data[MAXBUF] = { 0, };
	wchar_t wchData[MAXBUF] = { 0, };
	SerialComm* serialTemp = (SerialComm*)lpara;
	for (int nStep = 0; nStep < 10; nStep++)
	{
		if (m_Comm[nStep].m_sComPort == serialTemp->m_sComPort)
		{
			str.Format(_T("[%s][Recv] "), m_Comm[nStep].m_sComPort);
			m_Comm[nStep].Receive(data, (int)length);                    // length 길이 만큼 데이터를 얻음
			data[length] = '\0';
			_in_fn_Multi2Uni(data, wchData);
			for (int i = 0; i < (int)length; i++)
			{
				str += wchData[i];
			}
			str += " [";
			for (int i = 0; i < (int)length; i++)
			{
				temp.Format(_T("%02x "), data[i]);
				str += temp;
			}
			str += "]";
			m_fn_WriteLog(str);
		}
	}
	return 0;
}

void SerialLightDlg::OnBnClickedBnCmd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CString strMsg;
	//strMsg.Format(_T(":1W11255"));
	DPPROTOCOL1 stProtocol;
	stProtocol.start = ':';
	stProtocol.id = '1';
	stProtocol.comm = 'W';
	stProtocol.startAdd[0] = 'A';
	stProtocol.startAdd[1] = '1';
	stProtocol.data[0] = '1';
	stProtocol.end[0] = 0x0d;
	stProtocol.end[1] = 0x0a;

	char chBuffer[MAXBUF] = { 0, };
	wchar_t wchBuffer[MAXBUF] = { 0, };
	memcpy(chBuffer, &stProtocol, sizeof(DPPROTOCOL1));
	_in_fn_Multi2Uni(chBuffer, wchBuffer);
	GetDlgItem(IDC_EDIT_INPUT)->SetWindowText(wchBuffer);
	//m_fn_Send(stProtocol, m_bAllTrans);
}

void SerialLightDlg::m_fn_getSerialPort()
{

	//http://www.devpia.com/MAEUL/Contents/Detail.aspx?BoardID=50&MAEULNo=20&no=887656&ref=887655  
	HKEY hKey;

	RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &hKey);

	TCHAR szData[20], szName[100];
	DWORD index = 0, dwSize = 100, dwSize2 = 20, dwType = REG_SZ;
	((CComboBox*)GetDlgItem(IDC_CB_PORT))->ResetContent();
	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));

	while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL))
	{
		index++;

		RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
		((CComboBox*)GetDlgItem(IDC_CB_PORT))->AddString(CString(szData));

		memset(szData, 0x00, sizeof(szData));
		memset(szName, 0x00, sizeof(szName));
		dwSize = 100;
		dwSize2 = 20;
	}

	RegCloseKey(hKey);
}

void SerialLightDlg::OnCbnDropdownCbPort()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_fn_getSerialPort();
	int nCbCount = 0;
	nCbCount = ((CComboBox*)GetDlgItem(IDC_CB_PORT))->GetCount();
	if (nCbCount == 0)
	{
		CString strCom;
		for (int nStep = 1; nStep < MAX_PORT_COUNT; nStep++)
		{
			strCom.Format(_T("COM%d"), nStep);
			((CComboBox*)GetDlgItem(IDC_CB_PORT))->AddString(strCom);
		}
	}
}

void SerialLightDlg::m_fn_WriteLog(CString strMsg)
{
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_LOG);
	int nListCount = pList->GetCount();
	pList->AddString(strMsg);
	if (nListCount > MAX_LIST_ITEM)
		pList->DeleteString(0);
	pList->SetCurSel(nListCount);
}

void SerialLightDlg::OnBnClickedBnCmdreload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_fn_LoadINI();
	
}

void SerialLightDlg::m_fn_LoadINI()
{
	CString strPath;
	strPath.Format(_T("%s\\SerialCommand.ini"), m_fn_GetPath());
	

	TCHAR	chBuff[100] = { 0, };				//파일을 읽을때 사용하는 임시 버퍼
	TCHAR	chSeps[] = _T("[]");				//코큰 구분자
	TCHAR* chToken = 0;						//토큰
	int		nTypeStep = 0;
	//TCHAR chFilePath[_MAX_PATH] = { 0, };
	TCHAR* next_token1 = NULL;

#ifdef UNICODE
	
	std::wifstream infile(strPath);	//파일을 Open 한다.
#else
	ifstream infile(strPath);	//파일을 Open 한다.
#endif

	try {
		while (infile.getline(chBuff, 100))	//한 라인을 읽는다.
		{
			if (chBuff[0] == _T('['))
			{
				chToken = _tcstok_s(chBuff, chSeps, &next_token1);
				if (chToken != NULL)
				{
					_tcsnccpy_s(&m_strCmdList[nTypeStep][0], 100, chToken, _tcsclen(chToken));
					nTypeStep++;
				}
			}
			else
				continue;
		}
	}
	catch (...) {
		printf("File Open Error.\r\n");
	}
	infile.close();
	m_nCmdCount = nTypeStep;

	((CListBox*)GetDlgItem(IDC_LIST_CMD))->ResetContent();
	for (int nStep = 0; nStep < m_nCmdCount; nStep++)
	{
		((CListBox*)GetDlgItem(IDC_LIST_CMD))->AddString(m_strCmdList[nStep]);
	}
	SetDlgItemInt(IDC_STATIC_CMDCNT, m_nCmdCount);
	//m_fn_ReadINI(_T(""), _T(""), strPath);
	
}

CString SerialLightDlg::m_fn_GetPath()
{
	g_critical.Lock();
	static TCHAR pBuf[MAX_PATH] = { 0, };
	memset(pBuf, 0x00, sizeof(pBuf[0]) * MAX_PATH);
	GetModuleFileName(NULL, pBuf, sizeof(pBuf[0]) * MAX_PATH);
	CString strFilePath;
	strFilePath.Format(_T("%s"), pBuf);
	strFilePath = strFilePath.Left(strFilePath.ReverseFind(_T('\\')));
	g_critical.Unlock();
	return strFilePath;
}

CString SerialLightDlg::m_fn_ReadINI(CString strapp, CString strkey, CString strPath)
{
	TCHAR szReturnString[MAX_STRING_LENGTH] = { 0, };
	memset(szReturnString, 0x00, sizeof(szReturnString[0]) * MAX_STRING_LENGTH);
	GetPrivateProfileString(strapp, strkey, _T(""), szReturnString, MAX_STRING_LENGTH, strPath);
	CString str;
	str.Format(_T("%s"), szReturnString);
	return str;
}

void SerialLightDlg::m_fn_WriteINI(CString strapp, CString strkey, CString strval, CString strPath)
{
	WritePrivateProfileString(strapp, strkey, strval, strPath);
}

void SerialLightDlg::OnBnClickedBnWirteCmd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strPath;
	strPath.Format(_T("%s\\SerialCommand.ini"), m_fn_GetPath());
	if (m_nCmdCount == 0)
	{
		std::ofstream file;
		file.open(strPath, std::ios::binary);
		file.close();
	}

	CString strValue, strCmd;
	GetDlgItemText(IDC_EDIT_CMDNAME, strCmd);
	GetDlgItemText(IDC_EDIT_COMMAND, strValue);
	m_fn_WriteINI(strCmd, _T("Command"), strValue, strPath);
	m_fn_LoadINI();
}

void SerialLightDlg::OnBnClickedBnDelCmd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strPath;
	strPath.Format(_T("%s\\SerialCommand.ini"), m_fn_GetPath());
	CListBox* ctrlList = ((CListBox*)GetDlgItem(IDC_LIST_CMD));
	int nSel = ctrlList->GetCurSel();
	CString strSel;
	ctrlList->GetText(nSel, strSel);
	CString strValue[MAX_LIST_ITEM];

	for (int nStep = 0; nStep < MAX_LIST_ITEM; nStep++)
	{
		if (!_tcscmp(strSel, m_strCmdList[nStep]))
		{
			memset(m_strCmdList[nStep], 0x00, sizeof(m_strCmdList[0][0]) * MAX_LIST_ITEM);
		}
	}

	for (int nStep = 0; nStep < MAX_LIST_ITEM; nStep++)
	{
		if (_tcscmp(_T(""), m_strCmdList[nStep]))
		{
			strValue[nStep] = m_fn_ReadINI(m_strCmdList[nStep], _T("Command"), strPath);
		}
	}

	DeleteFile(strPath);
	for (int nStep = 0; nStep < MAX_LIST_ITEM; nStep++)
	{
		if (_tcscmp(_T(""), m_strCmdList[nStep]))
		{
			m_fn_WriteINI(m_strCmdList[nStep], _T("Command"), strValue[nStep], strPath);
		}
	}
	SetDlgItemText(IDC_EDIT_CMDNAME, _T(""));
	SetDlgItemText(IDC_EDIT_COMMAND, _T(""));
	m_fn_LoadINI();
}


void SerialLightDlg::OnLbnSelchangeListCmd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strPath;
	strPath.Format(_T("%s\\SerialCommand.ini"), m_fn_GetPath());
	CListBox* ctrlList = ((CListBox*)GetDlgItem(IDC_LIST_CMD));
	CString strCmd, strValue;
	ctrlList->GetText(ctrlList->GetCurSel(), strCmd);
	strValue = m_fn_ReadINI(strCmd, _T("Command"), strPath);
	SetDlgItemText(IDC_EDIT_CMDNAME, strCmd);
	SetDlgItemText(IDC_EDIT_COMMAND, strValue);
}


void SerialLightDlg::OnBnClickedBnCmdSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;

	GetDlgItemText(IDC_EDIT_COMMAND, strValue);
	SetDlgItemText(IDC_EDIT_INPUT, strValue);
}

void SerialLightDlg::m_fn_EnableButton(int nState)
{
	switch (nState)
	{
	case 0:
		GetDlgItem(IDC_BN_CLOSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BN_SEND)->EnableWindow(FALSE);
		break;
	case 1:
		GetDlgItem(IDC_BN_CLOSE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BN_SEND)->EnableWindow(TRUE);
	default:
		break;
	}
	
}



void SerialLightDlg::OnBnClickedBnAddQueue()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CListBox* ctrlList = ((CListBox*)GetDlgItem(IDC_LIST_QUEUE));
	CString strValue;
	GetDlgItemText(IDC_EDIT_INPUT, strValue);
	m_listCmd.push_back(strValue.GetBuffer());
	ctrlList->AddString(strValue);
	ctrlList->SetCurSel(ctrlList->GetCount()-1);
}


void SerialLightDlg::OnBnClickedBnDelQueue()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CListBox*)GetDlgItem(IDC_LIST_QUEUE))->ResetContent();
	m_listCmd.clear();
}


void SerialLightDlg::OnBnClickedBnSendQueue()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSleepTime = 0;
	nSleepTime = GetDlgItemInt(IDC_EDIT_SLEEP);
	std::list<std::wstring>::iterator it;
	for (it = m_listCmd.begin(); it != m_listCmd.end(); it++)
	{
		m_fn_Send(it->c_str(), m_bAllTrans);
		Sleep(nSleepTime);
	}
}
