
// mydrawView.cpp : CmydrawView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "mydraw.h"
#endif

#include "mydrawDoc.h"
#include "mydrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmydrawView

IMPLEMENT_DYNCREATE(CmydrawView, CView)

BEGIN_MESSAGE_MAP(CmydrawView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CmydrawView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_RED, &CmydrawView::OnRed)
	ON_COMMAND(ID_GREEN, &CmydrawView::OnGreen)
	ON_COMMAND(ID_BLUE, &CmydrawView::OnBlue)
END_MESSAGE_MAP()

// CmydrawView ����/����

CmydrawView::CmydrawView()
{
	// TODO: �ڴ˴���ӹ������
	m_color=(RGB(255,0,0));
	m_bdrag=false;
	m_hcross=AfxGetApp()->LoadStandardCursor(IDC_CROSS);	//	���ʮ�ֹ��
}

CmydrawView::~CmydrawView()
{
}

BOOL CmydrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CmydrawView ����

void CmydrawView::OnDraw(CDC* pDC)
{
	CmydrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	int n=pDoc->getnumline();
	//TRACE("n1=%d",n);									//����ʱ��
	while(n--)
	{
		//TRACE("n2=%d",n);
		pDoc->getline(n)->drawline(pDC);
	}
}


// CmydrawView ��ӡ


void CmydrawView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CmydrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CmydrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CmydrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CmydrawView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CmydrawView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	CMenu menupopup;
	if(menupopup.CreatePopupMenu())
	{
		menupopup.AppendMenuW(MF_STRING,ID_RED,_T("��ɫ\tCtrl+R"));
		menupopup.AppendMenuW(MF_STRING,ID_GREEN,_T("��ɫ\tCtrl+G"));
		menupopup.AppendMenuW(MF_STRING,ID_BLUE,_T("��ɫ\tCtrl+B"));
		menupopup.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);			//��ʾ�˵�
	}
}


// CmydrawView ���

#ifdef _DEBUG
void CmydrawView::AssertValid() const
{
	CView::AssertValid();
}

void CmydrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmydrawDoc* CmydrawView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmydrawDoc)));
	return (CmydrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CmydrawView ��Ϣ�������


void CmydrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetCapture();
	::SetCursor(m_hcross);
	m_pstart=point;
	m_bdrag=true;
	//CView::OnLButtonDown(nFlags, point);
}


void CmydrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bdrag)
	{
		CmydrawDoc* pDoc=GetDocument();
		ASSERT_VALID(pDoc);								//�����ĵ������Ƿ�������Ч
		pDoc->addline(m_pstart,point,m_color);

		CPen pen(PS_SOLID,1,m_color);
		CClientDC dc(this);
		dc.SelectObject(&pen);
		dc.MoveTo(m_pstart);
		dc.LineTo(point);
		m_pstart=point;
	}
	//CView::OnMouseMove(nFlags, point);
}


void CmydrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bdrag)
	{
		m_bdrag=false;
		ReleaseCapture();
	}
	//CView::OnLButtonUp(nFlags, point);
}


void CmydrawView::OnRed()
{
	// TODO: �ڴ���������������
	m_color=(RGB(255,0,0));
}


void CmydrawView::OnGreen()
{
	// TODO: �ڴ���������������
	m_color=(RGB(0,255,0));
}


void CmydrawView::OnBlue()
{
	// TODO: �ڴ���������������
	m_color=(RGB(0,0,255));
}
