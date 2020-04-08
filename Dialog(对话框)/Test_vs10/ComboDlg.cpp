// ComboDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test_vs10.h"
#include "ComboDlg.h"
#include "afxdialogex.h"


// CComboDlg dialog

IMPLEMENT_DYNAMIC(CComboDlg, CDialogEx)

CComboDlg::CComboDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComboDlg::IDD, pParent)
{

	m_strCtrlName = _T("");
	m_straddcombo = _T("");
}

CComboDlg::~CComboDlg()
{
}

void CComboDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CTRNAME, m_ComboBx);
	DDX_CBString(pDX, IDC_COMBO_CTRNAME, m_strCtrlName);
	DDX_Text(pDX, IDC_EDIT_ADDCOMBO, m_straddcombo);
}


BEGIN_MESSAGE_MAP(CComboDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_CTRNAME, &CComboDlg::OnCbnSelchangeComboCtrname)
	ON_BN_CLICKED(IDC_APPLY, &CComboDlg::OnBnClickedApply)
END_MESSAGE_MAP()


// CComboDlg message handlers


BOOL CComboDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
		m_pwnd = NULL;


	/*m_ComboBx.AddString(_T("静态文本"));
	m_ComboBx.AddString(_T("编辑框"));
	m_ComboBx.AddString(_T("组框"));
	m_ComboBx.AddString(_T("按钮"));
	m_ComboBx.AddString(_T("复选框"));
	m_ComboBx.AddString(_T("单选按钮"));
	m_ComboBx.AddString(_T("组合框"));
	m_ComboBx.AddString(_T("列表框"));
	m_ComboBx.AddString(_T("滚动条"));*/


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CComboDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialogEx::DestroyWindow();
}


void CComboDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if(m_pwnd != NULL)
		delete m_pwnd;

	// TODO: Add your message handler code here
}


void CComboDlg::OnCbnSelchangeComboCtrname()
{
	// TODO: Add your control notification handler code here

		if(m_pwnd != NULL)
	{
		delete m_pwnd;
		m_pwnd = NULL;
	}

	int iChoice = m_ComboBx.GetCurSel();

	switch(iChoice)
	{
	case 0:
		m_pwnd = new CStatic;
		((CStatic *)m_pwnd)->Create(_T("Static Text"), WS_VISIBLE, CRect(180,40,300,70), this, 1);
		break;

	case 1:
		m_pwnd = new CEdit;
		((CEdit *)m_pwnd)->Create(WS_VISIBLE | WS_BORDER, CRect(180,40,300,70), this, 2);
		break;

	case 2:
		m_pwnd = new CButton;
		((CButton *)m_pwnd)->Create(_T("Group Box"), WS_VISIBLE | BS_GROUPBOX, CRect(180,40,300,70), this, 3);
		break;

		
	case 3:
		m_pwnd = new CButton;
		((CButton *)m_pwnd)->Create(_T("Button"), WS_VISIBLE | WS_DISABLED | BS_PUSHBUTTON, CRect(180,40,300,70), this, 4);
		break;

	case 4:
		m_pwnd = new CButton;
		((CButton *)m_pwnd)->Create(_T("Check Box"), WS_VISIBLE | BS_CHECKBOX, CRect(180,40,300,70), this, 5);
		break;

	case 5:
		m_pwnd = new CButton;
		((CButton *)m_pwnd)->Create(_T("Radio Button"), WS_VISIBLE | BS_RADIOBUTTON, CRect(180,40,300,70), this, 6);
		break;

	case 6:
		m_pwnd = new CComboBox;
		((CComboBox *)m_pwnd)->Create( WS_VISIBLE | CBS_DROPDOWN , CRect(180,40,300,70), this, 7);
		break;

		
	case 7:
		m_pwnd = new CListBox;
		((CListBox *)m_pwnd)->Create( WS_VISIBLE | WS_BORDER, CRect(180,40,300,70), this, 8);
		break;

	case 8:
		m_pwnd = new CScrollBar;
		((CScrollBar *)m_pwnd)->Create( WS_VISIBLE | SBS_VERT, CRect(250,40,300,70), this, 9);
		break;
		
		
	default:
		m_pwnd = new CStatic;
		((CStatic *)m_pwnd)->Create(_T("No any Control"), WS_VISIBLE, CRect(180,40,300,70), this, 1);
		break;
		
		break;
	}
}


void CComboDlg::OnBnClickedApply()
{
	// TODO: Add your control notification handler code here
		if(m_pwnd != NULL)
	{
		delete m_pwnd;
		m_pwnd = NULL;
	}

	UpdateData();

	m_pwnd = new CStatic;

	((CStatic *)m_pwnd)->Create(_T("Static Text: \n" + m_strCtrlName), WS_VISIBLE, CRect(180,40,300,70), this, 10);
}
