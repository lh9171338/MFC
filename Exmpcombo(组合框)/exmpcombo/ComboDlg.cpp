// ComboDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "exmpcombo.h"
#include "ComboDlg.h"
#include "afxdialogex.h"


// CComboDlg �Ի���

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


// CComboDlg ��Ϣ�������


BOOL CComboDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	pwnd=NULL;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CComboDlg::OnDestroy()
{
	CDialog::OnDestroy();
	if(pwnd!=NULL)
		delete pwnd;
	// TODO: �ڴ˴������Ϣ����������
}


void CComboDlg::OnSelchangeCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(pwnd!=NULL)
	{
		delete pwnd;							//ɾ���ϴ����ɵĿؼ�����
		pwnd=NULL;
	}
	int n=m_combobox.GetCurSel();				//��õ�ǰѡ�������
	switch(n)
	{
	case 0:
		pwnd=new CStatic;
		((CStatic*)pwnd)->Create(_T("��̬�ı�"),WS_VISIBLE,CRect(400,40,600,150),this,1);
		break;
	case 1:
		pwnd=new CEdit;
		((CEdit*)pwnd)->Create(WS_VISIBLE|WS_BORDER,CRect(400,40,600,150),this,2);		//�༭��
		break;
	case 2:
		pwnd =new CButton;
		((CButton*)pwnd)->Create(_T("��ť"),WS_VISIBLE|WS_DISABLED|BS_PUSHBUTTON,CRect(400,40,600,150),this,3);
		break;
	case 3:
		pwnd =new CButton;
		((CButton*)pwnd)->Create(_T("��ѡ��ť"),WS_VISIBLE|BS_RADIOBUTTON,CRect(400,40,600,150),this,4);
		break;
	case 4:
		pwnd =new CButton;
		((CButton*)pwnd)->Create(_T("��ѡ��ť"),WS_VISIBLE|BS_CHECKBOX,CRect(400,40,600,150),this,5);
		break;
	case 5:
		pwnd=new CListBox;
		((CListBox*)pwnd)->Create(WS_VISIBLE|WS_BORDER,CRect(400,40,600,150),this,6);			//�б��
		break;
	case 6:
		pwnd=new CComboBox;
		((CComboBox*)pwnd)->Create(WS_VISIBLE|CBS_DROPDOWN,CRect(400,40,600,150),this,7);		//��Ͽ�
		break;
	}
}


void CComboDlg::OnClickedButtonapply()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(pwnd!=NULL)
	{
		delete pwnd;
		pwnd=NULL;
	}
	UpdateData();
	pwnd=new CStatic;
	((CStatic*)pwnd)->Create(_T("Static Text��\n"+m_name),WS_VISIBLE,CRect(400,40,600,150),this,8);
}
