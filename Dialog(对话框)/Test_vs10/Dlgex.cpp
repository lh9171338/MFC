// Dlgex.cpp : implementation file
//

#include "stdafx.h"
#include "Test_vs10.h"
#include "Dlgex.h"
#include "afxdialogex.h"


// CDlgex dialog

IMPLEMENT_DYNAMIC(CDlgex, CDialogEx)

CDlgex::CDlgex(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgex::IDD, pParent)
{

	m_nRadius = 0;
}

CDlgex::~CDlgex()
{
}

void CDlgex::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nRadius);
	DDV_MinMaxInt(pDX, m_nRadius, 10, 500);
}


BEGIN_MESSAGE_MAP(CDlgex, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CDlgex::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CDlgex message handlers


void CDlgex::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
