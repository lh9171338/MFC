// PsdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test_vs10.h"
#include "PsdDlg.h"
#include "afxdialogex.h"


// CPsdDlg dialog

IMPLEMENT_DYNAMIC(CPsdDlg, CDialogEx)

CPsdDlg::CPsdDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPsdDlg::IDD, pParent)
{

	m_strPsdShow = _T("");
	m_strPsd = _T("");
	m_strUsername = _T("");
}

CPsdDlg::~CPsdDlg()
{
}

void CPsdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlCheck);
	DDX_Text(pDX, IDC_EDIT_PADWORDV, m_strPsdShow);
	DDX_Text(pDX, IDC_EDIT_PSDWORD, m_strPsd);
	DDX_Text(pDX, IDC_EDITI_COUNT, m_strUsername);
}


BEGIN_MESSAGE_MAP(CPsdDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_PSDWORD, &CPsdDlg::OnEnChangeEditPsdword)
END_MESSAGE_MAP()


// CPsdDlg message handlers


void CPsdDlg::OnEnChangeEditPsdword()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

		UpdateData();
		m_strPsdShow = m_strPsd;
		UpdateData(false);

	// TODO:  Add your control notification handler code here
}
