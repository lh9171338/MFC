// DlgButton.cpp : implementation file
//

#include "stdafx.h"
#include "Test_vs10.h"
#include "DlgButton.h"
#include "afxdialogex.h"


// CDlgButton dialog

IMPLEMENT_DYNAMIC(CDlgButton, CDialogEx)

CDlgButton::CDlgButton(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgButton::IDD, pParent)
{

}

CDlgButton::~CDlgButton()
{
}

void CDlgButton::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgButton, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO3, &CDlgButton::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CDlgButton message handlers


void CDlgButton::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
}
