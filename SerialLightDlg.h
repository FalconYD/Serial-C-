#pragma once

#include <list>
// SerialLightDlg 대화 상자

class SerialLightDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SerialLightDlg)

public:
	SerialLightDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SerialLightDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_LIGHT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBnOpen();
	afx_msg void OnBnClickedChkAll();
	afx_msg void OnBnClickedBnClose();
	afx_msg void OnBnClickedBnSend();
	afx_msg void OnBnClickedBnCmd();
	afx_msg void OnCbnDropdownCbPort();
	afx_msg void OnBnClickedBnCmdreload();
	afx_msg void OnBnClickedBnWirteCmd();
	afx_msg void OnBnClickedBnDelCmd();
	afx_msg void OnLbnSelchangeListCmd();
	afx_msg void OnBnClickedBnCmdSet();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT OnReceive(WPARAM length, LPARAM lpara);
private:
	//std::list<SerialComm> m_listComm;
	void m_fn_Send(CString strMsg, bool bAllSend = false);
	void m_fn_getSerialPort();
	void m_fn_LoadINI();
	void m_fn_WriteINI(CString strapp, CString strkey, CString strval, CString strPath);
	CString m_fn_ReadINI(CString strapp, CString strkey, CString strPath);
	CString m_fn_GetPath();
	void m_fn_WriteLog(CString strMsg);
	void m_fn_Init();
	void m_fn_UpdateCOMList();
	void m_fn_SerialOpen();
	void m_fn_EnableButton(int nState);
public:
	
private:
	SerialComm m_Comm[MAX_PORT_COUNT];
	int m_nSockCount = 0;
	int m_nCmdCount = 0;
	BOOL m_bAllTrans;
	BOOL m_bAttachCR;
	BOOL m_bAttachLF;
	BOOL m_bHex = FALSE;
	TCHAR m_strCmdList[MAX_LIST_ITEM][MAX_LIST_ITEM];
	std::list<std::wstring> m_listCmd;
public:
	afx_msg void OnBnClickedBnAddQueue();
	afx_msg void OnBnClickedBnDelQueue();
	afx_msg void OnBnClickedBnSendQueue();
};
