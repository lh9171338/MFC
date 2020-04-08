
// tankView.cpp : CtankView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "tank.h"
#endif

#include "tankDoc.h"
#include "tankView.h"
#include <ctime>
#include<cstdlib>
#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" ) 
BOOL PlaySound(LPCSTR pszSound, HMODULE hmod,DWORD fdwSound); 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtankView

IMPLEMENT_DYNCREATE(CtankView, CView)

BEGIN_MESSAGE_MAP(CtankView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CtankView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_KEYUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CtankView 构造/析构

CtankView::CtankView()
{
	// TODO: 在此处添加构造代码
	map[0][0].init1map(map);
	init(9,25,1,P1);
	srand(time(NULL));
	m_type=rand()%3+2;
	init(1,1,m_type,A[0]);
	m_type=rand()%3+2;
	init(25,1,m_type,A[1]);
	m_type=rand()%3+2;
	init(13,1,m_type,A[2]);
	A[3].m_alive=false;
	m_start=m_move=false;
	m_first=true;
	m_life=3;
	m_score=0;
}
// 重写
CtankView::~CtankView()
{
}

BOOL CtankView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CtankView 绘制

void CtankView::OnDraw(CDC* pDC)
{
	CtankDoc* pDoc = GetDocument();
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
	

	CPen pen(PS_SOLID,1,RGB(0,0,255));	
	CBrush brush(RGB(0,0,0));
	MemDC.SelectObject(&brush);
	MemDC.SelectObject(&pen);
	MemDC.Rectangle(0,0,521,521);
	if(!m_start)
	{
		CBrush brush(RGB(0,255,0));
		MemDC.SelectObject(&brush);
		MemDC.BeginPath();
		MemDC.MoveTo(600,100);
		MemDC.LineTo(640,125);
		MemDC.LineTo(600,150);
		MemDC.LineTo(600,100);
		MemDC.EndPath();
		MemDC.FillPath();
	}
	P1.draw(&MemDC);
	int i,j;
	for(i=0;i<4;i++)
		if(A[i].m_alive)
			A[i].draw(&MemDC);
	for(i=0;i<26;i++)
		for(j=0;j<26;j++)
			map[i][j].drawmap(&MemDC);
	MemDC.SetTextColor(RGB(255,0,255));
	CString str;
	str.Format(_T("分数:%d"),m_score);
	MemDC.TextOutW(600,200,str);
	str.Format(_T("数量:%d"),m_score/100);
	MemDC.TextOutW(600,225,str);
	if(m_life==0)
	{
		MemDC.SetTextColor(RGB(255,0,255));
		MemDC.TextOutW(600,250,_T("game over"));
		KillTimer(1);
		KillTimer(2);
		KillTimer(3);
	}
	else
	{
		str.Format(_T("生命:%d"),m_life);
		MemDC.TextOutW(600,250,str);
	}
	
	



	pDC->BitBlt(0,0,r.right,r.bottom,&MemDC,0,0,SRCCOPY); 
	MemBitmap.DeleteObject(); 
	MemDC.DeleteDC(); 
	// TODO: 在此处为本机数据添加绘制代码
}



// CtankView 打印


void CtankView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CtankView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CtankView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CtankView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CtankView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CtankView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CtankView 诊断

#ifdef _DEBUG
void CtankView::AssertValid() const
{
	CView::AssertValid();
}

void CtankView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtankDoc* CtankView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtankDoc)));
	return (CtankDoc*)m_pDocument;
}
#endif //_DEBUG


// CtankView 消息处理程序


void CtankView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//m_move=false;
	if(m_life)
	{
	if(nChar==VK_RETURN)
	{
		if(!m_start)
		{
			if(m_first)
			{
				PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC); 
				m_first=false;
			}
			m_start=true;
			SetTimer(1,40,NULL);							//高速坦克
			SetTimer(2,60,NULL);							//低速坦克
			SetTimer(3,100,NULL);							//子弹
			m_time1=m_time2=0;
		}
	}
	if(m_start&&m_life)
	{
		switch(nChar)
		{
		case 'A':
				m_move=true;
				P1.m_d='L';
			break;
		case 'D':
				m_move=true;
				P1.m_d='R';
			break;
		case 'W':
				m_move=true;
				P1.m_d='U';
			break;
		case 'S':
				m_move=true;
				P1.m_d='D';
			break;
		case 'J':
				Pfire(P1);
			break;
		case 'P':
				{
					m_start=false;
					GetDocument()->UpdateAllViews(NULL);
				}
		default:break;
		}
	}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CtankView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent==1)
	{
		if(m_time1==0)
		{
			if(P1.m_alive)
				P1.m_oldd=P1.m_d;
			else
				init(9,25,1,P1);
		}
		if(m_move||m_time1>0)
		{
			m_time1++;
			if(P1.m_alive)
				Pmove(P1,m_time1);
			if(m_time1==5)
				m_time1=0;
		}
		if(m_time1==0&&m_start==false)
			KillTimer(1);
	}
	else if(nIDEvent==2)
	{
		if(m_time2==0)
		{
			for(int i=0;i<4;i++)
			{
				if(A[i].m_alive)
				{
					produced(A[i]);
					A[i].m_oldd=A[i].m_d;
				}
				else
				{
					int n=bornplace();
					if(n)
					{
						srand(time(NULL));
						int m_type=rand()%3+2;
						init(12*n+1,1,m_type,A[i]);
					}
				}
			}
		}
		m_time2++;
		for(int i=0;i<4;i++)
			if(A[i].m_alive)
				Pmove(A[i],m_time2);
	
		if(m_time2==5)
			m_time2=0;
		if(m_time2==0&&m_start==false)
			KillTimer(2);
	}		
	else if(nIDEvent==3)
	{
		zmove(P1);
		for(int i=0;i<4;i++)
		{
			if(A[i].m_alive)
			{
				Pfire(A[i]);
				zmove(A[i]);
			}
		}
		if(!m_start)
			KillTimer(3);
	}
	GetDocument()->UpdateAllViews(NULL);
	CView::OnTimer(nIDEvent);
}
void CtankView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nChar=='A'||nChar=='D'||nChar=='W'||nChar=='S')
		m_move=false;
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


BOOL CtankView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return true;
	return CView::OnEraseBkgnd(pDC);
}

void CtankView::Pmove(CT &t,int m_time)
{
	switch(t.m_oldd)
	{
	case 'L':
		if(t.m_p.x>21&&!map[t.I-2][t.J].m_wall&&!map[t.I-2][t.J-1].m_wall&&!map[t.I-2][t.J].m_tank&&!map[t.I-2][t.J-1].m_tank)
		{
			t.m_p.x-=4;
			if(m_time==5)
			{
				map[t.I][t.J].m_tank=map[t.I-1][t.J].m_tank=map[t.I-1][t.J-1].m_tank=map[t.I][t.J-1].m_tank=false;
				t.I--;
				map[t.I][t.J].m_tank=map[t.I-1][t.J].m_tank=map[t.I-1][t.J-1].m_tank=map[t.I][t.J-1].m_tank=true;
				map[t.I][t.J].m_typetank=map[t.I-1][t.J].m_typetank=map[t.I-1][t.J-1].m_typetank=map[t.I][t.J-1].m_typetank=t.m_type;
			}
		}
		break;
	case 'R':
		if(t.m_p.x<501&&!map[t.I+1][t.J].m_wall&&!map[t.I+1][t.J-1].m_wall&&!map[t.I+1][t.J].m_tank&&!map[t.I+1][t.J-1].m_tank)
		{
			t.m_p.x+=4;
			if(m_time==5)
			{
				map[t.I][t.J].m_tank=map[t.I-1][t.J].m_tank=map[t.I-1][t.J-1].m_tank=map[t.I][t.J-1].m_tank=false;
				t.I++;
				map[t.I][t.J].m_tank=map[t.I-1][t.J].m_tank=map[t.I-1][t.J-1].m_tank=map[t.I][t.J-1].m_tank=true;
				map[t.I][t.J].m_typetank=map[t.I-1][t.J].m_typetank=map[t.I-1][t.J-1].m_typetank=map[t.I][t.J-1].m_typetank=t.m_type;
			}
		}
		break;
	case 'U':
		if(t.m_p.y>21&&!map[t.I][t.J-2].m_wall&&!map[t.I-1][t.J-2].m_wall&&!map[t.I][t.J-2].m_tank&&!map[t.I-1][t.J-2].m_tank)
		{
			t.m_p.y-=4;
			if(m_time==5)
			{
				map[t.I][t.J].m_tank=map[t.I-1][t.J].m_tank=map[t.I-1][t.J-1].m_tank=map[t.I][t.J-1].m_tank=false;
				t.J--;
				map[t.I][t.J].m_tank=map[t.I-1][t.J].m_tank=map[t.I-1][t.J-1].m_tank=map[t.I][t.J-1].m_tank=true;
				map[t.I][t.J].m_typetank=map[t.I-1][t.J].m_typetank=map[t.I-1][t.J-1].m_typetank=map[t.I][t.J-1].m_typetank=t.m_type;
			}
		}
		break;
	case 'D':
		if(t.m_p.y<501&&!map[t.I][t.J+1].m_wall&&!map[t.I-1][t.J+1].m_wall&&!map[t.I][t.J+1].m_tank&&!map[t.I-1][t.J+1].m_tank)
		{
			t.m_p.y+=4;
			if(m_time==5)
			{
				map[t.I][t.J].m_tank=map[t.I-1][t.J].m_tank=map[t.I-1][t.J-1].m_tank=map[t.I][t.J-1].m_tank=false;
				t.J++;
				map[t.I][t.J].m_tank=map[t.I-1][t.J].m_tank=map[t.I-1][t.J-1].m_tank=map[t.I][t.J-1].m_tank=true;
				map[t.I][t.J].m_typetank=map[t.I-1][t.J].m_typetank=map[t.I-1][t.J-1].m_typetank=map[t.I][t.J-1].m_typetank=t.m_type;
			}
		}
		break;
		default:break;
	}
	if(m_time==5)
	{
		t.m_p.x=t.I*20+1;
		t.m_p.y=t.J*20+1;
	}

}
void CtankView::produced(CT &t)
{
	srand(time(NULL));
	switch(t.m_oldd)
	{
	case 'U':
		if(t.m_p.y>21&&!map[t.I][t.J-2].m_wall&&!map[t.I-1][t.J-2].m_wall&&!map[t.I][t.J-2].m_tank&&!map[t.I-1][t.J-2].m_tank&&rand()%4<3)					//前进
			t.m_d='U';
		else
		{
			int choose=0;
			bool left,right,back;
			left=right=back=false;
			if(t.m_p.x>21&&!map[t.I-2][t.J].m_wall&&!map[t.I-2][t.J-1].m_wall&&!map[t.I-2][t.J].m_tank&&!map[t.I-2][t.J-1].m_tank)			//左转
			{
				choose++;
				left=true;
			}
			if(t.m_p.x<501&&!map[t.I+1][t.J].m_wall&&!map[t.I+1][t.J-1].m_wall&&!map[t.I+1][t.J].m_tank&&!map[t.I+1][t.J-1].m_tank)			//右转
			{
				choose++;
				right=true;
			}
			if(t.m_p.y<501&&!map[t.I][t.J+1].m_wall&&!map[t.I-1][t.J+1].m_wall&&!map[t.I][t.J+1].m_tank&&!map[t.I-1][t.J+1].m_tank)			//后退
			{
				choose++;
				back=true;
			}
			if(choose==0)
				t.m_d='N';
			else
			{
			switch(rand()%choose)
			{
			case 0:
				if(left)
					t.m_d='L';
				else if(right)
					t.m_d='R';
				else
					t.m_d='D';
				break;
			case 1:
				if(right)
					t.m_d='R';
				else if(back)
					t.m_d='D';
				else
					t.m_d='L';
				break;
			case 2:
				if(back)
					t.m_d='D';
				else if(left)
					t.m_d='L';
				else
					t.m_d='R';
				break;
			}
			}
		}
		break;
	case 'D':
		if(t.m_p.y<501&&!map[t.I][t.J+1].m_wall&&!map[t.I-1][t.J+1].m_wall&&!map[t.I][t.J+1].m_tank&&!map[t.I-1][t.J+1].m_tank&&rand()%4<3)				//前进
			t.m_d='D';
		else
		{
			int choose=0;
			bool left,right,back;
			left=right=back=false;
			if(t.m_p.x<501&&!map[t.I+1][t.J].m_wall&&!map[t.I+1][t.J-1].m_wall&&!map[t.I+1][t.J].m_tank&&!map[t.I+1][t.J-1].m_tank)			//左转
			{
				choose++;
				left=true;
			}
			if(t.m_p.x>21&&!map[t.I-2][t.J].m_wall&&!map[t.I-2][t.J-1].m_wall&&!map[t.I-2][t.J].m_tank&&!map[t.I-2][t.J-1].m_tank)			//右转
			{
				choose++;
				right=true;
			}
			if(t.m_p.y>21&&!map[t.I][t.J-2].m_wall&&!map[t.I-1][t.J-2].m_wall&&!map[t.I][t.J-2].m_tank&&!map[t.I-1][t.J-2].m_tank)			//后退
			{
				choose++;
				back=true;
			}
			if(choose==0)
				t.m_d='N';
			else
			{
			switch(rand()%choose)
			{
			case 0:
				if(left)
					t.m_d='R';
				else if(right)
					t.m_d='L';
				else
					t.m_d='U';
				break;
			case 1:
				if(right)
					t.m_d='L';
				else if(back)
					t.m_d='U';
				else
					t.m_d='R';
				break;
			case 2:
				if(back)
					t.m_d='U';
				else if(left)
					t.m_d='L';
				else
					t.m_d='R';
				break;
			}
			}
		}
		break;
	case 'L':
		if(t.m_p.x>21&&!map[t.I-2][t.J].m_wall&&!map[t.I-2][t.J-1].m_wall&&!map[t.I-2][t.J].m_tank&&!map[t.I-2][t.J-1].m_tank&&rand()%4<3)			//前进
			t.m_d='L';
		else
		{
			int choose=0;
			bool left,right,back;
			left=right=back=false;
			if(t.m_p.y<501&&!map[t.I][t.J+1].m_wall&&!map[t.I-1][t.J+1].m_wall&&!map[t.I][t.J+1].m_tank&&!map[t.I-1][t.J+1].m_tank)		//左转
			{
				choose++;
				left=true;
			}
			if(t.m_p.y>21&&!map[t.I][t.J-2].m_wall&&!map[t.I-1][t.J-2].m_wall&&!map[t.I][t.J-2].m_tank&&!map[t.I-1][t.J-2].m_tank)		//右转
			{
				choose++;
				right=true;
			}
			if(t.m_p.x<501&&!map[t.I+1][t.J].m_wall&&!map[t.I+1][t.J-1].m_wall&&!map[t.I+1][t.J].m_tank&&!map[t.I+1][t.J-1].m_tank)		//后退
			{
				choose++;
				back=true;
			}
			if(choose==0)
				t.m_d='N';
			else
			{
			switch(rand()%choose)
			{
			case 0:
				if(left)
					t.m_d='D';
				else if(right)
					t.m_d='U';
				else
					t.m_d='R';
				break;
			case 1:
				if(right)
					t.m_d='U';
				else if(back)
					t.m_d='R';
				else
					t.m_d='D';
				break;
			case 2:
				if(back)
					t.m_d='R';
				else if(left)
					t.m_d='D';
				else
					t.m_d='U';
				break;
			}
			}
		}
		break;
	case 'R':
		if(t.m_p.x<501&&!map[t.I+1][t.J].m_wall&&!map[t.I+1][t.J-1].m_wall&&!map[t.I+1][t.J].m_tank&&!map[t.I+1][t.J-1].m_tank&&rand()%4<3)				//前进
			t.m_d='R';
		else
		{
			int choose=0;
			bool left,right,back;
			left=right=back=false;
			if(t.m_p.y>21&&!map[t.I][t.J-2].m_wall&&!map[t.I-1][t.J-2].m_wall&&!map[t.I][t.J-2].m_tank&&!map[t.I-1][t.J-2].m_tank)			//左转
			{
				choose++;
				left=true;
			}
			if(t.m_p.y<501&&!map[t.I][t.J+1].m_wall&&!map[t.I-1][t.J+1].m_wall&&!map[t.I][t.J+1].m_tank&&!map[t.I-1][t.J+1].m_tank)			//右转
			{
				choose++;
				right=true;
			}
			if(t.m_p.x>21&&!map[t.I-2][t.J].m_wall&&!map[t.I-2][t.J-1].m_wall&&!map[t.I-2][t.J].m_tank&&!map[t.I-2][t.J-1].m_tank)			//后退
			{
				choose++;
				back=true;
			}
			if(choose==0)
				t.m_d='N';
			else
			{
			switch(rand()%choose)
			{
			case 0:
				if(left)
					t.m_d='U';
				else if(right)
					t.m_d='D';
				else
					t.m_d='L';
				break;
			case 1:
				if(right)
					t.m_d='D';
				else if(back)
					t.m_d='L';
				else
					t.m_d='U';
				break;
			case 2:
				if(back)
					t.m_d='L';
				else if(left)
					t.m_d='U';
				else
					t.m_d='D';
				break;
			}
			}
		}
		break;
	}
}
void CtankView::init(int i,int j,int type,CT &t)
{
	switch(type)
	{
	case 1:
		t.set(i,j,RGB(51,204,153),'U',1);
		break;
	case 2:
		t.set(i,j,RGB(255,0,0),'D',2);
		break;
	case 3:
		t.set(i,j,RGB(0,255,0),'D',3);
		break;
	case 4:
		t.set(i,j,RGB(0,0,255),'D',4);
		break;
	}
	map[i][j].m_tank=map[i-1][j].m_tank=map[i-1][j-1].m_tank=map[i][j-1].m_tank=true;						//四个点
	map[i][j].m_typetank=map[i-1][j].m_typetank=map[i-1][j-1].m_typetank=map[i][j-1].m_typetank=t.m_type;
	t.m_alive=true;
}
int CtankView::bornplace()
{
	int choose=0;
	bool p1,p2,p3;
	p1=p2=p3=false;
	if(!map[1][1].m_tank&&!map[0][1].m_tank&&!map[0][0].m_tank&&!map[1][0].m_tank)
	{
		choose++;
		p1=true;
	}
	if(!map[13][1].m_tank&&!map[12][1].m_tank&&!map[12][0].m_tank&&!map[13][0].m_tank)
	{
		choose++;
		p2=true;
	}
	if(!map[25][1].m_tank&&!map[24][1].m_tank&&!map[24][0].m_tank&&!map[25][0].m_tank)
	{
		choose++;
		p3=true;
	}
	if(choose==0)
		return 0;
	else
	{
		srand(time(NULL));
		int j=rand()%choose;
		switch(j)
		{
		case 1:
			if(p1)
				j=1;
			else if(p2)
				j=2;
			else
				j=3;
			break;
		case 2:
			if(p2)
				j=2;
			else if(p3)
				j=3;
			else
				j=1;
			break;
		case 3:
			if(p3)
				j=3;
			else if(p1)
				j=1;
			else
				j=2;
			break;
		}
		return j;
	}
}
void CtankView::Pfire(CT &t)
{
	if(!t.m_zidan)
	{
		t.m_dzidan=t.m_oldd;
		t.ZI=t.I;
		t.ZJ=t.J;
		t.m_zidan=true;
		map[t.ZI][t.ZJ].m_zidan=true;
		map[t.ZI][t.ZJ].m_zidantype=t.m_type;
	}
}
void CtankView::zmove(CT &t)
{
	if(t.m_zidan)
	{
		map[t.ZI][t.ZJ].m_zidan=false;
		switch(t.m_dzidan)
		{
		case 'L':
			t.ZI--;
			break;
		case 'R':
			t.ZI++;
			break;
		case 'U':
			t.ZJ--;
			break;
		case 'D':
			t.ZJ++;
			break;
		default:break;
		}
		if(t.ZI<0||t.ZI>25||t.ZJ<0||t.ZJ>25)											//出界
			t.m_zidan=false;
		else if(t.ZI>11&&t.ZI<14&&t.ZJ>23)												//打到老巢
		{
			m_life=0;
			map[13][25].m_typewall=6;
			PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC); 
		}
		else if(map[t.ZI][t.ZJ].m_zidan)												//打到子弹
		{
			if(t.m_type<=1)
			{
				int i=0;
				for(i=0;i<4;i++)
				{
					if(A[i].ZI==t.ZI&&A[i].ZJ==t.ZJ)
						break;
				}
				t.m_zidan=false;
				A[i].m_zidan=false;
				map[t.ZI][t.ZJ].m_zidan=false;
			}
			else if(P1.m_zidan)
			{
				if(t.ZI==P1.ZI&&t.ZJ==P1.ZJ)
				{
					t.m_zidan=false;
					P1.m_zidan=false;
					map[t.ZI][t.ZJ].m_zidan=false;
				}
			}
		}
		else
		{
		if(t.m_dzidan=='U'||t.m_dzidan=='D')
		{
			if(map[t.ZI][t.ZJ].m_wall||map[t.ZI-1][t.ZJ].m_wall)						//打到墙
			{
				if(map[t.ZI][t.ZJ].m_wall)
				{
					if(map[t.ZI][t.ZJ].m_typewall==1)										//铁
						t.m_zidan=false;
					else if(map[t.ZI][t.ZJ].m_typewall==2)									//砖
					{
						t.m_zidan=false;
						map[t.ZI][t.ZJ].m_wall=false;
					}
				}
				if(map[t.ZI-1][t.ZJ].m_wall)
				{
					if(map[t.ZI-1][t.ZJ].m_typewall==1)										//铁
						t.m_zidan=false;
					else if(map[t.ZI-1][t.ZJ].m_typewall==2)								//砖
					{
						t.m_zidan=false;
						map[t.ZI-1][t.ZJ].m_wall=false;
					}
				}
			}
			else if(map[t.ZI][t.ZJ].m_tank||map[t.ZI-1][t.ZJ].m_tank)						//打到坦克
			{
				if(map[t.ZI][t.ZJ].m_tank)
				{
					if(t.m_type<=1)
					{
						int i=0;
						for(i=0;i<4;i++)
						{
							if((t.ZI==A[i].I&&t.ZJ==A[i].J)||(t.ZI==A[i].I-1&&t.ZJ==A[i].J)||(t.ZI==A[i].I-1&&t.ZJ==A[i].J-1)||(t.ZI==A[i].I&&t.ZJ==A[i].J-1))
								break;
						}
						if(i<4)
						{
						t.m_zidan=false;
						A[i].m_alive=false;
						map[A[i].I][A[i].J].m_tank=map[A[i].I-1][A[i].J].m_tank=map[A[i].I-1][A[i].J-1].m_tank=map[A[i].I][A[i].J-1].m_tank=false;
						m_score+=100;
						PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC); 
						}
					}
					else
					{
						if((t.ZI==P1.I&&t.ZJ==P1.J)||(t.ZI==P1.I-1&&t.ZJ==P1.J)||(t.ZI==P1.I-1&&t.ZJ==P1.J-1)||(t.ZI==P1.I&&t.ZJ==P1.J-1))
						{
							t.m_zidan=false;
							P1.m_alive=false;
							map[P1.I][P1.J].m_tank=map[P1.I-1][P1.J].m_tank=map[P1.I-1][P1.J-1].m_tank=map[P1.I][P1.J-1].m_tank=false;
							m_life--;
						}
					}
				}
				if(map[t.ZI-1][t.ZJ].m_tank)
				{
					if(t.m_type<=1)
					{
						int i=0;
						for(i=0;i<4;i++)
						{
							if((t.ZI-1==A[i].I&&t.ZJ==A[i].J)||(t.ZI-1==A[i].I-1&&t.ZJ==A[i].J)||(t.ZI-1==A[i].I-1&&t.ZJ==A[i].J-1)||(t.ZI-1==A[i].I&&t.ZJ==A[i].J-1))
								break;
						}
						if(i<4)
						{
						t.m_zidan=false;
						A[i].m_alive=false;
						map[A[i].I][A[i].J].m_tank=map[A[i].I-1][A[i].J].m_tank=map[A[i].I-1][A[i].J-1].m_tank=map[A[i].I][A[i].J-1].m_tank=false;
						m_score+=100;
						PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC); 
						}
					}
					else
					{
						if((t.ZI-1==P1.I&&t.ZJ==P1.J)||(t.ZI-1==P1.I-1&&t.ZJ==P1.J)||(t.ZI-1==P1.I-1&&t.ZJ==P1.J-1)||(t.ZI-1==P1.I&&t.ZJ==P1.J-1))
						{
							t.m_zidan=false;
							P1.m_alive=false;
							map[P1.I][P1.J].m_tank=map[P1.I-1][P1.J].m_tank=map[P1.I-1][P1.J-1].m_tank=map[P1.I][P1.J-1].m_tank=false;
							m_life--;
						}
					}
				}
			}
		}
		else
		{
			if(map[t.ZI][t.ZJ].m_wall||map[t.ZI][t.ZJ-1].m_wall)						//打到墙
			{
				if(map[t.ZI][t.ZJ].m_wall)
				{
					if(map[t.ZI][t.ZJ].m_typewall==1)										//铁
						t.m_zidan=false;
					else if(map[t.ZI][t.ZJ].m_typewall==2)									//砖
					{
						t.m_zidan=false;
						map[t.ZI][t.ZJ].m_wall=false;
					}
				}
				if(map[t.ZI][t.ZJ-1].m_wall)
				{
					if(map[t.ZI][t.ZJ-1].m_typewall==1)										//铁
						t.m_zidan=false;
					else if(map[t.ZI][t.ZJ-1].m_typewall==2)								//砖
					{
						t.m_zidan=false;
						map[t.ZI][t.ZJ-1].m_wall=false;
					}
				}
			}
			else if(map[t.ZI][t.ZJ].m_tank||map[t.ZI][t.ZJ-1].m_tank)						//打到坦克
			{
				if(map[t.ZI][t.ZJ].m_tank)
				{
					if(t.m_type<=1)
					{
						int i=0;
						for(i=0;i<4;i++)
						{
							if((t.ZI==A[i].I&&t.ZJ==A[i].J)||(t.ZI==A[i].I-1&&t.ZJ==A[i].J)||(t.ZI==A[i].I-1&&t.ZJ==A[i].J-1)||(t.ZI==A[i].I&&t.ZJ==A[i].J-1))
								break;
						}
						if(i<4)
						{
						t.m_zidan=false;
						A[i].m_alive=false;
						map[A[i].I][A[i].J].m_tank=map[A[i].I-1][A[i].J].m_tank=map[A[i].I-1][A[i].J-1].m_tank=map[A[i].I][A[i].J-1].m_tank=false;
						m_score+=100;
						PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC); 
						}
					}
					else
					{
						if((t.ZI==P1.I&&t.ZJ==P1.J)||(t.ZI==P1.I-1&&t.ZJ==P1.J)||(t.ZI==P1.I-1&&t.ZJ==P1.J-1)||(t.ZI==P1.I&&t.ZJ==P1.J-1))
						{
							t.m_zidan=false;
							P1.m_alive=false;
							map[P1.I][P1.J].m_tank=map[P1.I-1][P1.J].m_tank=map[P1.I-1][P1.J-1].m_tank=map[P1.I][P1.J-1].m_tank=false;
							m_life--;
						}
					}
				}
				if(map[t.ZI][t.ZJ-1].m_tank)
				{
					if(t.m_type<=1)
					{
						int i=0;
						for(i=0;i<4;i++)
						{
							if((t.ZI==A[i].I&&t.ZJ-1==A[i].J)||(t.ZI==A[i].I-1&&t.ZJ-1==A[i].J)||(t.ZI==A[i].I-1&&t.ZJ-1==A[i].J-1)||(t.ZI==A[i].I&&t.ZJ-1==A[i].J-1))
								break;
						}
						if(i<4)
						{
						t.m_zidan=false;
						A[i].m_alive=false;
						map[A[i].I][A[i].J].m_tank=map[A[i].I-1][A[i].J].m_tank=map[A[i].I-1][A[i].J-1].m_tank=map[A[i].I][A[i].J-1].m_tank=false;
						m_score+=100;
						PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC); 
						}
					}
					else
					{
						if((t.ZI==P1.I&&t.ZJ-1==P1.J)||(t.ZI==P1.I-1&&t.ZJ-1==P1.J)||(t.ZI==P1.I-1&&t.ZJ-1==P1.J-1)||(t.ZI==P1.I&&t.ZJ-1==P1.J-1))
						{
							t.m_zidan=false;
							P1.m_alive=false;
							map[P1.I][P1.J].m_tank=map[P1.I-1][P1.J].m_tank=map[P1.I-1][P1.J-1].m_tank=map[P1.I][P1.J-1].m_tank=false;
							m_life--;
						}
					}
				}
			}
		}
		}
		if(t.m_zidan)
			map[t.ZI][t.ZJ].m_zidan=true;
	}
}