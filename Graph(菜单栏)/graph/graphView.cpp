
// graphView.cpp : CgraphView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "graph.h"
#include<cmath>
#endif

#include "graphDoc.h"
#include "graphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CgraphView

IMPLEMENT_DYNCREATE(CgraphView, CView)

BEGIN_MESSAGE_MAP(CgraphView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CgraphView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_RECT, &CgraphView::OnRect)
	ON_COMMAND(ID_CIRCLE, &CgraphView::OnCircle)
	ON_COMMAND(ID_BIGGER, &CgraphView::OnBigger)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BLUE, &CgraphView::OnBlue)
	ON_COMMAND(ID_GREEN, &CgraphView::OnGreen)
	ON_COMMAND(ID_RED, &CgraphView::OnRed)
	ON_COMMAND(ID_SMALLER, &CgraphView::OnSmaller)
END_MESSAGE_MAP()

// CgraphView ����/����

CgraphView::CgraphView()
{
	// TODO: �ڴ˴���ӹ������
	m_drag=false;
	m_time=false;
	m_color=RGB(0,0,0);
	m_sign=0;
	m_rate=1;
	m_hcross=AfxGetApp()->LoadStandardCursor(IDC_CROSS);
}

CgraphView::~CgraphView()
{
}

BOOL CgraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CgraphView ����

void CgraphView::OnDraw(CDC* pDC)
{
	int i,n;
	CgraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	n=pDoc->getnumcircle();
	i=0;
	while(i<n)
	{
		pDoc->getcircle(i++)->drawcircle(pDC,m_rate);
	}
	n=pDoc->getnumrectange();
	i=0;
	while(i<n)
	{
		pDoc->getrectange(i++)->drawrectange(pDC,m_rate);
	}
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if(m_drag)
	{
		CPen pen(PS_SOLID,1,m_color);
		pDC->SelectObject(&pen);
		switch(m_sign)
		{
			case 1:pDC->Rectangle(m_p1.x,m_p1.y,m_p2.x,m_p2.y);break;
			case 2:pDC->Ellipse(m_p2.x,m_p2.y,m_p3.x,m_p3.y);break;
			default:break;
		}
	}
	m_rate=1;
}


// CgraphView ��ӡ


void CgraphView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CgraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CgraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CgraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CgraphView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CgraphView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CgraphView ���

#ifdef _DEBUG
void CgraphView::AssertValid() const
{
	CView::AssertValid();
}

void CgraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CgraphDoc* CgraphView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CgraphDoc)));
	return (CgraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CgraphView ��Ϣ�������


void CgraphView::OnRect()
{
	// TODO: �ڴ���������������
	m_sign=1;
}

void CgraphView::OnCircle()
{
	// TODO: �ڴ���������������
	m_sign=2;
}
void CgraphView::OnBigger()
{
	// TODO: �ڴ���������������
	m_rate=2;
	CgraphDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->UpdateAllViews(NULL);
}


void CgraphView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetCapture();
	::SetCursor(m_hcross);
	m_p1=point;
	m_drag=true;
	CView::OnLButtonDown(nFlags, point);
}


void CgraphView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_drag)
	{
		m_drag=false;
		if(m_time)
		{
			CgraphDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			switch(m_sign)
			{
			case 1:pDoc->addrectange(m_p1,m_p2,m_color);break;
			case 2:pDoc->addcircle(m_p2,m_p3,m_color);break;
			default:break;
			}
		}
		m_time=false;
		ReleaseCapture();
	}
	CView::OnLButtonUp(nFlags, point);
}


void CgraphView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_drag)
	{
		m_time=true;
		int r;
		switch(m_sign)
		{
			case 1:m_p2=point;break;
			case 2:r=(int)sqrt((double)(m_p1.x-point.x)*(m_p1.x-point.x)+(double)(m_p1.y-point.y)*(m_p1.y-point.y));
					   m_p2.x=m_p1.x-r;
					   m_p2.y=m_p1.y-r;
					   m_p3.x=m_p1.x+r;
					   m_p3.y=m_p1.y+r;
					   break;
			default:break;
		}
		CgraphDoc* pDoc=GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->UpdateAllViews(NULL);
	}
	//CView::OnMouseMove(nFlags, point);
}


void CgraphView::OnBlue()
{
	// TODO: �ڴ���������������
	m_color=RGB(0,0,255);
}


void CgraphView::OnGreen()
{
	// TODO: �ڴ���������������
	m_color=RGB(0,255,0);
}


void CgraphView::OnRed()
{
	// TODO: �ڴ���������������
	m_color=RGB(255,0,0);
}


void CgraphView::OnSmaller()
{
	// TODO: �ڴ���������������
	m_rate=0.5;
	CgraphDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->UpdateAllViews(NULL);
}
