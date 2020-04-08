
// ExmpListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExmpList.h"
#include "ExmpListDlg.h"
#include "afxdialogex.h"
#include "afx.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CExmpListDlg �Ի���




CExmpListDlg::CExmpListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExmpListDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_name = _T("");
	m_capital = _T("");
	m_populat = _T("");
	m_area = _T("");
}

void CExmpListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSTATE, m_ListBx);
	DDX_Text(pDX, IDC_EDITNAME, m_name);
	DDX_Text(pDX, IDC_EDITCAPITAL, m_capital);
	DDX_Text(pDX, IDC_EDITPOPULAT, m_populat);
	DDX_Text(pDX, IDC_EDITAREA, m_area);
}

BEGIN_MESSAGE_MAP(CExmpListDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONADD, &CExmpListDlg::OnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTONDEL, &CExmpListDlg::OnClickedButtondel)
	ON_LBN_SELCHANGE(IDC_LISTSTATE, &CExmpListDlg::OnSelchangeListstate)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CExmpListDlg ��Ϣ�������

BOOL CExmpListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	read();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CExmpListDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CExmpListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CExmpListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExmpListDlg::OnClickedButtonadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_name.IsEmpty())
	{
		MessageBox(_T("�������Ʋ��ܿ�"));
		return ;
	}
	m_name.TrimLeft();
	m_name.TrimRight();							//ȥ�ո�
	if((m_ListBx.FindString(-1,m_name))!=LB_ERR)
	{
		MessageBox(_T("�б�������и�����������"));
		return ;
	}
	int n=m_ListBx.AddString(m_name);
	sstate state1;
	state1.name=m_name;
	state1.capital=m_capital;
	state1.populat=m_populat;
	state1.area=m_area;
	m_ListBx.SetItemDataPtr(n,new sstate(state1));		//��������
}


void CExmpListDlg::OnClickedButtondel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int n=m_ListBx.GetCurSel();
	if(n!=-1)
	{
		delete (sstate*)m_ListBx.GetItemDataPtr(n);		//�ͷŽṹ��ָ��
		m_ListBx.DeleteString(n);
		m_name=m_capital=m_populat=m_area=_T("");
		UpdateData(false);
	}
	else
		MessageBox(_T("û��ѡ���б�����б�����ʧ��"));

}


void CExmpListDlg::OnSelchangeListstate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int n=m_ListBx.GetCurSel();
	if(n!=-1)
	{
		sstate *p=(sstate*)m_ListBx.GetItemDataPtr(n);		
		m_name=p->name;
		m_capital=p->capital;
		m_populat=p->populat;
		m_area=p->area;
		UpdateData(false);
	}
}


void CExmpListDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	save();
	for(int n=m_ListBx.GetCount()-1;n>=0;n--)
		delete (sstate*)m_ListBx.GetItemDataPtr(n);		//�ͷŽṹ��ָ��
	// TODO: �ڴ˴������Ϣ����������
}


void CExmpListDlg::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		int n=m_ListBx.GetCount();
		ar<<n;
		for(int i=0;i<n;i++)
		{
			sstate *p=(sstate*)m_ListBx.GetItemDataPtr(i);	
			ar<<p->name<<p->capital<<p->populat<<p->area;								//���ļ�
		}
	}
	else
	{
		sstate state1;
		int n;
		ar>>n;
		for(int i=0;i<n;i++)
		{
			ar>>state1.name>>state1.capital>>state1.populat>>state1.area;				//���ļ�
			m_ListBx.AddString(state1.name);
			m_ListBx.SetItemDataPtr(i,new sstate(state1));		//��������
		}
	}
}
void CExmpListDlg::read()
{
	CFile file;
	if(file.Open(_T("file1.dat"),CFile::modeRead))
	{
		CArchive ar(&file,CArchive::load);
		Serialize(ar);
		ar.Close();
		file.Close();
	}
}
void CExmpListDlg::save()
{
	CFile file;
	if(file.Open(_T("file1.dat"),CFile::modeCreate|CFile::modeWrite))
	{
		CArchive ar(&file,CArchive::store);
		Serialize(ar);
		ar.Close();
		file.Close();
	}
}