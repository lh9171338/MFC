
// ExmpList.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExmpListApp:
// �йش����ʵ�֣������ ExmpList.cpp
//

class CExmpListApp : public CWinApp
{
public:
	CExmpListApp();

// ��д
public:
	virtual BOOL InitInstance();
	
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExmpListApp theApp;