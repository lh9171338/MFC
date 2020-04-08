
// HuaRongDaoView.cpp : CHuaRongDaoView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HuaRongDao.h"
#endif

#include "HuaRongDaoDoc.h"
#include "HuaRongDaoView.h"
#include <mmsystem.h>
#include <Digitalv.h>
#pragma comment( lib, "Winmm.lib" ) 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHuaRongDaoView

IMPLEMENT_DYNCREATE(CHuaRongDaoView, CView)

BEGIN_MESSAGE_MAP(CHuaRongDaoView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHuaRongDaoView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_CREATE()

	ON_BN_CLICKED(IDB_RESTART,ONRESTART)
	ON_BN_CLICKED(IDB_SAVE,ONSAVE)
	ON_BN_CLICKED(IDB_LOAD,ONLOAD)
	ON_BN_CLICKED(IDB_NEXT,ONNEXT)
	ON_BN_CLICKED(IDB_HELP,ONHELP)
	ON_BN_CLICKED(IDB_LEVEL,ONLEVEL)
	ON_BN_CLICKED(IDB_VIDEO,ONVIDEO)
	ON_LBN_SELCHANGE(IDC_LISTLEVEL,OnSelchangeListlevel)
	ON_LBN_SELCHANGE(IDC_LISTVIDEO,OnSelchangeListvideo)
	ON_LBN_DBLCLK(IDC_LISTLEVEL,OnDblclkListlevel)
	ON_LBN_DBLCLK(IDC_LISTVIDEO,OnDblclkListvideo)

	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CHuaRongDaoView 构造/析构
Person person[15]={{0,_T("01.曹操")},{1,_T("02.张飞-竖")},{1,_T("03.张飞-横")},{2,_T("04.赵云-竖")},{2,_T("05.赵云-横")},
				{3,_T("06.马超-竖")},{3,_T("07.马超-横")},{4,_T("08.黄忠-竖")},{4,_T("09.黄忠-横")},{5,_T("10.关羽-横")},
				{5,_T("11.关羽-竖")},{6,_T("12.卒1")},{7,_T("13.卒2")},{8,_T("14.卒3")},{9,_T("15.卒4")}};
CHuaRongDaoView::CHuaRongDaoView()
{
	// TODO: 在此处添加构造代码
	playflag=false;
	successflag=false;				
	makeflag=false;	
	dragflag=false;
	timeflag=false;
	pwndstatic=NULL;
	pwndedit=NULL;
	pwndlevel_list=NULL;				
	pwndvideo_list=NULL;
	m_date1=m_date2=_T("");
}
CHuaRongDaoView::~CHuaRongDaoView()
{
}

BOOL CHuaRongDaoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CHuaRongDaoView 绘制

void CHuaRongDaoView::OnDraw(CDC* pDC)
{
	CHuaRongDaoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC MemDC;
	CBitmap MemBitmap;
	CRect r;
	GetClientRect(r);
	MemDC.CreateCompatibleDC(NULL); 
	MemBitmap.CreateCompatibleBitmap(pDC,r.right,r.bottom); 
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap); 
	MemDC.FillSolidRect(0,0,r.right,r.bottom,RGB(255,255,255)); 

	draw(&MemDC);

	pDC->BitBlt(0,0,r.right,r.bottom,&MemDC,0,0,SRCCOPY); 
	MemBitmap.DeleteObject(); 
	MemDC.DeleteDC(); 
	
	// TODO: 在此处为本机数据添加绘制代码
}


// CHuaRongDaoView 打印


void CHuaRongDaoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHuaRongDaoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHuaRongDaoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CHuaRongDaoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CHuaRongDaoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CHuaRongDaoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHuaRongDaoView 诊断

#ifdef _DEBUG
void CHuaRongDaoView::AssertValid() const
{
	CView::AssertValid();
}

void CHuaRongDaoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHuaRongDaoDoc* CHuaRongDaoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHuaRongDaoDoc)));
	return (CHuaRongDaoDoc*)m_pDocument;
}
#endif //_DEBUG


// CHuaRongDaoView 消息处理程序


void CHuaRongDaoView::OnLButtonDown(UINT nFlags, CPoint point)			//移动
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(makeflag)
	{
		int x=point.x/100-2;
		int y=(point.y+50)/100-1;
		if(x>=0&&x<4&&y>=0&&y<5)											//点在棋盘内							
		{
			if(!m_chessboard[x][y].empty)									//点到棋子
			{
				m_chessman[m_chessmannumber].m_clickflag=false;
				m_chessmannumber=getchessmannumber(x,y);
				m_chessman[m_chessmannumber].m_clickflag=true;
				b3.EnableWindow();
				dragflag=false;
			}
			else if(m_chessmannumber!=10)										//点在空位，放置
			{
				setchess(x,y);	
			}
			reflesh();
		}
	}
	else if(!playflag)				//不在播放状态
	{
		if(pwndstatic!=NULL)
		{
			delete pwndstatic;							//删除上次生成的控件对象
			pwndstatic=NULL;
			b5.EnableWindow();
		}
		if(pwndlevel_list!=NULL)
		{
			delete pwndlevel_list;							//删除上次生成的控件对象
			pwndlevel_list=NULL;
			b6.EnableWindow();
			b1.SetWindowTextW(_T("开始游戏"));
		}
		if(timeflag)
		{
			int x=point.x/100-2;
			int y=(point.y+50)/100-1;
			if(x>=0&&x<4&&y>=0&&y<5)											//点在棋盘内							
			{
				if(!m_chessboard[x][y].empty)									//点到棋子
				{
					m_chessman[m_chessmannumber].m_clickflag=false;
					m_chessmannumber=getchessmannumber(x,y);
					m_chessman[m_chessmannumber].m_clickflag=true;
				}
				else if(m_chessmannumber!=10)										//点在空位，移动
				{
					m_d=getderection(x,y);
					if(m_d!='\0')												//无效方向
					{
						move(m_d);
						m_chessman[m_chessmannumber].move(m_d);

						/***************************************存数组**********************************/
						m_stepnumber++;
						GetDocument()->addmovement(m_chessmannumber,m_d,m_stepnumber);
						succeed();
					}
				}
				reflesh();
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}
void CHuaRongDaoView::OnRButtonDown(UINT nFlags, CPoint point)			//后撤
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!playflag&&timeflag)
	{
		if(m_stepnumber)
		{
			m_stepnumber--;
			m_chessman[m_chessmannumber].m_clickflag=false;
			m_chessmannumber=GetDocument()->m_movementarray.GetAt(m_stepnumber)->m_chessmannumber;
			m_chessman[m_chessmannumber].m_clickflag=true;
			m_d=GetDocument()->m_movementarray.GetAt(m_stepnumber)->m_d+32;//转小写
			move(m_d);								
			m_chessman[m_chessmannumber].move(m_d);
	
			/***************************************清数组**********************************/
			GetDocument()->m_movementarray.RemoveAt(m_stepnumber);
			Invalidate();
		}
	}
	CView::OnRButtonDown(nFlags, point);
}
void CHuaRongDaoView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(makeflag&&m_chessmannumber!=10)						
	{
		if(!m_chessman[m_chessmannumber].m_finishset)
		{
			int w=m_chessman[m_chessmannumber].m_width/200;
			int h=m_chessman[m_chessmannumber].m_height/200;
			int x=point.x/100-2;
			int y=(point.y+50)/100-1;
			if(x>=0&&y>=0&&x+w<4&&y+h<5)								//点在矩形内
			{
				dragflag=true;
				if((m_chessman[m_chessmannumber].m_x!=x)||(m_chessman[m_chessmannumber].m_y!=y))
				{
					m_chessman[m_chessmannumber].m_x=x;
					m_chessman[m_chessmannumber].m_y=y;
					reflesh();
				}
			}
		}
	}
	CView::OnMouseMove(nFlags, point);
}
void CHuaRongDaoView::initselect(int level)
{
	if(level>0)
	{
		load_level(level);
		m_chessmannumber=10;
		m_d='\0';
		m_stepnumber=0;
		m_time=0;
		clearmovement();
	}
	else
	{
		for(int i=0;i<10;i++)
			m_chessman[i].m_finishset=false;
	}
}
void CHuaRongDaoView::draw(CDC *pDC)
{
	/**************************背景**************************/
	CPen pen1(PS_SOLID,3,RGB(0,0,0));
	pDC->SelectObject(&pen1);
	CBrush brush1(RGB(255,153,0));
	pDC->SelectObject(&brush1);
	pDC->Rectangle(0,0,800,600);

	CBrush brush2(RGB(0,255,0));
	pDC->SelectObject(&brush2);				
	pDC->Rectangle(200,50,600,550);

	/**************************画图**************************/
	for(int i=0;i<10;i++)
		m_chessman[i].draw(pDC);
	if(dragflag)
		m_chessman[m_chessmannumber].draw(pDC,true);
	/***************************边框****************************/
	CPen pen4(PS_SOLID,3,RGB(0,0,255));
	pDC->SelectObject(&pen4);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(200,50,600,550);

	/****************************出口*****************************/
	CPen pen3(PS_SOLID,4,RGB(0,255,0));
	pDC->SelectObject(&pen3);
	CBrush brush3(RGB(0,255,0));
	pDC->SelectObject(&brush3);
	pDC->Rectangle(300,550,500,600);


	/****************************其他******************************/
	CString str;
	CFont font1;
	font1.CreatePointFont(150,_T("华文行楷"));
	pDC->SelectObject(&font1);
	pDC->SetTextColor(RGB(0,0,255));
	pDC->TextOutW(360,10,_T("华容道"));

	/****************************************文本框1***************************************/
	if(m_levelnumber>0)
	{
		ASSERT((&m_static)&&m_static.GetSafeHwnd());
		CDC *pdc1=m_static.GetDC();          //获得控件DC
		CFont font2;
		font2.CreatePointFont(120,_T("华文行楷"));
		pdc1->SelectObject(&font2);
		pdc1->SetTextColor(RGB(0,255,255));
		pdc1->TextOutW(5,5,_T("关卡:"));
		pdc1->TextOutW(5,80,_T("步数:"));
		pdc1->TextOutW(5,130,_T("时间:"));

		CFont font3;
		font3.CreatePointFont(80,_T("楷体"));
		pdc1->SelectObject(&font3);
		pdc1->SetTextColor(RGB(255,0,255));
		str.Format(_T("%d"),m_level);
		pdc1->TextOutW(5,30,str);
		pdc1->TextOutW(5,55,m_levelname);
		str.Format(_T("%d"),m_stepnumber);
		pdc1->TextOutW(5,105,str);
		if(m_time<60)
			str.Format(_T("%ds"),m_time);
		else
			str.Format(_T("%dmin%ds"),m_time/60,m_time%60);
		pdc1->TextOutW(5,155,str);
		ReleaseDC(pdc1);
	}
	/****************************************文本框2***************************************/
	if(makeflag)
	{
		if(pwndstatic!=NULL)
		{
			ASSERT(pwndstatic&&pwndstatic->GetSafeHwnd());
			CDC *pdc=pwndstatic->GetDC();          //获得控件DC
			CFont font2;
			font2.CreatePointFont(120,_T("华文行楷"));
			pdc->SelectObject(&font2);
			pdc->SetTextColor(RGB(0,255,255));
			pdc->SetBkColor(pdc->GetBkColor());	//背景色
			//pdc->SetBkColor(RGB(255,153,0));
			pdc->TextOutW(5,5,_T("关卡:"));
			pdc->TextOutW(5,55,_T("名称:"));
			CFont font3;
			font3.CreatePointFont(80,_T("楷体"));
			pdc->SelectObject(&font3);
			pdc->SetTextColor(RGB(255,0,255));
			str.Format(_T("%d"),m_levelnumber+1);
			pdc->TextOutW(50,30,str);
			ReleaseDC(pdc);
		}
	}
	else
	{
		if(pwndstatic!=NULL)
		{
			ASSERT(pwndstatic&&pwndstatic->GetSafeHwnd());
			CDC *pdc=pwndstatic->GetDC();          //获得控件DC
			CFont font2;
			font2.CreatePointFont(120,_T("华文行楷"));
			pdc->SelectObject(&font2);
			pdc->SetTextColor(RGB(0,255,255));
			pdc->SetBkColor(pdc->GetBkColor());	//背景色
			//pdc->SetBkColor(RGB(255,153,0));
			pdc->TextOutW(5,5,_T("单击左键:"));
			pdc->TextOutW(5,55,_T("单击右键:"));
			pdc->TextOutW(5,105,_T("最新进度:"));
			CFont font3;
			font3.CreatePointFont(80,_T("楷体"));
			pdc->SelectObject(&font3);
			pdc->SetTextColor(RGB(255,0,255));
			pdc->TextOutW(50,30,_T("选中对象"));
			pdc->TextOutW(50,80,_T("后撤一步"));
			if(m_date1==_T(""))								//无保存进度
				pdc->TextOutW(50,130,_T("无保存进度"));
			else
			{
				pdc->TextOutW(50,130,m_date1);
				pdc->TextOutW(50,155,m_date2);
			}
			ReleaseDC(pdc);
		}
	}
}
void CHuaRongDaoView::reflesh()
{
	Invalidate();						//使客户区无效
	CWnd *pWnd=(CWnd*)GetDlgItem(1);
	pWnd->Invalidate();
	pWnd->UpdateWindow();				//使文本区1区无效
	if(pwndstatic!=NULL)
	{
		pWnd=(CWnd*)GetDlgItem(2);
		pWnd->Invalidate();
		pWnd->UpdateWindow();				//使文本区2区无效
	}
}
int CHuaRongDaoView::getchessmannumber(int x,int y)			//获得棋子序号
{
	int k;
	for(k=0;k<10;k++)
	{
		if(m_chessman[k].m_finishset)
		{
			int i=m_chessman[k].m_x;
			int j=m_chessman[k].m_y;
			int w=m_chessman[k].m_width/200;
			int h=m_chessman[k].m_height/200;
			if(i==x&&j==y)
				break;
			else if(i+w==x&&j==y)
				break;
			else if(i==x&&j+h==y)
				break;
			else if(i+w==x&&j+h==y)
				break;
		}
	}
	return k;
}
void CHuaRongDaoView::move(char d)
{
	int i=m_chessman[m_chessmannumber].m_x;
	int j=m_chessman[m_chessmannumber].m_y;
	int w=m_chessman[m_chessmannumber].m_width/200;
	int h=m_chessman[m_chessmannumber].m_height/200;
	switch(d)
	{
	case 'L':
	case 'r':	//后撤
		m_chessboard[i+w][j].empty=m_chessboard[i+w][j+h].empty=true;
		m_chessboard[i-1][j].empty=m_chessboard[i-1][j+h].empty=false;
		break;
	case 'R':
	case 'l':	//后撤
		m_chessboard[i][j].empty=m_chessboard[i][j+h].empty=true;
		m_chessboard[i+w+1][j].empty=m_chessboard[i+w+1][j+h].empty=false;
		break;
	case 'U':
	case 'd':	//后撤
		m_chessboard[i][j+h].empty=m_chessboard[i+w][j+h].empty=true;
		m_chessboard[i][j-1].empty=m_chessboard[i+w][j-1].empty=false;
		break;
	case 'D':
	case 'u':	//后撤
		m_chessboard[i][j].empty=m_chessboard[i+w][j].empty=true;
		m_chessboard[i][j+h+1].empty=m_chessboard[i+w][j+h+1].empty=false;
		break;
	default:break;
	}
}
char CHuaRongDaoView::getderection(int x,int y)				//获得方向
{
	int i=m_chessman[m_chessmannumber].m_x;
	int j=m_chessman[m_chessmannumber].m_y;
	int w=m_chessman[m_chessmannumber].m_width/200;
	int h=m_chessman[m_chessmannumber].m_height/200;
	if(x<i)					//左
	{
		/***************************判断是否可移动************************************/
		if(m_chessboard[i-1][j].empty&&m_chessboard[i-1][j+h].empty)
		{
			return 'L';
		}
	}
	else if(x>i&&i+w+1<4)					//右,不能出界
	{
		if(m_chessboard[i+w+1][j].empty&&m_chessboard[i+w+1][j+h].empty)
		{
			return 'R';
		}
	}
	if(y<j)					//上
	{
		if(m_chessboard[i][j-1].empty&&m_chessboard[i+w][j-1].empty)
		{
			return 'U';
		}
	}
	else if(y>j&&j+h+1<5)			//下
	{
		if(m_chessboard[i][j+h+1].empty&&m_chessboard[i+w][j+h+1].empty)
		{
			return 'D';
		}
	}
	return '\0';
}
void CHuaRongDaoView::setchess(int x,int y)							//摆放棋子
{
	int w=m_chessman[m_chessmannumber].m_width/200;
	int h=m_chessman[m_chessmannumber].m_height/200;
	if(m_chessboard[x][y].empty&&m_chessboard[x+w][y].empty&&m_chessboard[x][y+h].empty&&m_chessboard[x+w][y+h].empty)		//可放
	{
		dragflag=false;
		if(m_chessman[m_chessmannumber].m_finishset)
		{
			int i=m_chessman[m_chessmannumber].m_x;
			int j=m_chessman[m_chessmannumber].m_y;
			m_chessboard[i][j].empty=m_chessboard[i+w][j].empty=m_chessboard[i][j+h].empty=m_chessboard[i+w][j+h].empty=true;
		}
		else
		{
			int n=pwndlevel_list->GetCount();
			for(int i=0;i<15;i++)
			{
				if(person[i].m_chessmannumber==m_chessmannumber)
				{
					CString str;
					int j;
					for(j=0;j<n;j++)
					{
						pwndlevel_list->GetText(j,str);
						if(person[i].m_name==str)
							break;
					}
					if(j<n)
						pwndlevel_list->DeleteString(j);
				}
			}
		}
		m_chessman[m_chessmannumber].m_x=x;
		m_chessman[m_chessmannumber].m_y=y;
		m_chessman[m_chessmannumber].m_finishset=true;
		m_chessman[m_chessmannumber].m_clickflag=true;
		b3.EnableWindow();
		m_chessboard[x][y].empty=m_chessboard[x+w][y].empty=m_chessboard[x][y+h].empty=m_chessboard[x+w][y+h].empty=false;
		Ismakefinish();
	}
}
void CHuaRongDaoView::succeed()								//判断是否过关
{
	if(m_chessman[0].m_x==1&&m_chessman[0].m_y==3)
	{
		KillTimer(1);
		timeflag=false;
		//PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(),SND_RESOURCE|SND_ASYNC); 
		successflag=true;
		b2.SetWindowTextW(_T("解法收藏"));
		b4.SetWindowTextW(_T("下一关"));
		if(m_level<14)
			b4.EnableWindow();
	}
}
BOOL CHuaRongDaoView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return true;
	//return CView::OnEraseBkgnd(pDC);
}
void CHuaRongDaoView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(playflag)
	{
		int n=GetDocument()->m_movementarray.GetSize();
		m_time++;
		m_stepnumber++;
		m_chessmannumber=GetDocument()->m_movementarray.GetAt(m_time-1)->m_chessmannumber;
		m_d=GetDocument()->m_movementarray.GetAt(m_time-1)->m_d;
		move(m_d);
		m_chessman[m_chessmannumber].move(m_d);
		for(int i=0;i<10;i++)
			m_chessman[i].m_clickflag=false;
		m_chessman[m_chessmannumber].m_clickflag=true;
		if(m_stepnumber==n)
		{
			Timer(3);
			b2.EnableWindow(false);
			b3.EnableWindow(false);
		}
		reflesh();
	}
	else
	{
		m_time++;
		reflesh();
	}
	CView::OnTimer(nIDEvent);
}
int CHuaRongDaoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	/**************************************按键*************************************/
	CRect rect_button1(700,50,780,80);
	b1.Create(_T("开始游戏"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button1,this,IDB_RESTART);
	b1.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button2(700,110,780,140);
	b2.Create(_T("保存进度"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button2,this,IDB_SAVE);
	b2.ShowWindow(SW_SHOWNORMAL);
	

	CRect rect_button3(700,170,780,200);
	b3.Create(_T("载入进度"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button3,this,IDB_LOAD);
	b3.ShowWindow(SW_SHOWNORMAL);
	Iscanload();
	
	CRect rect_button4(700,230,780,260);
	b4.Create(_T("自制关卡"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button4,this,IDB_NEXT);
	b4.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button5(20,50,100,80);
	b5.Create(_T("帮助"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button5,this,IDB_HELP);
	b5.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button6(700,300,780,330);
	b6.Create(_T("选择关卡"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button6,this,IDB_LEVEL);
	b6.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button7(20,300,100,330);
	b7.Create(_T("解法"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button7,this,IDB_VIDEO);
	b7.ShowWindow(SW_SHOWNORMAL);

	m_static.Create(_T(""),WS_CHILD|SS_WHITERECT|WS_VISIBLE|WS_BORDER,CRect(610,90,690,290),this,1);

	load_level_solution();
	if(m_levelnumber>0)
	{
		m_static.ShowWindow(SW_SHOWNORMAL);
		initselect(1);
	}
	else
	{
		m_static.ShowWindow(SW_HIDE);
		initselect(0);
	}
	// TODO:  在此添加您专用的创建代码
	return 0;
}
void CHuaRongDaoView::ONRESTART() 
{
	if(playflag)
	{
		Timer(3);
		b2.EnableWindow(false);
		b3.EnableWindow();
		initselect(m_level);
		load_solution(m_level);
		Timer(1);
		reflesh();
	}
	else if(makeflag)
	{
		m_levelnumber++;
		m_level=m_levelnumber;
		pwndedit->GetWindowText(m_levelname);
		save_level(m_level);
		makeflag=false;
		b1.SetWindowTextW(_T("开始游戏"));
		b2.SetWindowTextW(_T("保存进度"));
		b3.SetWindowTextW(_T("载入进度"));
		b6.SetWindowTextW(_T("选择关卡"));
		b1.EnableWindow();
		b2.EnableWindow();
		Iscanload();
		b4.EnableWindow();
		b5.ShowWindow(SW_SHOWNORMAL);
		b7.ShowWindow(SW_SHOWNORMAL);
		m_static.ShowWindow(SW_SHOWNORMAL);
		if(pwndlevel_list!=NULL)
		{
			delete pwndlevel_list;							//删除上次生成的控件对象
			pwndlevel_list=NULL;
			b6.EnableWindow();
		}
		if(pwndedit!=NULL)
		{
			delete pwndedit;							//删除上次生成的控件对象
			pwndedit=NULL;
		}
		if(pwndstatic!=NULL)
		{
			delete pwndstatic;							//删除上次生成的控件对象
			pwndstatic=NULL;
		}
		initselect(m_level);
		reflesh();
	}
	else if(successflag)
	{
		b2.SetWindowTextW(_T("保存进度"));
		b2.EnableWindow();
		b4.SetWindowTextW(_T("自制关卡"));
		successflag=false;
		initselect(m_level);
		clearmovement();
		Timer(1);
		reflesh();
	}
	else
	{
		if(!timeflag)
		{
			b1.SetWindowTextW(_T("重新开始"));
			Timer(1);
		}
		else
		{
			Timer(3);
			b2.SetWindowTextW(_T("保存进度"));
			b2.EnableWindow();
			initselect(m_level);
			clearmovement();
			Timer(1);
		}
		reflesh();
	}
}
void CHuaRongDaoView::ONSAVE()
{
	if(playflag)					//播放		
	{
		if(pwndvideo_list!=NULL)
		{
			delete pwndvideo_list;
			pwndvideo_list=NULL;
			b7.EnableWindow();

			load_solution(m_level);
			Iscannext();
		}
		b1.EnableWindow();
		b2.EnableWindow(false);
		b3.EnableWindow();
		Timer(1);
	}		
	else if(makeflag)				//退出
	{
		makeflag=false;
		dragflag=false;
		b1.SetWindowTextW(_T("开始游戏"));
		b2.SetWindowTextW(_T("保存进度"));
		b3.SetWindowTextW(_T("载入进度"));
		b6.SetWindowTextW(_T("选择关卡"));
		b1.EnableWindow();
		b2.EnableWindow();
		Iscanload();
		b4.EnableWindow();
		b5.ShowWindow(SW_SHOWNORMAL);
		b7.ShowWindow(SW_SHOWNORMAL);
		m_static.ShowWindow(SW_SHOWNORMAL);
		if(pwndlevel_list!=NULL)
		{
			delete pwndlevel_list;							//删除上次生成的控件对象
			pwndlevel_list=NULL;
			b6.EnableWindow();
		}
		if(pwndedit!=NULL)
		{
			delete pwndedit;								//删除上次生成的控件对象
			pwndedit=NULL;
		}
		if(pwndstatic!=NULL)
		{
			delete pwndstatic;								//删除上次生成的控件对象
			pwndstatic=NULL;
		}
		initselect(m_level);
		reflesh();
	}
	else if(successflag)									//解法收藏
	{
		int j;
		for(j=0;j<m_solutionnumber;j++)
			if(psolution[j]==m_level)
				break;
		if(j==m_solutionnumber)
		{
			m_solutionnumber++;
			int *p=new int[m_solutionnumber];
			int i;
			for(i=0;i<m_solutionnumber-1;i++)
				p[i]=psolution[i];
			p[i]=m_level;
			delete [] psolution;
			psolution=NULL;
			psolution=new int[m_solutionnumber];
			for(i=0;i<m_solutionnumber;i++)
				psolution[i]=p[i];
			delete [] p;
		}
		save_solution(m_level);
		b2.EnableWindow(false);
	}
	else
	{
		save();
		b3.EnableWindow();
	}
}
void CHuaRongDaoView::ONLOAD()
{
	if(playflag)
	{
		Timer(2);
		b2.EnableWindow();
		b3.EnableWindow(false);
		reflesh();
	}
	else if(makeflag)
	{
		int x=m_chessman[m_chessmannumber].m_x;
		int y=m_chessman[m_chessmannumber].m_y;
		int w=m_chessman[m_chessmannumber].m_width/200;
		int h=m_chessman[m_chessmannumber].m_height/200;
		m_chessman[m_chessmannumber].m_finishset=false;
		m_chessman[m_chessmannumber].m_clickflag=false;
		b3.EnableWindow(false);
		m_chessboard[x][y].empty=m_chessboard[x+w][y].empty=m_chessboard[x][y+h].empty=m_chessboard[x+w][y+h].empty=true;
		for(int i=0;i<15;i++)
			if(person[i].m_chessmannumber==m_chessmannumber)
				pwndlevel_list->AddString(person[i].m_name);
		m_chessmannumber=10;
		Ismakefinish();
		reflesh();
	}
	else
	{
		Timer(3);
		load();
		b1.SetWindowTextW(_T("重新开始"));
		Timer(1);
		reflesh();
	}
}
void CHuaRongDaoView::ONNEXT()
{
	if(playflag)
	{
		m_level=Iscannext();
		Timer(3);
		b1.EnableWindow(false);
		b2.EnableWindow();
		b3.EnableWindow(false);
		Iscannext();
		initselect(m_level);
		load_solution(m_level);
		reflesh();
	}
	else if(successflag)
	{
		successflag=false;
		b1.SetWindowTextW(_T("开始游戏"));
		b2.SetWindowTextW(_T("保存进度"));
		b2.EnableWindow();
		b4.SetWindowTextW(_T("自制关卡"));
		m_level++;
		initselect(m_level);
		reflesh();
	}
	else
	{
		Timer(3);
		makeflag=true;
		m_chessmannumber=10;
		b1.SetWindowTextW(_T("确定"));
		b2.SetWindowTextW(_T("退出"));
		b3.SetWindowTextW(_T("删除人物"));
		b6.SetWindowTextW(_T("选择人物"));
		b1.EnableWindow(false);
		b3.EnableWindow(false);
		b4.EnableWindow(false);
		b5.ShowWindow(SW_HIDE);
		b7.ShowWindow(SW_HIDE);
		for(int i=0;i<10;i++)
			m_chessman[i].m_finishset=false;	
		for(int i=0;i<4;i++)
			for(int j=0;j<5;j++)
				m_chessboard[i][j].empty=true;
		if(pwndlevel_list!=NULL)
		{
			delete pwndlevel_list;							//删除上次生成的控件对象
			pwndlevel_list=NULL;
			b6.EnableWindow();
		}
		if(pwndstatic!=NULL)
		{
			delete pwndstatic;								//删除上次生成的控件对象
			pwndstatic=NULL;
			b5.EnableWindow();
		}
		pwndstatic=new CStatic;
		pwndstatic->Create(_T(""),WS_CHILD|SS_WHITERECT|WS_VISIBLE|WS_BORDER,CRect(20,90,180,170),this,2);
		pwndedit=new CEdit;
		pwndedit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER,CRect(20,170,180,200),this,IDC_EDIT);
		m_static.ShowWindow(SW_HIDE);
		reflesh();
	}
}
void CHuaRongDaoView::ONHELP()
{
	pwndstatic=new CStatic;
	((CStatic*)pwndstatic)->Create(_T(""),WS_CHILD|SS_WHITERECT|WS_VISIBLE|WS_BORDER,CRect(20,90,180,290),this,2);
	b5.EnableWindow(false);
	reflesh();
}
void CHuaRongDaoView::ONLEVEL()
{
	if(playflag)			//退出
	{
		Timer(3);
		b1.SetWindowTextW(_T("开始游戏"));
		b2.SetWindowTextW(_T("保存进度"));
		b3.SetWindowTextW(_T("载入进度"));
		b4.SetWindowTextW(_T("自制关卡"));
		b6.SetWindowTextW(_T("选择关卡"));
		b1.EnableWindow();
		b2.EnableWindow();
		Iscanload();
		b4.EnableWindow();
		b5.ShowWindow(SW_SHOWNORMAL);
		if(pwndvideo_list!=NULL)
		{
			delete pwndvideo_list;							//删除上次生成的控件对象
			pwndvideo_list=NULL;
			b7.EnableWindow();
		}
		playflag=false;
		initselect(m_level);
		reflesh();
	}
	else if(makeflag)
	{
		pwndlevel_list=new CListBox;
		pwndlevel_list->Create(WS_CHILD|WS_VISIBLE|LBS_STANDARD,CRect(610,340,780,550),this,IDC_LISTLEVEL);
		for(int i=0;i<15;i++)
			pwndlevel_list->AddString(person[i].m_name);
		b6.EnableWindow(false);
		reflesh();
	}
	else
	{
		Timer(3);
		pwndlevel_list=new CListBox;
		pwndlevel_list->Create(WS_CHILD|WS_VISIBLE|LBS_STANDARD,CRect(610,340,780,550),this,IDC_LISTLEVEL);
		CString str;
		for(int i=1;i<=m_levelnumber;i++)
		{
			str.Format(_T("%d%d"),i/10,i%10);
			pwndlevel_list->AddString(str);
		}
		b6.EnableWindow(false);
		reflesh();
	}
}
void CHuaRongDaoView::ONVIDEO()
{
	Timer(3);
	pwndvideo_list=new CListBox;
	((CListBox*)pwndvideo_list)->Create(WS_CHILD|WS_VISIBLE|LBS_STANDARD,CRect(20,340,180,550),this,IDC_LISTVIDEO);
	CString str;
	for(int i=0;i<m_solutionnumber;i++)
	{
		str.Format(_T("%d%d"),psolution[i]/10,psolution[i]%10);
		pwndvideo_list->AddString(str);
	}
	if(!playflag)
	{
		b1.SetWindowTextW(_T("重新播放"));
		b2.SetWindowTextW(_T("播放"));
		b3.SetWindowTextW(_T("暂停"));
		b4.SetWindowTextW(_T("下一关"));
		b6.SetWindowTextW(_T("退出"));
		playflag=true;
		b5.ShowWindow(SW_HIDE);
		if(pwndlevel_list!=NULL)
		{
			delete pwndlevel_list;							//删除上次生成的控件对象
			pwndlevel_list=NULL;
			b6.EnableWindow();
		}
		if(pwndstatic!=NULL)
		{
			delete pwndstatic;							//删除上次生成的控件对象
			pwndstatic=NULL;
			b5.EnableWindow();
		}
	}
	b1.EnableWindow(false);
	b2.EnableWindow();
	b3.EnableWindow(false);
	b4.EnableWindow(false);
	b7.EnableWindow(false);
	initselect(m_level);
	reflesh();
}
void CHuaRongDaoView::OnSelchangeListlevel()
{
	if(makeflag)
	{
		int n=pwndlevel_list->GetCurSel();
		if(n!=-1)
		{
			CString str;
			pwndlevel_list->GetText(n,str);
			int pos=str.Find('.');
			CString temp=str.Left(pos);
			int m=_ttoi(temp);
			if(m_chessmannumber!=10)
			{
				m_chessman[m_chessmannumber].m_clickflag=false;
				b3.EnableWindow(false);
			}
			switch(m)
			{
			case 1:m_chessmannumber=0;m_chessman[m_chessmannumber].set(200,200,Caocao);break;
			case 2:m_chessmannumber=1;m_chessman[m_chessmannumber].set(100,200,Zhangfei);break;
			case 3:m_chessmannumber=1;m_chessman[m_chessmannumber].set(200,100,Zhangfei1);break;
			case 4:m_chessmannumber=2;m_chessman[m_chessmannumber].set(100,200,Zhaoyun);break;
			case 5:m_chessmannumber=2;m_chessman[m_chessmannumber].set(200,100,Zhaoyun1);break;
			case 6:m_chessmannumber=3;m_chessman[m_chessmannumber].set(100,200,Machao);break;
			case 7:m_chessmannumber=3;m_chessman[m_chessmannumber].set(200,100,Machao1);break;
			case 8:m_chessmannumber=4;m_chessman[m_chessmannumber].set(100,200,Huangzhong);break;
			case 9:m_chessmannumber=4;m_chessman[m_chessmannumber].set(200,100,Huangzhong1);break;
			case 10:m_chessmannumber=5;m_chessman[m_chessmannumber].set(200,100,Guanyu);break;
			case 11:m_chessmannumber=5;m_chessman[m_chessmannumber].set(100,200,Guanyu1);break;
			case 12:m_chessmannumber=6;m_chessman[m_chessmannumber].set(100,100,Zu);break;
			case 13:m_chessmannumber=7;m_chessman[m_chessmannumber].set(100,100,Zu);break;
			case 14:m_chessmannumber=8;m_chessman[m_chessmannumber].set(100,100,Zu);break;
			case 15:m_chessmannumber=9;m_chessman[m_chessmannumber].set(100,100,Zu);break;
			default:break;
			}
			dragflag=false;
			m_chessman[m_chessmannumber].m_finishset=false;
			reflesh();
		}
		else
			MessageBox(_T("没有选择列表项或列表框操作失败"));
	}
	else
	{
		int n=pwndlevel_list->GetCurSel();
		if(n!=-1)
		{
			m_level=n+1;
			initselect(m_level);
			reflesh();
		}
		else
			MessageBox(_T("没有选择列表项或列表框操作失败"));
	}
}
void CHuaRongDaoView::OnSelchangeListvideo()
{
	int n=pwndvideo_list->GetCurSel();
	if(n!=-1)
	{
		m_level=psolution[n];
		initselect(m_level);
		reflesh();
	}
	else
		MessageBox(_T("没有选择列表项或列表框操作失败"));
}
void CHuaRongDaoView::OnDblclkListlevel()
{
	if((!playflag)&&(!makeflag))
	{
		delete pwndlevel_list;							//删除上次生成的控件对象
		pwndlevel_list=NULL;
		b6.EnableWindow();
		b1.SetWindowTextW(_T("开始游戏"));
		reflesh();
	}
}
void CHuaRongDaoView::OnDblclkListvideo()
{
	delete pwndvideo_list;							//删除上次生成的控件对象
	pwndvideo_list=NULL;
	b7.EnableWindow();
	
	b1.EnableWindow();
	b2.EnableWindow(false);
	b3.EnableWindow();
	Iscannext();
	load_solution(m_level);
	Timer(1);
	reflesh();
}
void CHuaRongDaoView::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		/******************************************************获取时间****************************************************************/
		SYSTEMTIME st;
		GetLocalTime(&st);
		m_date1.Format(_T("%4d-%2d-%2d"),st.wYear,st.wMonth,st.wDay);
		m_date2.Format(_T("%2d:%2d:%2d"),st.wHour,st.wMinute,st.wSecond);
		ar<<m_date1<<m_date2;
		/***************************************CMovement***************************************/
		int n=GetDocument()->m_movementarray.GetSize();
		ar<<n;
		CMovement *pmovement=NULL;
		for(int i=0;i<n;i++)
		{
			pmovement=GetDocument()->m_movementarray.GetAt(i);	
			ar<<pmovement->m_chessmannumber<<pmovement->m_d<<pmovement->m_stepnumber;								//存文件
		}
		
		/***************************************CChessman***************************************/
		for(int i=0;i<10;i++)
			ar<<m_chessman[i].m_x<<m_chessman[i].m_y<<m_chessman[i].m_width<<m_chessman[i].m_height<<m_chessman[i].m_name<<m_chessman[i].m_clickflag<<m_chessman[i].m_finishset;
		/***************************************CChessboard***************************************/
		for(int i=0;i<4;i++)
			for(int j=0;j<5;j++)
				ar<<m_chessboard[i][j].empty;

		/***************************************其他***************************************/
		ar<<m_chessmannumber<<m_d<<m_stepnumber<<m_level<<m_time;
	}
	else
	{
		ar>>m_date1>>m_date2;
		int n=clearmovement();
		ar>>n;
		for(int i=0;i<n;i++)
		{
			CMovement *pmovement=new CMovement;
			ar>>pmovement->m_chessmannumber>>pmovement->m_d>>pmovement->m_stepnumber;							//读文件
			GetDocument()->m_movementarray.Add(pmovement);
		}
		for(int i=0;i<10;i++)
			ar>>m_chessman[i].m_x>>m_chessman[i].m_y>>m_chessman[i].m_width>>m_chessman[i].m_height>>m_chessman[i].m_name>>m_chessman[i].m_clickflag>>m_chessman[i].m_finishset;
		for(int i=0;i<4;i++)
			for(int j=0;j<5;j++)
				ar>>m_chessboard[i][j].empty;
		ar>>m_chessmannumber>>m_d>>m_stepnumber>>m_level>>m_time;
	}
}
void CHuaRongDaoView::load()
{
	CFile file;
	if(file.Open(_T(".\\file1.txt"),CFile::modeRead))
	{
		CArchive ar(&file,CArchive::load);
		Serialize(ar);
		ar.Close();
		file.Close();
	}
}
void CHuaRongDaoView::save()
{
	CFile file;
	if(file.Open(_T(".\\file1.txt"),CFile::modeCreate|CFile::modeWrite))
	{
		CArchive ar(&file,CArchive::store);
		Serialize(ar);
		ar.Close();
		file.Close();
	}
}
void CHuaRongDaoView::save_solution(int level)
{
	CFile file;
	solutionfilename.Format(_T("solution%d.txt"),level);
	if(file.Open(solutionfilename,CFile::modeCreate|CFile::modeWrite))
	{
		CArchive ar(&file,CArchive::store);
		int n=GetDocument()->m_movementarray.GetSize();
		ar<<n;
		CMovement *pmovement=NULL;
		for(int i=0;i<n;i++)
		{
			pmovement=GetDocument()->m_movementarray.GetAt(i);	
			ar<<pmovement->m_chessmannumber<<pmovement->m_d<<pmovement->m_stepnumber;								//存文件
		}
		ar.Close();
		file.Close();
	}
}
void CHuaRongDaoView::load_solution(int level)
{
	CFile file;
	solutionfilename.Format(_T("solution%d.txt"),level);
	if(file.Open(solutionfilename,CFile::modeRead))
	{
		CArchive ar(&file,CArchive::load);
		int n=clearmovement();
		ar>>n;
		for(int i=0;i<n;i++)
		{
			CMovement *pmovement=new CMovement;
			ar>>pmovement->m_chessmannumber>>pmovement->m_d>>pmovement->m_stepnumber;							//读文件
			GetDocument()->m_movementarray.Add(pmovement);
		}
		ar.Close();
		file.Close();
	}
}
void  CHuaRongDaoView::save_level(int level)
{
	CFile file;
	levelfilename.Format(_T("level%d.txt"),level);
	if(file.Open(levelfilename,CFile::modeCreate|CFile::modeWrite))
	{
		CArchive ar(&file,CArchive::store);
		ar<<m_level<<m_levelname;
		for(int i=0;i<10;i++)
			ar<<m_chessman[i].m_x<<m_chessman[i].m_y<<m_chessman[i].m_width<<m_chessman[i].m_height<<m_chessman[i].m_name;
		for(int i=0;i<4;i++)
			for(int j=0;j<5;j++)
				ar<<m_chessboard[i][j].empty;
		ar.Close();
		file.Close();
	}
}
void  CHuaRongDaoView::load_level(int level)	
{
	CFile file;
	levelfilename.Format(_T("level%d.txt"),level);
	if(file.Open(levelfilename,CFile::modeRead))
	{
		CArchive ar(&file,CArchive::load);
		ar>>m_level>>m_levelname;
		for(int i=0;i<10;i++)
		{
			ar>>m_chessman[i].m_x>>m_chessman[i].m_y>>m_chessman[i].m_width>>m_chessman[i].m_height>>m_chessman[i].m_name;
			m_chessman[i].m_clickflag=false;
			m_chessman[i].m_finishset=true;
		}
		for(int i=0;i<4;i++)
			for(int j=0;j<5;j++)
				ar>>m_chessboard[i][j].empty;
		ar.Close();
		file.Close();
	}
}
void CHuaRongDaoView::save_level_solution()
{
	CFile file;
	if(file.Open(_T(".\\level_solution.txt"),CFile::modeCreate|CFile::modeWrite))
	{
		CArchive ar(&file,CArchive::store);
		ar<<m_levelnumber<<m_solutionnumber;
		for(int i=0;i<m_solutionnumber;i++)
			ar<<psolution[i];
		delete [] psolution;
		ar.Close();
		file.Close();
	}
}
void CHuaRongDaoView::load_level_solution()
{
	CFile file;
	if(file.Open(_T(".\\level_solution.txt"),CFile::modeRead|CFile::modeCreate|CFile::modeNoTruncate))
	{
		CFileStatus status;  
		file.GetStatus(_T(".\\level_solution.txt"),status);
		long lSizeOfFile;  
		lSizeOfFile=status.m_size; 
		if(lSizeOfFile)						//非空文件
		{
			CArchive ar(&file,CArchive::load);
			ar>>m_levelnumber>>m_solutionnumber;
			psolution=new int[m_solutionnumber];
			for(int i=0;i<m_solutionnumber;i++)
				ar>>psolution[i];
			ar.Close();
		}
		else
		{
			m_levelnumber=0;
			m_solutionnumber=0;
			psolution=NULL;
		}
		file.Close();
	}
}
void CHuaRongDaoView::Iscanload()
{
	CFile file;
	if(file.Open(_T("file1.txt"),CFile::modeRead|CFile::modeCreate|CFile::modeNoTruncate))
	{
		CFileStatus status;  
		file.GetStatus(_T("file1.txt"),status);
		long lSizeOfFile;  
		lSizeOfFile=status.m_size; 
		if(lSizeOfFile)						//非空文件
		{
			CArchive ar(&file,CArchive::load);
			ar>>m_date1>>m_date2;
			ar.Close();
			file.Close();
			b3.EnableWindow();
		}
		else
		{
			file.Close();
			b3.EnableWindow(false);
		}
	}
}
int CHuaRongDaoView::Iscannext()
{
	int i;
	for(i=0;i<m_solutionnumber;i++)
		if(psolution[i]==m_level)
			break;
	if(i<m_solutionnumber-1)
		b4.EnableWindow();
	else
		b4.EnableWindow(false);
	return psolution[i+1];
}
void CHuaRongDaoView::Ismakefinish()
{
	int i;
	for(i=0;i<10;i++)
	{
		if(!m_chessman[i].m_finishset)
			break;
	}
	if(i==10)				//自制完成
		b1.EnableWindow();
	else
		b1.EnableWindow(false);
}
void CHuaRongDaoView::OnDestroy()
{
	CView::OnDestroy();
	clearmovement();
	save_level_solution();
	// TODO: 在此处添加消息处理程序代码
}
int CHuaRongDaoView::clearmovement()
{
	int n=GetDocument()->m_movementarray.GetSize();
	for(int i=0;i<n;i++)
		delete GetDocument()->m_movementarray.GetAt(i);
	GetDocument()->m_movementarray.RemoveAll();
	return n;
}
void CHuaRongDaoView::Timer(int n)
{
	switch(n)
	{
	case 1:
		if(!timeflag)//播放
		{
			SetTimer(1,1000,NULL);
			timeflag=true;
		}
		break;
	case 2:
		if(timeflag)//暂停
		{
			KillTimer(1);
			timeflag=false;
		}
		break;
	case 3:
		if(timeflag)//退出
		{
			KillTimer(1);
			timeflag=false;
		}
		break;
	default:break;
	}
}