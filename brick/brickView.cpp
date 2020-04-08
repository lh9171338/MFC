
// brickView.cpp : CbrickView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "brick.h"
#endif

#include "brickDoc.h"
#include "brickView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CbrickView

IMPLEMENT_DYNCREATE(CbrickView, CView)

BEGIN_MESSAGE_MAP(CbrickView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CbrickView::OnFilePrintPreview)
	ON_BN_CLICKED(IDB_L,ONLDOWN)
	ON_BN_CLICKED(IDB_R,ONRDOWN)
	ON_BN_CLICKED(IDB_TURN,ONTURNDOWN)
	ON_BN_CLICKED(IDB_D,ONDDOWN)
	ON_BN_CLICKED(IDB_START,ONSTARTDOWN)
	ON_BN_CLICKED(IDB_STOP,ONSTOPDOWN)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CbrickView 构造/析构

CbrickView::CbrickView()
{
	// TODO: 在此处添加构造代码
	bagin=first=false;
	life=true;
	m_score=m_type=0;
	m_hard=1000;
	init();
}

CbrickView::~CbrickView()
{
}

BOOL CbrickView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CbrickView 绘制

void CbrickView::OnDraw(CDC* pDC)
{
	CbrickDoc* pDoc = GetDocument();
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

	draw(&MemDC);												//必须用指针或引用

	pDC->BitBlt(0,0,r.right,r.bottom,&MemDC,0,0,SRCCOPY); 
	MemBitmap.DeleteObject(); 
	MemDC.DeleteDC(); 
	// TODO: 在此处为本机数据添加绘制代码
}


// CbrickView 打印


void CbrickView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CbrickView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CbrickView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CbrickView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CbrickView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CbrickView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CbrickView 诊断

#ifdef _DEBUG
void CbrickView::AssertValid() const
{
	CView::AssertValid();
}

void CbrickView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CbrickDoc* CbrickView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CbrickDoc)));
	return (CbrickDoc*)m_pDocument;
}
#endif //_DEBUG


// CbrickView 消息处理程序


int CbrickView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO:  在此添加您专用的创建代码
	CRect rect_button1(300,200,340,230);
	b1.Create(_T("左"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button1,this,IDB_L);
	b1.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button2(380,200,420,230);
	b2.Create(_T("右"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button2,this,IDB_R);
	b2.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button3(340,170,380,200);
	b3.Create(_T("旋转"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button3,this,IDB_TURN);
	b3.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button4(340,230,380,260);
	b4.Create(_T("下"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button4,this,IDB_D);
	b4.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button5(440,170,500,200);
	b5.Create(_T("开始"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button5,this,IDB_START);
	b5.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button6(440,230,500,260);
	b6.Create(_T("暂停"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button6,this,IDB_STOP);
	b6.ShowWindow(SW_SHOWNORMAL);

	return 0;
}


void CbrickView::OnDestroy()
{
	CView::OnDestroy();
	KillTimer(1);
	// TODO: 在此处添加消息处理程序代码
}

void CbrickView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(first)
	{
		d='D';
		move();
	}
	CView::OnTimer(nIDEvent);
}
void CbrickView::init()
{
	int i,j;
	for(i=0;i<L;i++)
	{
		for(j=0;j<H;j++)
		{
			M[i][j].m_color=RGB(255,255,255);
			M[i][j].m_p.x=i*20;
			M[i][j].m_p.y=20*j;
			M[i][j].brick=M[i][j].moveb=false;
		}
	}
	for(i=0;i<H;i++)
		m_num[i]=0;
}
void CbrickView::move()
{
	m_move=false;
	switch(d)
	{
	case 'L':
		B.I1--;
		B.I2--;
		B.I3--;
		B.I4--;
		if((B.I1>-1&&B.I2>-1&&B.I3>-1&&B.I4>-1)&&(!M[B.I1][B.J1].brick&&!M[B.I2][B.J2].brick&&!M[B.I3][B.J3].brick&&!M[B.I4][B.J4].brick))
		{
			B.I1++;
			B.I2++;
			B.I3++;
			B.I4++;
			//M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I3][B.J3].moveb=M[B.I4][B.J4].moveb=false;
			M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I3][B.J3].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
			B.I1--;
			B.I2--;
			B.I3--;
			B.I4--;
			//M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I3][B.J3].moveb=M[B.I4][B.J4].moveb=true;
			M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I3][B.J3].m_color=M[B.I4][B.J4].m_color=B.m_color;
			m_move=true;
		}
		else
		{
			B.I1++;
			B.I2++;
			B.I3++;
			B.I4++;
		}
		break;
	case 'R':
		B.I1++;
		B.I2++;
		B.I3++;
		B.I4++;
		if((B.I1<L&&B.I2<L&&B.I3<L&&B.I4<L)&&(!M[B.I1][B.J1].brick&&!M[B.I2][B.J2].brick&&!M[B.I3][B.J3].brick&&!M[B.I4][B.J4].brick))
		{
			B.I1--;
			B.I2--;
			B.I3--;
			B.I4--;
			//M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I3][B.J3].moveb=M[B.I4][B.J4].moveb=false;
			M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I3][B.J3].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
			B.I1++;
			B.I2++;
			B.I3++;
			B.I4++;
			//M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I3][B.J3].moveb=M[B.I4][B.J4].moveb=true;
			M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I3][B.J3].m_color=M[B.I4][B.J4].m_color=B.m_color;
			m_move=true;
		}
		else
		{
			B.I1--;
			B.I2--;
			B.I3--;
			B.I4--;
		}
		break;
	case 'D':
		B.J1++;
		B.J2++;
		B.J3++;
		B.J4++;
		if((B.J1<H&&B.I2<H&&B.J3<H&&B.J4<H)&&(!M[B.I1][B.J1].brick&&!M[B.I2][B.J2].brick&&!M[B.I3][B.J3].brick&&!M[B.I4][B.J4].brick))
		{
			B.J1--;
			B.J2--;
			B.J3--;
			B.J4--;
			//M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I3][B.J3].moveb=M[B.I4][B.J4].moveb=false;
			M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I3][B.J3].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
			B.J1++;
			B.J2++;
			B.J3++;
			B.J4++;
			//M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I3][B.J3].moveb=M[B.I4][B.J4].moveb=true;
			M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I3][B.J3].m_color=M[B.I4][B.J4].m_color=B.m_color;
			m_move=true;
		}
		else
		{
			B.J1--;
			B.J2--;
			B.J3--;
			B.J4--;
			//M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I3][B.J3].moveb=M[B.I4][B.J4].moveb=false;
			M[B.I1][B.J1].brick=M[B.I2][B.J2].brick=M[B.I3][B.J3].brick=M[B.I4][B.J4].brick=true;							//走到底了
			m_num[B.J1]++;
			m_num[B.J2]++;
			m_num[B.J3]++;
			m_num[B.J4]++;
			full();		
			pro();
		}
		break;
	default:break;
	}
	if(m_move)
		GetDocument()->UpdateAllViews(NULL);
}
void CbrickView::draw(CDC *pDC)
{
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	pDC->SelectObject(&pen);
	int i,j;
	for(i=0;i<L;i++)
	{
		for(j=0;j<H;j++)
		{
			CBrush brush(M[i][j].m_color);
			pDC->SelectObject(&brush);
			pDC->Rectangle(M[i][j].m_p.x,M[i][j].m_p.y,M[i][j].m_p.x+20,M[i][j].m_p.y+20);
		}
	}
	CPen pen1(PS_SOLID,1,RGB(255,0,0));
	pDC->SelectObject(&pen1);
	pDC->MoveTo(0,60);
	pDC->LineTo(L*20,60);
	pDC->SelectObject(&pen);
	CBrush brush(RGB(255,255,255));
	pDC->SelectObject(&brush);
	pDC->Rectangle(300,0,380,80);
	switch(m_type)
	{
	case 1:
		{
		CBrush brush(RGB(255,0,0));
		pDC->SelectObject(&brush);
		pDC->Rectangle(320,20,340,40);
		pDC->Rectangle(340,20,360,40);
		pDC->Rectangle(320,40,340,60);
		pDC->Rectangle(340,40,360,60);
		}
		break;
	case 2:
		{
		CBrush brush(RGB(0,255,0));
		pDC->SelectObject(&brush);
		pDC->Rectangle(320,20,340,40);
		pDC->Rectangle(340,20,360,40);
		pDC->Rectangle(360,40,380,60);
		pDC->Rectangle(340,40,360,60);
		}
		break;
	case 3:
		{
		CBrush brush(RGB(0,0,255));
		pDC->SelectObject(&brush);
		pDC->Rectangle(360,20,380,40);
		pDC->Rectangle(340,20,360,40);
		pDC->Rectangle(320,40,340,60);
		pDC->Rectangle(340,40,360,60);
		}
		break;
	case 4:
		{
		CBrush brush(RGB(255,0,255));
		pDC->SelectObject(&brush);
		pDC->Rectangle(320,20,340,40);
		pDC->Rectangle(340,20,360,40);
		pDC->Rectangle(320,40,340,60);
		pDC->Rectangle(360,20,380,40);
		}
		break;
	case 5:
		{
		CBrush brush(RGB(255,255,0));
		pDC->SelectObject(&brush);
		pDC->Rectangle(320,20,340,40);
		pDC->Rectangle(340,20,360,40);
		pDC->Rectangle(300,20,320,40);
		pDC->Rectangle(340,40,360,60);
		}
		break;
	case 6:
		{
		CBrush brush(RGB(0,255,255));
		pDC->SelectObject(&brush);
		pDC->Rectangle(300,20,320,40);
		pDC->Rectangle(320,20,340,40);
		pDC->Rectangle(340,20,360,40);
		pDC->Rectangle(360,20,380,40);
		}
		break;
	case 7:
		{
		CBrush brush(RGB(0,200,100));
		pDC->SelectObject(&brush);
		pDC->Rectangle(320,20,340,40);
		pDC->Rectangle(340,20,360,40);
		pDC->Rectangle(360,20,380,40);
		pDC->Rectangle(340,40,360,60);
		}
		break;
	default:break;
	}
	CString str;
	str.Format(_T("得分:%d"),m_score);
	pDC->SetTextColor(RGB(255,0,255));
	pDC->TextOutW(300,100,str);
	str.Format(_T("难度:%d"),m_score/25);
	pDC->TextOutW(300,125,str);
	if(!life)
		pDC->TextOutW(500,150,_T("game over"));
	if(bagin)
	{
		CBrush brush1(RGB(255,0,0));
		pDC->SelectObject(&brush1);
		pDC->Rectangle(520,170,560,200);
		CBrush brush2(RGB(0,255,0));
		pDC->SelectObject(&brush2);
		pDC->Rectangle(520,230,560,260);
	}
	else
	{
		CBrush brush1(RGB(0,255,0));
		pDC->SelectObject(&brush1);
		pDC->Rectangle(520,170,560,200);
		CBrush brush2(RGB(255,0,0));
		pDC->SelectObject(&brush2);
		pDC->Rectangle(520,230,560,260);
	}
}
void CbrickView::pro()
{
	B.m_type=m_type;
	srand(time(NULL));
	m_type=rand()%7+1;
	switch(B.m_type)
	{
	case 1:B.I1=5;
		B.I2=6;
		B.I3=5;
		B.I4=6;
		B.J1=1;
		B.J2=1;
		B.J3=2;
		B.J4=2;
		B.m_color=RGB(255,0,0);
		break;
	case 2:B.I1=4;
		B.I2=5;
		B.I3=5;
		B.I4=6;
		B.J1=1;
		B.J2=1;
		B.J3=2;
		B.J4=2;
		B.m_color=RGB(0,255,0);
		break;
	case 3:B.I1=6;
		B.I2=5;
		B.I3=5;
		B.I4=4;
		B.J1=1;
		B.J2=1;
		B.J3=2;
		B.J4=2;
		B.m_color=RGB(0,0,255);
		break;
	case 4:B.I1=4;
		B.I2=4;
		B.I3=5;
		B.I4=6;
		B.J1=1;
		B.J2=2;
		B.J3=1;
		B.J4=1;
		B.m_color=RGB(255,0,255);
		break;
	case 5:B.I1=6;
		B.I2=6;
		B.I3=5;
		B.I4=4;
		B.J1=1;
		B.J2=2;
		B.J3=1;
		B.J4=1;
		B.m_color=RGB(255,255,0);
		break;
	case 6:B.I1=7;
		B.I2=6;
		B.I3=5;
		B.I4=4;
		B.J1=1;
		B.J2=1;
		B.J3=1;
		B.J4=1;
		B.m_color=RGB(0,255,255);
		break;
	case 7:B.I1=4;
		B.I2=5;
		B.I3=5;
		B.I4=6;
		B.J1=2;
		B.J2=2;
		B.J3=1;
		B.J4=2;
		B.m_color=RGB(0,200,100);
		break;
	default:break;
	}
	B.hang=true;
	//M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I3][B.J3].moveb=M[B.I4][B.J4].moveb=true;
	M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I3][B.J3].m_color=M[B.I4][B.J4].m_color=B.m_color;
}
int CbrickView::turnl()
{
	//左旋
	int I1=B.I1,I2=B.I2,I4=B.I4;			//很重要
	B.I1=B.J1-B.J3+B.I3;
	B.J1=-(I1-B.I3)+B.J3;
	B.I2=B.J2-B.J3+B.I3;
	B.J2=-(I2-B.I3)+B.J3;
	B.I4=B.J4-B.J3+B.I3;
	B.J4=-(I4-B.I3)+B.J3;
	if(B.I1>-1&&B.I1<L&&B.I2>-1&&B.I2<L&&B.I4>-1&&B.I4<L)
	{
		if(!M[B.I1][B.J1].brick&&!M[B.I2][B.J2].brick&&!M[B.I4][B.J4].brick)
			return 1;
	}
	turnr();
	return 0;
}
int CbrickView::turnr()
{
	//右旋
	int I1=B.I1,I2=B.I2,I4=B.I4;			//很重要
	B.I1=-(B.J1-B.J3)+B.I3;
	B.J1=I1-B.I3+B.J3;
	B.I2=-(B.J2-B.J3)+B.I3;
	B.J2=I2-B.I3+B.J3;
	B.I4=-(B.J4-B.J3)+B.I3;
	B.J4=I4-B.I3+B.J3;
	if(B.I1>-1&&B.I1<L&&B.I2>-1&&B.I2<L&&B.I4>-1&&B.I4<L)
	{
		if(!M[B.I1][B.J1].brick&&!M[B.I2][B.J2].brick&&!M[B.I4][B.J4].brick)
			return 1;
	}
	turnl();
	return 0;
}
void CbrickView::full()
{
	if(m_num[2]>0)
	{
		life=false;
		KillTimer(1);
	}
	else
	{
		if(m_num[B.J1]==L)
		{
			int i,j;
			for(j=B.J1;m_num[j]>0;j--)
			{
				for(i=0;i<L;i++)
				{
					M[i][j].brick=M[i][j-1].brick;
					M[i][j].m_color=M[i][j-1].m_color;
				}
				m_num[j]=m_num[j-1];
			}
			B.J2++;
			B.J3++;
			B.J4++;
			m_score+=10;
		}
		if(B.J2<H&&m_num[B.J2]==L)
		{
			int i,j;
			for(j=B.J2;m_num[j]>0;j--)
			{
				for(i=0;i<L;i++)
				{
					M[i][j].brick=M[i][j-1].brick;
					M[i][j].m_color=M[i][j-1].m_color;
				}
				m_num[j]=m_num[j-1];
			}
			B.J3++;
			B.J4++;
			m_score+=10;
		}
		if(B.J3<H&&m_num[B.J3]==L)
		{
			int i,j;
			for(j=B.J3;m_num[j]>0;j--)
			{
				for(i=0;i<L;i++)
				{
					M[i][j].brick=M[i][j-1].brick;
					M[i][j].m_color=M[i][j-1].m_color;
				}
				m_num[j]=m_num[j-1];
			}
			B.J4++;
			m_score+=10;
		}
		if(B.J4<H&&m_num[B.J4]==L)
		{
			int i,j;
			for(j=B.J4;m_num[j]>0;j--)
			{
				for(i=0;i<L;i++)
				{
					M[i][j].brick=M[i][j-1].brick;
					M[i][j].m_color=M[i][j-1].m_color;
				}
				m_num[j]=m_num[j-1];
			}
			m_score+=10;
		}
		m_hard=1000-m_score/25*100;
	}
}

void CbrickView::ONLDOWN()
{
	if(bagin&&life)
	{
		d='L';
		move();
	}
	this->SetFocus();
	this->GetFocus();
}
void CbrickView::ONRDOWN()
{
	if(bagin&&life)
	{
		d='R';
		move();
	}	
	this->SetFocus();
	this->GetFocus();
}
void CbrickView::ONTURNDOWN()
{
	if(bagin&&life)
	{
		switch(B.m_type)
		{
		case 1:break;
		case 2:
		case 6:if(B.hang)
			   {
				   if(turnr())
				   {
						 turnl();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=false;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
						 turnr();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=true;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=B.m_color;
						 B.hang=false;
						 GetDocument()->UpdateAllViews(NULL);
				   }
			   }
			   else
			   {
					if(turnl())
				   {
						 turnr();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=false;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
						 turnl();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=true;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=B.m_color;
						 B.hang=true;
						 GetDocument()->UpdateAllViews(NULL);
				   } 
			   }
			   break;
		case 3:
			if(!B.hang)
			   {
				   if(turnr())
				   {
						 turnl();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=false;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
						 turnr();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=true;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=B.m_color;
						 B.hang=true;
						 GetDocument()->UpdateAllViews(NULL);
				   }
			   }
			   else
			   {
					if(turnl())
				   {
						 turnr();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=false;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
						 turnl();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=true;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=B.m_color;
						 B.hang=false;
						 GetDocument()->UpdateAllViews(NULL);
				   } 
			   }
			   break;

		case 4:
		case 5:
		case 7:if(turnr())
			{
					 turnl();
					 //M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=false;
					 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
					 turnr();
					// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=true;
					 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=B.m_color;
					 GetDocument()->UpdateAllViews(NULL);
			}
			break;
		default:break;
		}
	}
	this->SetFocus();
	this->GetFocus();
}
void CbrickView::ONDDOWN()
{
	if(bagin&&life)
	{
		d='D';
		move();
	}
	this->SetFocus();
	this->GetFocus();
}
void CbrickView::ONSTARTDOWN()
{
	if(!bagin&&life)
	{
		SetTimer(1,m_hard ,NULL);
		bagin=true;
		if(!first)
		{
			srand(time(NULL));
			m_type=rand()%7+1;
			pro();
			first=true;
		}
		GetDocument()->UpdateAllViews(NULL);
	}
	this->SetFocus();
	this->GetFocus();
}
void CbrickView::ONSTOPDOWN()
{
	if(bagin&&life)
	{
		KillTimer(1);
		bagin=false;
	}
	this->SetFocus();
	this->GetFocus();
}



void CbrickView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nChar==VK_LEFT)
	{
		if(bagin&&life)
		{
			d='L';
			move();
		}
	}
	else if(nChar==VK_RIGHT)
	{
		if(bagin&&life)
		{
			d='R';
			move();
		}
	}
	else if(nChar==VK_DOWN)
	{
		if(bagin&&life)
		{
			d='D';
			move();
		}
	}
	else if(nChar==VK_UP)
	{
		if(bagin&&life)
		{
		switch(B.m_type)
		{
		case 1:break;
		case 2:
		case 6:if(B.hang)
			   {
				   if(turnr())
				   {
						 turnl();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=false;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
						 turnr();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=true;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=B.m_color;
						 B.hang=false;
						 GetDocument()->UpdateAllViews(NULL);
				   }
			   }
			   else
			   {
					if(turnl())
				   {
						 turnr();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=false;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
						 turnl();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=true;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=B.m_color;
						 B.hang=true;
						 GetDocument()->UpdateAllViews(NULL);
				   } 
			   }
			   break;
		case 3:
			if(!B.hang)
			   {
				   if(turnr())
				   {
						 turnl();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=false;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
						 turnr();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=true;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=B.m_color;
						 B.hang=true;
						 GetDocument()->UpdateAllViews(NULL);
				   }
			   }
			   else
			   {
					if(turnl())
				   {
						 turnr();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=false;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
						 turnl();
						// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=true;
						 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=B.m_color;
						 B.hang=false;
						 GetDocument()->UpdateAllViews(NULL);
				   } 
			   }
			   break;

		case 4:
		case 5:
		case 7:if(turnr())
			{
					 turnl();
					 //M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=false;
					 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=RGB(255,255,255);
					 turnr();
					// M[B.I1][B.J1].moveb=M[B.I2][B.J2].moveb=M[B.I4][B.J4].moveb=true;
					 M[B.I1][B.J1].m_color=M[B.I2][B.J2].m_color=M[B.I4][B.J4].m_color=B.m_color;
					 GetDocument()->UpdateAllViews(NULL);
			}
			break;
		default:break;
		}
		}	
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CbrickView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return true;
	//return CView::OnEraseBkgnd(pDC);
}
