
// exmpcomboView.cpp : CexmpcomboView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "exmpcombo.h"
#endif

#include "exmpcomboDoc.h"
#include "exmpcomboView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CexmpcomboView

IMPLEMENT_DYNCREATE(CexmpcomboView, CView)

BEGIN_MESSAGE_MAP(CexmpcomboView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CexmpcomboView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CexmpcomboView ����/����

CexmpcomboView::CexmpcomboView()
{
	// TODO: �ڴ˴���ӹ������

}

CexmpcomboView::~CexmpcomboView()
{
}

BOOL CexmpcomboView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CexmpcomboView ����

void CexmpcomboView::OnDraw(CDC* /*pDC*/)
{
	CexmpcomboDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CexmpcomboView ��ӡ


void CexmpcomboView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CexmpcomboView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CexmpcomboView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CexmpcomboView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CexmpcomboView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CexmpcomboView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CexmpcomboView ���

#ifdef _DEBUG
void CexmpcomboView::AssertValid() const
{
	CView::AssertValid();
}

void CexmpcomboView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CexmpcomboDoc* CexmpcomboView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CexmpcomboDoc)));
	return (CexmpcomboDoc*)m_pDocument;
}
#endif //_DEBUG


// CexmpcomboView ��Ϣ�������
