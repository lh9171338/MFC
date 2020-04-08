
// boxView.cpp : CboxView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "box.h"
#endif

#include "boxDoc.h"
#include "boxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CboxView

IMPLEMENT_DYNCREATE(CboxView, CView)

BEGIN_MESSAGE_MAP(CboxView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CboxView::OnFilePrintPreview)
	ON_BN_CLICKED(IDB_L,ONLDOWN)
	ON_BN_CLICKED(IDB_R,ONRDOWN)
	ON_BN_CLICKED(IDB_U,ONUDOWN)
	ON_BN_CLICKED(IDB_D,ONDDOWN)
	ON_BN_CLICKED(IDB_BACK,ONBACKDOWN)
	ON_BN_CLICKED(IDB_RSTART,ONRSTARTDOWN)
	ON_BN_CLICKED(IDB_NEXT,ONNEXTDOWN)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CboxView 构造/析构

CboxView::CboxView()
{
	// TODO: 在此处添加构造代码
	stepnum=0;
	success=false;
}
void CboxView::set(int test)
{
	stepnum=0;
	m_wayarray.RemoveAll();
	success=false;
	switch(test)
	{
	case 1:init1();break;
	case 2:init2();break;
	default:break;
	}
	CboxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UpdateAllViews(NULL);
}
CboxView::~CboxView()
{
}

BOOL CboxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CboxView 绘制

void CboxView::OnDraw(CDC* pDC)
{
	CboxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CPen pen1(PS_SOLID,1,RGB(0,0,255));
	pDC->SelectObject(&pen1);
	pDC->Rectangle(0,0,L*20,W*20);
	int i,j;
	for(i=0;i<L;i++)
	{
		for(j=0;j<W;j++)
		{
			CPen pen(PS_SOLID,1,RGB(0,0,0));
			pDC->SelectObject(&pen);
			if(map[i][j].wall)
			{
				CBrush brush(RGB(0,0,255));
				pDC->SelectObject(&brush);
				pDC->Rectangle(map[i][j].p.x,map[i][j].p.y,map[i][j].p.x+20,map[i][j].p.y+20);
			}
			else if(map[i][j].place)
			{
				CBrush brush(RGB(0,255,0));
				pDC->SelectObject(&brush);
				pDC->Rectangle(map[i][j].p.x,map[i][j].p.y,map[i][j].p.x+20,map[i][j].p.y+20);
			}
			else
			{
				CBrush brush(RGB(255,255,255));
				pDC->SelectObject(&brush);
				pDC->Rectangle(map[i][j].p.x,map[i][j].p.y,map[i][j].p.x+20,map[i][j].p.y+20);
			}
			if(map[i][j].box)
			{
				CPen pen(PS_SOLID,1,RGB(255,0,255));
				pDC->SelectObject(&pen);
				pDC->MoveTo(map[i][j].p.x+2,map[i][j].p.y+7);
				pDC->LineTo(map[i][j].p.x+2,map[i][j].p.y+17);
				pDC->LineTo(map[i][j].p.x+12,map[i][j].p.y+17);
				pDC->LineTo(map[i][j].p.x+12,map[i][j].p.y+7);
				pDC->LineTo(map[i][j].p.x+2,map[i][j].p.y+7);
				pDC->MoveTo(map[i][j].p.x+2,map[i][j].p.y+7);
				pDC->LineTo(map[i][j].p.x+7,map[i][j].p.y+2);
				pDC->LineTo(map[i][j].p.x+17,map[i][j].p.y+2);
				pDC->LineTo(map[i][j].p.x+17,map[i][j].p.y+12);
				pDC->LineTo(map[i][j].p.x+12,map[i][j].p.y+17);
				pDC->MoveTo(map[i][j].p.x+12,map[i][j].p.y+7);
				pDC->LineTo(map[i][j].p.x+17,map[i][j].p.y+2);
			}
		}
	}
	CBrush brush1(RGB(0,255,0));
	pDC->SelectObject(&brush1);
	pDC->Ellipse(map[I][J].p.x+8,map[I][J].p.y+2,map[I][J].p.x+12,map[I][J].p.y+6);
	pDC->Rectangle(map[I][J].p.x+7,map[I][J].p.y+6,map[I][J].p.x+13,map[I][J].p.y+12);
	pDC->Rectangle(map[I][J].p.x+3,map[I][J].p.y+6,map[I][J].p.x+7,map[I][J].p.y+5);
	pDC->Rectangle(map[I][J].p.x+14,map[I][J].p.y+6,map[I][J].p.x+18,map[I][J].p.y+5);
	pDC->Rectangle(map[I][J].p.x+7,map[I][J].p.y+12,map[I][J].p.x+9,map[I][J].p.y+18);
	pDC->Rectangle(map[I][J].p.x+11,map[I][J].p.y+12,map[I][J].p.x+13,map[I][J].p.y+18);
	CString str;
	str.Format(_T("步数：%d"),stepnum);
	pDC->SetTextColor(RGB(255,0,255));
	pDC->TextOutW(500,25,str);
	str.Format(_T("关卡：%d"),test);
	pDC->SetTextColor(RGB(255,0,255));
	pDC->TextOutW(500,52,str);
	if(stepnum)
	{
		CBrush brush(RGB(0,255,0));
		pDC->SelectObject(&brush);
		pDC->Rectangle(760,160,800,190);
	}
	else
	{
		CBrush brush(RGB(255,0,0));
		pDC->SelectObject(&brush);
		pDC->Rectangle(760,160,800,190);
	}
	if(stepnum)
	{
		CBrush brush(RGB(0,255,0));
		pDC->SelectObject(&brush);
		pDC->Rectangle(760,200,800,230);
	}
	else
	{
		CBrush brush(RGB(255,0,0));
		pDC->SelectObject(&brush);
		pDC->Rectangle(760,200,800,230);
	}
	if(success)
	{
		pDC->SetTextColor(RGB(255,0,255));
		pDC->TextOutW(500,75,_T("you succeed"));
		CBrush brush(RGB(0,255,0));
		pDC->SelectObject(&brush);
		pDC->Rectangle(760,240,800,270);
	}
	else
	{
		CBrush brush(RGB(255,0,0));
		pDC->SelectObject(&brush);
		pDC->Rectangle(760,240,800,270);
	}
	// TODO: 在此处为本机数据添加绘制代码
}


// CboxView 打印


void CboxView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CboxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CboxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CboxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CboxView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CboxView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CboxView 诊断

#ifdef _DEBUG
void CboxView::AssertValid() const
{
	CView::AssertValid();
}

void CboxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CboxDoc* CboxView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CboxDoc)));
	return (CboxDoc*)m_pDocument;
}
#endif //_DEBUG


// CboxView 消息处理程序


int CboxView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rect_button1(500,200,540,230);
	b1.Create(_T("左"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button1,this,IDB_L);
	b1.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button2(580,200,620,230);
	b2.Create(_T("右"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button2,this,IDB_R);
	b2.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button3(540,160,580,190);
	b3.Create(_T("上"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button3,this,IDB_U);
	b3.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button4(540,240,580,270);
	b4.Create(_T("下"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button4,this,IDB_D);
	b4.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button5(640,160,720,190);
	b5.Create(_T("后退"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button5,this,IDB_BACK);
	b5.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button6(640,200,720,230);
	b6.Create(_T("重新开始"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button6,this,IDB_RSTART);
	b6.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button7(640,240,720,270);
	b7.Create(_T("下一关"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button7,this,IDB_NEXT);
	b7.ShowWindow(SW_SHOWNORMAL);
	test=1;
	init1();
	return 0;
}
void CboxView::ONLDOWN()
{
	d='L';
	move();
}
void CboxView::ONRDOWN()
{
	d='R';
	move();
}
void CboxView::ONUDOWN()
{
	d='U';
	move();
}
void CboxView::ONDDOWN()
{
	d='D';
	move();
}
void CboxView::ONRSTARTDOWN()
{
	if(stepnum)
		set(test);
}
void CboxView::ONBACKDOWN()
{
	if(stepnum)
	{
		stepnum--;
		char m_d=m_wayarray.GetAt(stepnum)->m_d;
		bool m_boxmove=m_wayarray.GetAt(stepnum)->m_boxmove;
		switch(m_d)
		{
		case 'L':I++;
				if(m_boxmove)	
				{
					map[I-2][J].box=false;
					map[I-1][J].box=true;
					if(map[I-2][J].place==true&&map[I-1][J].place==false)
						 atplacenum--;
					else if(map[I-2][J].place==false&&map[I-1][J].place==true)
						 atplacenum++;
				 }
				break;
		case 'R':I--;
			if(m_boxmove)	
			{
				map[I+2][J].box=false;
				map[I+1][J].box=true;
				if(map[I+2][J].place==true&&map[I+1][J].place==false)
					 atplacenum--;
				else if(map[I+2][J].place==false&&map[I+1][J].place==true)
					 atplacenum++;
			 }
			break;
		case 'U':J++;
			if(m_boxmove)	
			{
				map[I][J-2].box=false;
				map[I][J-1].box=true;
				if(map[I][J-2].place==true&&map[I][J-1].place==false)
					 atplacenum--;
				else if(map[I][J-2].place==false&&map[I][J-1].place==true)
					 atplacenum++;
			 }
			 break;
		case 'D':J--;
			if(m_boxmove)	
			{
				map[I][J+2].box=false;
				map[I][J+1].box=true;
				if(map[I][J+2].place==true&&map[I][J+1].place==false)
					 atplacenum--;
				else if(map[I][J+2].place==false&&map[I][J+1].place==true)
					 atplacenum++;
			 }
			break;
		default:break;
		}
		m_wayarray.RemoveAt(stepnum);
		CboxDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		pDoc->UpdateAllViews(NULL);
	}
}
void CboxView::ONNEXTDOWN()
{
	if(success)
	{
		test++;
		set(test);
	}
}
void CboxView::init1()
{
	I=J=4;
	L=W=8;
	BOXNUM=4;
	atplacenum=0;
	int i,j;
	for(i=0;i<L;i++)
	{
		for(j=0;j<W;j++)
		{
			map[i][j].wall=map[i][j].box=map[i][j].place=false;
			map[i][j].p.x=i*20;
			map[i][j].p.y=j*20;
		}
	}
    map[0][4].wall=map[0][3].wall=map[1][3].wall=map[2][3].wall=map[2][2].wall=map[2][1].wall=map[2][0].wall=map[3][0].wall=map[4][0].wall=map[4][1].wall=true;
	map[4][2].wall=map[5][2].wall=map[6][2].wall=map[7][2].wall=map[7][3].wall=map[7][4].wall=map[6][4].wall=map[5][4].wall=map[5][5].wall=map[5][6].wall=true;
	map[5][7].wall=map[4][7].wall=map[3][7].wall=map[3][6].wall=map[3][5].wall=map[2][5].wall=map[1][5].wall=map[0][5].wall=true;
	map[3][1].place=map[1][4].place=map[6][3].place=map[4][6].place=true;
	map[3][3].box=map[3][4].box=map[5][3].box=map[4][5].box=true;
}
void CboxView::init2()
{
	I=3;
	J=1;
	L=7;
	W=9;
	BOXNUM=4;
	atplacenum=0;
	int i,j;
	for(i=0;i<L;i++)
	{
		for(j=0;j<W;j++)
		{
			map[i][j].wall=map[i][j].box=map[i][j].place=false;
			map[i][j].p.x=i*20;
			map[i][j].p.y=j*20;
		}
	}
    map[1][0].wall=map[2][0].wall=map[3][0].wall=map[4][0].wall=map[5][0].wall=map[5][1].wall=map[5][2].wall=map[5][3].wall=map[5][4].wall=map[6][4].wall=true;
	map[6][5].wall=map[6][6].wall=map[6][7].wall=map[5][7].wall=map[5][8].wall=map[4][8].wall=map[3][8].wall=map[2][8].wall=map[2][7].wall=map[1][7].wall=true;
	map[0][7].wall=map[0][6].wall=map[0][5].wall=map[0][4].wall=map[0][3].wall=map[1][3].wall=map[1][2].wall=map[1][1].wall=true;
	map[3][2].place=map[3][3].place=map[3][4].place=map[3][5].place=map[3][6].place=map[3][1].place=true;
	map[2][2].box=map[4][2].box=map[3][3].box=map[3][4].box=map[3][5].box=map[3][6].box=true;
}
void CboxView::move()
{
	m_move=boxmove=false;
	switch(d)
	{
	case 'L':if(!map[I-1][J].wall)
			 {
				 if(!map[I-1][J].box)
				 {
					 I--;
					 m_move=true;
				 }
				 else
				 {
					 if(!map[I-2][J].wall&&!map[I-2][J].box)
					 {
						 I--;
						 m_move=boxmove=true;
						 map[I][J].box=false;
						 map[I-1][J].box=true;
						 if(map[I][J].place==true&&map[I-1][J].place==false)
							 atplacenum--;
						 else if(map[I][J].place==false&&map[I-1][J].place==true)
							 atplacenum++;
					 }
				 }
			 }
			break;
	case 'R':if(!map[I+1][J].wall)
			 {
				 if(!map[I+1][J].box)
				 {
					 I++;
					 m_move=true;
				 }
				 else
				 {
					 if(!map[I+2][J].wall&&!map[I+2][J].box)
					 {
						 I++;
						m_move=boxmove=true;
						 map[I][J].box=false;
						 map[I+1][J].box=true;
						 if(map[I][J].place==true&&map[I+1][J].place==false)
							 atplacenum--;
						 else if(map[I][J].place==false&&map[I+1][J].place==true)
							 atplacenum++;
					 }
				 }
			 }
		break;
	case 'U':if(!map[I][J-1].wall)
			 {
				 if(!map[I][J-1].box)
				 {
					 J--;
					 m_move=true;
				 }
				 else
				 {
					 if(!map[I][J-2].wall&&!map[I][J-2].box)
					 {
						 J--;
						 m_move=boxmove=true;
						 map[I][J].box=false;
						 map[I][J-1].box=true;
						 if(map[I][J].place==true&&map[I][J-1].place==false)
							 atplacenum--;
						 else if(map[I][J].place==false&&map[I][J-1].place==true)
							 atplacenum++;
					 }
				 }
			 }
			 break;
	case 'D':if(!map[I][J+1].wall)
			 {
				 if(!map[I][J+1].box)
				 {
					 J++;
					 m_move=true;
				 }
				 else
				 {
					 if(!map[I][J+2].wall&&!map[I][J+2].box)
					 {
						 J++;
						 m_move=boxmove=true;
						 map[I][J].box=false;
						 map[I][J+1].box=true;
						 if(map[I][J].place==true&&map[I][J+1].place==false)
							 atplacenum--;
						 else if(map[I][J].place==false&&map[I][J+1].place==true)
							 atplacenum++;
					 }
				 }
			 }
		break;
	default:break;
	}
	if(m_move)
	{
		stepnum++;
		Cway *p=new Cway(d,boxmove);
		m_wayarray.Add(p);
		if(atplacenum==BOXNUM)
			success=true;
		CboxDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		pDoc->UpdateAllViews(NULL);
	}
}



