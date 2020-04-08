
// player1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "player1.h"
#include "player1Dlg.h"
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
public:
//	afx_msg void OnButtonaddsong();
//	afx_msg void OnButtondeletesong();
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


// Cplayer1Dlg 对话框




Cplayer1Dlg::Cplayer1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cplayer1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cplayer1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_OCX1,m_player);
	DDX_Control(pDX, IDC_PROGRESSPALY, m_progress);
	DDX_Control(pDX, IDC_LISTSONG, m_listsong);
}

BEGIN_MESSAGE_MAP(Cplayer1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONOPEN, &Cplayer1Dlg::OnClickedButtonopen)
	ON_BN_CLICKED(IDC_BUTTONMINUS, &Cplayer1Dlg::OnClickedButtonminus)
	ON_BN_CLICKED(IDC_BUTTONGO, &Cplayer1Dlg::OnClickedButtongo)
	ON_BN_CLICKED(IDC_BUTTONFULL, &Cplayer1Dlg::OnClickedButtonfull)
	ON_BN_CLICKED(IDC_BUTTONBACK, &Cplayer1Dlg::OnClickedButtonback)
	ON_BN_CLICKED(IDC_BUTTONADD, &Cplayer1Dlg::OnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTONPAUSE, &Cplayer1Dlg::OnClickedButtonpause)
	ON_BN_CLICKED(IDC_BUTTONPLAY, &Cplayer1Dlg::OnClickedButtonplay)
	ON_BN_CLICKED(IDC_BUTTONSTOP, &Cplayer1Dlg::OnClickedButtonstop)
	ON_WM_TIMER()
	ON_LBN_DBLCLK(IDC_LISTSONG, &Cplayer1Dlg::OnDblclkListsong)
	ON_BN_CLICKED(IDC_BUTTONADDSONG, &Cplayer1Dlg::OnClickedButtonaddsong)
	ON_BN_CLICKED(IDC_BUTTONDELETESONG, &Cplayer1Dlg::OnClickedButtondeletesong)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// Cplayer1Dlg 消息处理程序

BOOL Cplayer1Dlg::OnInitDialog()
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

	m_control=static_cast<CWMPControls>(m_player.get_controls());
	m_setting=m_player.get_settings();	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cplayer1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cplayer1Dlg::OnPaint()
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
HCURSOR Cplayer1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cplayer1Dlg::OnClickedButtonopen()
{
	// TODO: 在此添加控件通知处理程序代码
	int n=m_listsong.GetCurSel();
	if(n!=-1)
	{
		filename=*(CString*)(m_listsong.GetItemDataPtr(n));
		m_player.put_URL(filename);
		m_media=static_cast<CWMPMedia>(m_player.newMedia(filename));
		m_progress.SetRange(0,(int)m_media.get_duration());  //媒体总长度
		m_progress.SetPos(0);	
	}
	else
		MessageBox(_T("没有选择列表项或列表框操作失败"));	
}


void Cplayer1Dlg::OnClickedButtonminus()
{
	// TODO: 在此添加控件通知处理程序代码
	m_setting.put_volume(m_setting.get_volume()-10);   //音量减少
}


void Cplayer1Dlg::OnClickedButtongo()
{
	// TODO: 在此添加控件通知处理程序代码
	m_control.fastForward();   //快进
}


void Cplayer1Dlg::OnClickedButtonfull()
{
	// TODO: 在此添加控件通知处理程序代码
	m_player.put_fullScreen(1);   //全屏
}


void Cplayer1Dlg::OnClickedButtonback()
{
	// TODO: 在此添加控件通知处理程序代码
	m_control.fastReverse();   //快退
}


void Cplayer1Dlg::OnClickedButtonadd()
{
	// TODO: 在此添加控件通知处理程序代码
	m_setting.put_volume(m_setting.get_volume()+10);  //音量增加
}


void Cplayer1Dlg::OnClickedButtonpause()
{
	// TODO: 在此添加控件通知处理程序代码
	m_control.pause();	//暂停
}


void Cplayer1Dlg::OnClickedButtonplay()
{
	// TODO: 在此添加控件通知处理程序代码
	m_control.play();  //播放
}


void Cplayer1Dlg::OnClickedButtonstop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_control.stop();        //停止
}


void Cplayer1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent != 1)  
         return;
	m_progress.SetPos(m_progress.GetPos()+1);
	CDialogEx::OnTimer(nIDEvent);
}
BEGIN_EVENTSINK_MAP(Cplayer1Dlg, CDialogEx)
	ON_EVENT(Cplayer1Dlg, IDC_OCX1, 5101, Cplayer1Dlg::PlayStateChangeOcx1, VTS_I4)
END_EVENTSINK_MAP()


void Cplayer1Dlg::PlayStateChangeOcx1(long NewState)
{
	// TODO: 在此处添加消息处理程序代码
	if (NewState==3)					 //播放状态时, 开启定时器
		SetTimer(1,1000,NULL);	
	else if (NewState==1)				//停止时, 关闭定时器, 进度条回0
	{
		m_progress.SetPos(0);
		KillTimer(1);
	}
	/*else
	{
		KillTimer(1);
		CString fileName;
		CFileDialog fileDialog( TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("音频、视频文件(*.*)|*.*||"),this);
		if (fileDialog.DoModal() == IDOK)
		{
			fileName=fileDialog.GetPathName();
			m_player.put_URL(fileName);   //打开播放
		} 
		m_media=static_cast<CWMPMedia>(m_player.newMedia(fileName));
		m_progress.SetRange(0,(int)m_media.get_duration());  //媒体总长度
		m_progress.SetPos(0);	
	}*/
}


void Cplayer1Dlg::OnDblclkListsong()
{
	// TODO: 在此添加控件通知处理程序代码
	int n=m_listsong.GetCurSel();
	if(n!=-1)
	{
		filename=*(CString*)m_listsong.GetItemDataPtr(n);
		m_player.put_URL(filename);
		m_media=static_cast<CWMPMedia>(m_player.newMedia(filename));
		m_progress.SetRange(0,(int)m_media.get_duration());  //媒体总长度
		m_progress.SetPos(0);	
	}
}




void Cplayer1Dlg::OnClickedButtonaddsong()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDialog( TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT| OFN_OVERWRITEPROMPT,_T("音频、视频文件(*.*)|*.*||"),this);
	if (fileDialog.DoModal() == IDOK)
	{
		POSITION pos = fileDialog.GetStartPosition();
		while (pos != NULL)
		{
			filename = fileDialog.GetNextPathName(pos);
			int pos1 = filename.ReverseFind('\\') + 1;
			CString str = filename.Mid(pos1);
			int pos2 = str.ReverseFind('.');
			name = str.Left(pos2);

			if (m_listsong.FindString(-1, name) != -1)
			{
				MessageBox(_T("列表框中已有该项，不能再添加"));
				continue;
			}
			else
			{
				int n = m_listsong.AddString(name);
				m_listsong.SetItemDataPtr(n, new CString(filename));		//建立关联
			}
		}
	} 
}


void Cplayer1Dlg::OnClickedButtondeletesong()
{
	// TODO: 在此添加控件通知处理程序代码
	int n=m_listsong.GetCurSel();
	if(n!=-1)
	{
		delete (CString*)m_listsong.GetItemDataPtr(n);		//释放结构体指针
		m_listsong.DeleteString(n);
	}
	else
		MessageBox(_T("没有选择列表项或列表框操作失败"));
}
void Cplayer1Dlg::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		int n=m_listsong.GetCount();
		ar<<n;
		for(int i=0;i<n;i++)
		{
			filename=*(CString*)m_listsong.GetItemDataPtr(i);
			m_listsong.GetText(i,name);
			ar<<filename<<name;								//存文件
		}
	}
	else
	{
		int n;
		ar>>n;
		for(int i=0;i<n;i++)
		{
			ar>>filename>>name;				//读文件
			m_listsong.AddString(name);
			m_listsong.SetItemDataPtr(i,new CString(filename));		//建立关联
		}
	}
}
void Cplayer1Dlg::read()
{
	CFile file;
	if(file.Open(_T(".\\file1.dat"),CFile::modeRead))
	{
		CArchive ar(&file,CArchive::load);
		Serialize(ar);
		ar.Close();
		file.Close();
	}
}
void Cplayer1Dlg::save()
{
	CFile file;
	if(file.Open(_T(".\\file1.dat"),CFile::modeCreate|CFile::modeWrite))
	{
		CArchive ar(&file,CArchive::store);
		Serialize(ar);
		ar.Close();
		file.Close();
	}
}

void Cplayer1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	save();
	for(int n=m_listsong.GetCount()-1;n>=0;n--)
		delete (CString*)m_listsong.GetItemDataPtr(n);		//释放结构体指针
	// TODO: 在此处添加消息处理程序代码
}
