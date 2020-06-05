#pragma once
#include "afxwin.h"
#include <afxmt.h>
#include <process.h>


#define	MAXBUF		1024
#define	InBufSize	1024
#define	OutBufSize	1024
#define ASCII_XON	0x11
#define ASCII_XOFF	0x13
#define	WM_MYRECEIVE	(WM_USER+1)
#define	WM_MYCLOSE		(WM_USER+2)
class SerialComm :
	public CCmdTarget
{
public:
	DECLARE_DYNCREATE(SerialComm)
	SerialComm();
	~SerialComm();
	SerialComm(const SerialComm& cls);

public:
	CString m_sComPort;
	CString m_sBaudRate;
	CString m_sParity;
	CString m_sDataBit;
	CString m_sStopBit;
	BOOL m_bFlowChk;
	BOOL m_bIsOpenned;
	int m_nLength;
	char m_sInBuf[MAXBUF *2];
	CEvent* m_pEvent = nullptr;
	OVERLAPPED m_OLW, m_OLR;
	HWND m_hWnd;
	HANDLE m_hComDev;
public:
	BOOL Create(HWND hWnd);
	void InitSerial();
	BOOL Send(char* outbuf, int len);
	int Receive(char* inbuf, int len);
	void Close();
	void HandleClose();
	void Clear();
	void SetParameter(CString port, CString baudrate, CString parity, CString databit, CString stopbit);
	static unsigned int _stdcall THREAD_SERIALCOMM(void* pParam);
};
