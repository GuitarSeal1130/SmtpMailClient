
// SmtpMail.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSmtpMailApp:
// �йش����ʵ�֣������ SmtpMail.cpp
//

class CSmtpMailApp : public CWinApp
{
public:
	CSmtpMailApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSmtpMailApp theApp;