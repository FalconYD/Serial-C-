
// SerialCommTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSerialCommTestApp:
// �� Ŭ������ ������ ���ؼ��� SerialCommTest.cpp�� �����Ͻʽÿ�.
//

class CSerialCommTestApp : public CWinApp
{
public:
	CSerialCommTestApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSerialCommTestApp theApp;
