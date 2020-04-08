
// mineView.cpp : CmineView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "mine.h"
#endif

#include "mineDoc.h"
#include "mineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmineView

IMPLEMENT_DYNCREATE(CmineView, CView)

BEGIN_MESSAGE_MAP(CmineView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CmineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDB_START,ONSTARTDOWN)
	ON_BN_CLICKED(IDB_RSTART,ONRSTARTDOWN)
	ON_COMMAND(ID_E, &CmineView::OnE)
	ON_UPDATE_COMMAND_UI(ID_E, &CmineView::OnUpdateE)
	ON_COMMAND(ID_N, &CmineView::OnN)
	ON_UPDATE_COMMAND_UI(ID_N, &CmineView::OnUpdateN)
	ON_COMMAND(ID_H, &CmineView::OnH)
	ON_UPDATE_COMMAND_UI(ID_H, &CmineView::OnUpdateH)
END_MESSAGE_MAP()

// CmineView ����/����
CmineView::CmineView()
{
	// TODO: �ڴ˴���ӹ������
	m_time=m_num=0;
	life=true;
	bagin=false;
	MINE=50;
}
void CmineView::set()
{
	m_time=m_num=0;
	life=true;
	bagin=false;
	MINE=50;
}
CmineView::~CmineView()
{
}

BOOL CmineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CmineView ����

void CmineView::OnDraw(CDC* pDC)
{
	CmineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int i,j;
	CPen pen(PS_SOLID,1,RGB(0,0,255));
	pDC->SelectObject(&pen);
	pDC->Rectangle(0,0,400,400);
	if(bagin)
	{
		for(i=0;i<20;i++)
		{
			for(j=0;j<20;j++)
			{
				CPen pen(PS_SOLID,1,RGB(0,255,0));
				pDC->SelectObject(&pen);
				pDC->Rectangle(p[i][j].p.x,p[i][j].p.y,p[i][j].p.x+18,p[i][j].p.y+18);
				if(!p[i][j].dig&&p[i][j].flag)
				{
					CPen pen(PS_SOLID,1,RGB(255,0,0));
					pDC->SelectObject(&pen);
					CPoint m(p[i][j].p.x+5,p[i][j].p.y+16);
					pDC->MoveTo(m);
					m.SetPoint(p[i][j].p.x+5,p[i][j].p.y+2);
					pDC->LineTo(m);
					m.SetPoint(p[i][j].p.x+13,p[i][j].p.y+9);
					pDC->LineTo(m);
					m.SetPoint(p[i][j].p.x+5,p[i][j].p.y+9);
					pDC->LineTo(m);
				}
				else if(p[i][j].dig)
					show(p[i][j]);
			}
		}
	}
	else
	{
		for(i=0;i<20;i++)
		{
			for(j=0;j<20;j++)
			{
				CPen pen(PS_SOLID,1,RGB(0,255,0));
				pDC->SelectObject(&pen);
				pDC->Rectangle(i*20+1,j*20+1,i*20+19,j*20+19);
			}
		}
	}
	CString str;
	str.Format(_T("time:%d"),m_time);
	pDC->SetTextColor(RGB(255,0,255));
	pDC->TextOutW(450,50,str);
	str.Format(_T("mine:%d"),MINE);
	pDC->SetTextColor(RGB(0,255,0));
	pDC->TextOutW(450,75,str);
	if(!life)
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->TextOutW(450,100,_T("dead"));
	}
	if(m_num==400-MINE)
	{
		pDC->SetTextColor(RGB(0,255,0));
		pDC->TextOutW(450,100,_T("you succeed"));
	}

	//showall();
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CmineView ��ӡ


void CmineView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CmineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CmineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CmineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CmineView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	if(life&&bagin)
	{
		if(0<=point.x&&point.x<400&&0<=point.y&&point.y<400)
		{
			int i,j;
			i=point.x/20;
			j=point.y/20;
			if(!p[i][j].flag)
				p[i][j].flag=true;
			else
				p[i][j].flag=false;
			CmineDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			if (!pDoc)
			return;
			pDoc->UpdateAllViews(NULL);
		}
	}
	else if(life&&!bagin)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}
}

void CmineView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	CMenu menupopup;
	if(menupopup.CreatePopupMenu())
	{
	menupopup.AppendMenuW(MF_STRING,ID_E,_T("��\tCtrl+R"));
	menupopup.AppendMenuW(MF_STRING,ID_N,_T("һ��\tCtrl+G"));
	menupopup.AppendMenuW(MF_STRING,ID_H,_T("��\tCtrl+B"));
	menupopup.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);			//��ʾ�˵�
	}
}


// CmineView ���

#ifdef _DEBUG
void CmineView::AssertValid() const
{
	CView::AssertValid();
}

void CmineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmineDoc* CmineView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmineDoc)));
	return (CmineDoc*)m_pDocument;
}
#endif //_DEBUG


// CmineView ��Ϣ�������


int CmineView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rect_button1(450,170,550,200);
	b1.Create(_T("��ʼ"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button1,this,IDB_START);
	b1.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button2(450,230,550,260);
	b2.Create(_T("���¿�ʼ"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button2,this,IDB_RSTART);
	b2.ShowWindow(SW_SHOWNORMAL);
	return 0;
}


void CmineView::OnDestroy()
{
	CView::OnDestroy();
	KillTimer(1);
	// TODO: �ڴ˴������Ϣ����������
}


void CmineView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_time++;
	CClientDC dc(this);
	CString str;
	str.Format(_T("time:%d"),m_time);
	dc.SetTextColor(RGB(255,0,255));
	dc.TextOutW(450,50,str);
	CView::OnTimer(nIDEvent);
}


void CmineView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(life&&bagin)
	{
		if(0<=point.x&&point.x<400&&0<=point.y&&point.y<400)
		{
			int i,j;
			i=point.x/20;
			j=point.y/20;
			CClientDC dc(this);
			if(!p[i][j].flag)
			{
				if(p[i][j].mine)
				{
					showall();																					
					CBrush brush(RGB(255,0,0));
					dc.SelectObject(&brush);
					dc.Ellipse(p[i][j].p.x+5,p[i][j].p.y+5,p[i][j].p.x+13,p[i][j].p.y+13);
					life=false; 
					KillTimer(1);
					dc.SetTextColor(RGB(255,0,0));
					dc.TextOutW(450,100,_T("dead"));
				}
				else
				{
					if(p[i][j].num==0)
					{
						p[i][j].dig=true;
						showsome(p[i][j],i,j);
					}
					show(p[i][j]);
					p[i][j].dig=true;
					m_num++;
					if(m_num==400-MINE)
					{
						showall();
						dc.SetTextColor(RGB(0,255,0));
						dc.TextOutW(450,100,_T("you succeed"));
						KillTimer(1);
					}
				}
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}
void CmineView::init()				//��ʼ��
{
	int i,j,x,y;
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
		{
			p[i][j].mine=p[i][j].dig=p[i][j].flag=false;
			p[i][j].num=0;
			p[i][j].p.SetPoint(i*20+1,j*20+1);
		}
	}
	srand(time(NULL));
	for(i=0;i<MINE;)
	{
		x=rand()%20;
		y=rand()%20;
		if(p[x][y].mine==false)
		{
			i++;
			p[x][y].mine=true;
		}
	}
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
		{
			if(!p[i][j].mine)
			{
			if(i-1>-1)
			{
				if(p[i-1][j].mine)
					p[i][j].num++;
				if(j-1>-1)
				{
					if(p[i-1][j-1].mine)
					p[i][j].num++;
				}
				if(j+1<20)
				{
					if(p[i-1][j+1].mine)
					p[i][j].num++;
				}
			}
			if(i+1<20)
			{
				if(p[i+1][j].mine)
					p[i][j].num++;
				if(j-1>-1)
				{
					if(p[i+1][j-1].mine)
					p[i][j].num++;
				}
				if(j+1<20)
				{
					if(p[i+1][j+1].mine)
					p[i][j].num++;
				}
			}
			if(j-1>-1)
			{
				if(p[i][j-1].mine)
				p[i][j].num++;
			}
			if(j+1<20)
			{
				if(p[i][j+1].mine)
				p[i][j].num++;
			}
			}
		}
	}
}
void CmineView::show(Cpoint q)
{
	CClientDC dc(this);
	if(q.mine)
	{
		CBrush brush(RGB(0,0,0));
		dc.SelectObject(&brush);
		dc.Ellipse(q.p.x+5,q.p.y+5,q.p.x+13,q.p.y+13);
	}
	else if(q.num==0)
	{
		CBrush brush(RGB(0,255,0));
		dc.SelectObject(&brush);
		dc.Rectangle(q.p.x,q.p.y,q.p.x+18,q.p.y+18);
	}
	else
	{
		switch(q.num)
		{
		case 1:dc.SetTextColor(RGB(255,102,0));break;
		case 2:dc.SetTextColor(RGB(0,0,255));break;
		case 3:dc.SetTextColor(RGB(255,0,0));break;
		case 4:dc.SetTextColor(RGB(255,255,0));break;
		case 5:dc.SetTextColor(RGB(0,255,255));break;
		case 6:dc.SetTextColor(RGB(255,0,255));break;
		case 7:dc.SetTextColor(RGB(138,43,226));break;
		case 8:dc.SetTextColor(RGB(127,255,212));break;
		default:break;
		}
		CString str;
		str.Format(_T("%d"),q.num);
		dc.TextOutW(q.p.x+5,q.p.y+1,str);
	}

}
void CmineView::showall()
{
	int i,j;
	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
			show(p[i][j]);
}
void CmineView::showsome(Cpoint q,int i,int j)
{
	if(i-1>-1)
	{
		if(!p[i-1][j].dig)
		{
			if(p[i-1][j].num==0)
			{
				p[i-1][j].dig=true;
				showsome(p[i-1][j],i-1,j);
			}
			show(p[i-1][j]);
			p[i-1][j].dig=true;
			m_num++;
		}
		if(j-1>-1)
		{
			if(!p[i-1][j-1].dig)
			{
				if(p[i-1][j-1].num==0)
				{
					p[i-1][j-1].dig=true;
					showsome(p[i-1][j-1],i-1,j-1);
				}
				show(p[i-1][j-1]);
				p[i-1][j-1].dig=true;
				m_num++;
			}
		}
		if(j+1<20)
		{
			if(!p[i-1][j+1].dig)
			{
				if(p[i-1][j+1].num==0)
				{
					p[i-1][j+1].dig=true;	
					showsome(p[i-1][j+1],i-1,j+1);
				}
				show(p[i-1][j+1]);
				p[i-1][j+1].dig=true;	
				m_num++;
			}
		}
	}
	if(i+1<20)
	{
		if(!p[i+1][j].dig)
		{
			if(p[i+1][j].num==0)
			{
				p[i+1][j].dig=true;
				showsome(p[i+1][j],i+1,j);
			}
			show(p[i+1][j]);
			p[i+1][j].dig=true;
			m_num++;
		}
		if(j-1>-1)
		{
			if(!p[i+1][j-1].dig)
			{
				if(p[i+1][j-1].num==0)
				{
					p[i+1][j-1].dig=true;
					showsome(p[i+1][j-1],i+1,j-1);
				}
				show(p[i+1][j-1]);
				p[i+1][j-1].dig=true;
				m_num++;
			}
		}
		if(j+1<20)
		{
			if(!p[i+1][j+1].dig)
			{
				if(p[i+1][j+1].num==0)
				{
					p[i+1][j+1].dig=true;	
					showsome(p[i+1][j+1],i+1,j+1);
				}
				show(p[i+1][j+1]);
				p[i+1][j+1].dig=true;	
				m_num++;
			}
		}
	}
	if(j-1>-1)
	{
		if(!p[i][j-1].dig)
		{
			if(p[i][j-1].num==0)
			{
				p[i][j-1].dig=true;
				showsome(p[i][j-1],i,j-1);
			}
			show(p[i][j-1]);
			p[i][j-1].dig=true;
			m_num++;
		}
	}
	if(j+1<20)
	{
		if(!p[i][j+1].dig)
		{
			if(p[i][j+1].num==0)
			{
				p[i][j+1].dig=true;
				showsome(p[i][j+1],i,j+1);
			}
			show(p[i][j+1]);
			p[i][j+1].dig=true;
			m_num++;
		}
	}
}

void CmineView::OnE()
{
	// TODO: �ڴ���������������
	MINE=50;
	CClientDC dc(this);
	CString str;
	str.Format(_T("mine:%d  "),MINE);
	dc.SetTextColor(RGB(0,255,0));
	dc.TextOutW(450,75,str);
}


void CmineView::OnUpdateE(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(MINE==50||bagin)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CmineView::OnN()
{
	// TODO: �ڴ���������������
	MINE=100;
	CClientDC dc(this);
	CString str;
	str.Format(_T("mine:%d"),MINE);
	dc.SetTextColor(RGB(0,255,0));
	dc.TextOutW(450,75,str);
}


void CmineView::OnUpdateN(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(MINE==100||bagin)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CmineView::OnH()
{
	// TODO: �ڴ���������������
	MINE=200;
	CClientDC dc(this);
	CString str;
	str.Format(_T("mine:%d"),MINE);
	dc.SetTextColor(RGB(0,255,0));
	dc.TextOutW(450,75,str);
}


void CmineView::OnUpdateH(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(MINE==200||bagin)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}
void CmineView::ONSTARTDOWN()
{
	if(life&&!bagin)
	{
		SetTimer(1,1000,NULL);
		bagin=true;
		init();
	}
}
void CmineView::ONRSTARTDOWN()
{
	set();
	CmineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UpdateAllViews(NULL);
}