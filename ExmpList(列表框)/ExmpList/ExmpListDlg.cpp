
// ExmpListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ExmpList.h"
#include "ExmpListDlg.h"
#include "afxdialogex.h"
#include "afx.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CExmpListDlg 对话框




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


// CExmpListDlg 消息处理程序

BOOL CExmpListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	read();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExmpListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExmpListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExmpListDlg::OnClickedButtonadd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_name.IsEmpty())
	{
		MessageBox(_T("国家名称不能空"));
		return ;
	}
	m_name.TrimLeft();
	m_name.TrimRight();							//去空格
	if((m_ListBx.FindString(-1,m_name))!=LB_ERR)
	{
		MessageBox(_T("列表框中已有该项，不能再添加"));
		return ;
	}
	int n=m_ListBx.AddString(m_name);
	sstate state1;
	state1.name=m_name;
	state1.capital=m_capital;
	state1.populat=m_populat;
	state1.area=m_area;
	m_ListBx.SetItemDataPtr(n,new sstate(state1));		//建立关联
}


void CExmpListDlg::OnClickedButtondel()
{
	// TODO: 在此添加控件通知处理程序代码
	int n=m_ListBx.GetCurSel();
	if(n!=-1)
	{
		delete (sstate*)m_ListBx.GetItemDataPtr(n);		//释放结构体指针
		m_ListBx.DeleteString(n);
		m_name=m_capital=m_populat=m_area=_T("");
		UpdateData(false);
	}
	else
		MessageBox(_T("没有选择列表项或列表框操作失败"));

}


void CExmpListDlg::OnSelchangeListstate()
{
	// TODO: 在此添加控件通知处理程序代码
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
		delete (sstate*)m_ListBx.GetItemDataPtr(n);		//释放结构体指针
	// TODO: 在此处添加消息处理程序代码
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
			ar<<p->name<<p->capital<<p->populat<<p->area;								//存文件
		}
	}
	else
	{
		sstate state1;
		int n;
		ar>>n;
		for(int i=0;i<n;i++)
		{
			ar>>state1.name>>state1.capital>>state1.populat>>state1.area;				//读文件
			m_ListBx.AddString(state1.name);
			m_ListBx.SetItemDataPtr(i,new sstate(state1));		//建立关联
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