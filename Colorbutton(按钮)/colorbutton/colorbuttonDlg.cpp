
// colorbuttonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "colorbutton.h"
#include "colorbuttonDlg.h"
#include "afxdialogex.h"

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


// CcolorbuttonDlg 对话框




CcolorbuttonDlg::CcolorbuttonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcolorbuttonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_color = 0;
}

void CcolorbuttonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIOCOLOR, m_color);
	DDX_Check(pDX, IDC_CHECKRED, m_RED);
	DDX_Check(pDX, IDC_CHECKGREEN, m_GREEN);
	DDX_Check(pDX, IDC_CHECKBLUE, m_BLUE);
}

BEGIN_MESSAGE_MAP(CcolorbuttonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_RADIOCOLOR, &CcolorbuttonDlg::OnClickedRadiocolor)
	ON_COMMAND(IDC_RADIOBLACK, &CcolorbuttonDlg::OnRadioblack)
	ON_BN_CLICKED(IDC_BUTTONAPPLY, &CcolorbuttonDlg::OnClickedButtonapply)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CcolorbuttonDlg 消息处理程序

BOOL CcolorbuttonDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcolorbuttonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcolorbuttonDlg::OnPaint()
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
HCURSOR CcolorbuttonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CcolorbuttonDlg::OnClickedRadiocolor()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_color=1;
	CWnd *p;
	p=GetDlgItem(IDC_CHECKRED);
	p->EnableWindow(true);
	p=GetDlgItem(IDC_CHECKGREEN);
	p->EnableWindow(true);
	p=GetDlgItem(IDC_CHECKBLUE);
	p->EnableWindow(true);
}


void CcolorbuttonDlg::OnRadioblack()
{
	// TODO: 在此添加命令处理程序代码
	//m_color=0;
	CWnd *p;
	p=GetDlgItem(IDC_CHECKRED);
	p->EnableWindow(false);
	p=GetDlgItem(IDC_CHECKGREEN);
	p->EnableWindow(false);
	p=GetDlgItem(IDC_CHECKBLUE);
	p->EnableWindow(false);
}


void CcolorbuttonDlg::OnClickedButtonapply()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *p=GetDlgItem(IDC_BUTTONDRAW);
	p->Invalidate();
	p->UpdateWindow();
}


void CcolorbuttonDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData();
	COLORREF m_c;
	if(m_color==0)
		m_c=RGB(m_RED?255:0,m_GREEN?255:0,m_BLUE?255:0);
	else
		m_c=RGB(0,0,0);
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);				//连接句柄
	if(nIDCtl==IDC_BUTTONDRAW)
	{
		CWnd *p=GetDlgItem(IDC_BUTTONDRAW);
		CRect r;
		p->GetClientRect(&r);						//获取按键所占区域
		dc.FillSolidRect(&r,m_c);					//绘制按键
	}
	dc.Detach();									//分离句柄
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
