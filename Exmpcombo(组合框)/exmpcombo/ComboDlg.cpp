// ComboDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "exmpcombo.h"
#include "ComboDlg.h"
#include "afxdialogex.h"


// CComboDlg 对话框

IMPLEMENT_DYNAMIC(CComboDlg, CDialog)

CComboDlg::CComboDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComboDlg::IDD, pParent)
{

	m_name = _T("");
}

CComboDlg::~CComboDlg()
{
}

void CComboDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, m_combobox);
	DDX_CBString(pDX, IDC_COMBO, m_name);
}


BEGIN_MESSAGE_MAP(CComboDlg, CDialog)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO, &CComboDlg::OnSelchangeCombo)
	ON_BN_CLICKED(IDC_BUTTONAPPLY, &CComboDlg::OnClickedButtonapply)
END_MESSAGE_MAP()


// CComboDlg 消息处理程序


BOOL CComboDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  在此添加额外的初始化
	pwnd=NULL;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CComboDlg::OnDestroy()
{
	CDialog::OnDestroy();
	if(pwnd!=NULL)
		delete pwnd;
	// TODO: 在此处添加消息处理程序代码
}


void CComboDlg::OnSelchangeCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	if(pwnd!=NULL)
	{
		delete pwnd;							//删除上次生成的控件对象
		pwnd=NULL;
	}
	int n=m_combobox.GetCurSel();				//获得当前选择的引索
	switch(n)
	{
	case 0:
		pwnd=new CStatic;
		((CStatic*)pwnd)->Create(_T("静态文本"),WS_VISIBLE,CRect(400,40,600,150),this,1);
		break;
	case 1:
		pwnd=new CEdit;
		((CEdit*)pwnd)->Create(WS_VISIBLE|WS_BORDER,CRect(400,40,600,150),this,2);		//编辑框
		break;
	case 2:
		pwnd =new CButton;
		((CButton*)pwnd)->Create(_T("按钮"),WS_VISIBLE|WS_DISABLED|BS_PUSHBUTTON,CRect(400,40,600,150),this,3);
		break;
	case 3:
		pwnd =new CButton;
		((CButton*)pwnd)->Create(_T("单选按钮"),WS_VISIBLE|BS_RADIOBUTTON,CRect(400,40,600,150),this,4);
		break;
	case 4:
		pwnd =new CButton;
		((CButton*)pwnd)->Create(_T("复选按钮"),WS_VISIBLE|BS_CHECKBOX,CRect(400,40,600,150),this,5);
		break;
	case 5:
		pwnd=new CListBox;
		((CListBox*)pwnd)->Create(WS_VISIBLE|WS_BORDER,CRect(400,40,600,150),this,6);			//列表框
		break;
	case 6:
		pwnd=new CComboBox;
		((CComboBox*)pwnd)->Create(WS_VISIBLE|CBS_DROPDOWN,CRect(400,40,600,150),this,7);		//组合框
		break;
	}
}


void CComboDlg::OnClickedButtonapply()
{
	// TODO: 在此添加控件通知处理程序代码
	if(pwnd!=NULL)
	{
		delete pwnd;
		pwnd=NULL;
	}
	UpdateData();
	pwnd=new CStatic;
	((CStatic*)pwnd)->Create(_T("Static Text：\n"+m_name),WS_VISIBLE,CRect(400,40,600,150),this,8);
}
