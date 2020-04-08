// Example.cpp : implementation file
//

#include "stdafx.h"
#include "Test_vs10.h"
#include "Example.h"
#include "afxdialogex.h"


// CExample dialog

IMPLEMENT_DYNAMIC(CExample, CDialogEx)

CExample::CExample(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExample::IDD, pParent)
{

	m_nRadius = 0;
}

CExample::~CExample()
{
}

void CExample::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nRadius);
	DDV_MinMaxInt(pDX, m_nRadius, 0, 500);
}


BEGIN_MESSAGE_MAP(CExample, CDialogEx)
END_MESSAGE_MAP()


// CExample message handlers
