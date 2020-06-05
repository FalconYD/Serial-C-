
// SerialCommTestDlg.h : 헤더 파일
//

#pragma once

//#include "MyComm.h"
//#include "SerialComm_DLL.h"
#include "afxwin.h"

// CSerialCommTestDlg 대화 상자
class CSerialCommTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CSerialCommTestDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALCOMMTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
