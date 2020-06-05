
// SerialCommTestDlg.h : ��� ����
//

#pragma once

//#include "MyComm.h"
//#include "SerialComm_DLL.h"
#include "afxwin.h"

// CSerialCommTestDlg ��ȭ ����
class CSerialCommTestDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSerialCommTestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALCOMMTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	SerialComm* m_Comm;
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnClose();
	LRESULT OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT OnReceive(WPARAM length, LPARAM lpara);
	afx_msg void OnBnClickedBtnTest();
	CString m_strRecvData;
	BOOL bWorking;
	CString m_strLight;
	afx_msg void OnBnClickedBtnRun();
	CEdit m_edit_rcv_view;
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnStop();
};
UINT CommTestThread(LPVOID lpData);
