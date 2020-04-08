
// KEYBOARDView.cpp : CKEYBOARDView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "KEYBOARD.h"
#endif

#include "KEYBOARDDoc.h"
#include "KEYBOARDView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKEYBOARDView

IMPLEMENT_DYNCREATE(CKEYBOARDView, CView)

BEGIN_MESSAGE_MAP(CKEYBOARDView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKEYBOARDView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CKEYBOARDView ����/����

CKEYBOARDView::CKEYBOARDView()
{
	// TODO: �ڴ˴���ӹ������
	shiftup=shiftdown=shiftb=left=false;
	m_num=0;
}

CKEYBOARDView::~CKEYBOARDView()
{
}

BOOL CKEYBOARDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CKEYBOARDView ����

void CKEYBOARDView::OnDraw(CDC* pDC)
{
	CKEYBOARDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(shiftdown)//������Shift��	
	{
		pDC->TextOut(20,20,_T("�û�������Shift��!"));
	}
	if(shiftup)//�ͷ���Shift��    
	{
		pDC->TextOut(20,20,_T("�û��ͷ���Shift��!"));
	}
	if(shiftb)//ͬʱ������Shift����B�� 
	{
		pDC->TextOut(20,20,_T("�û�ͬʱ����Shift����B��!"));
		shiftb=false;
	}
	CString str;
	str.Format(_T("%d"),m_num);
	pDC->TextOutW(400,400,str);
	//MessageBox(_T("���û����ַ���B"));	
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CKEYBOARDView ��ӡ


void CKEYBOARDView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKEYBOARDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CKEYBOARDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CKEYBOARDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CKEYBOARDView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKEYBOARDView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKEYBOARDView ���

#ifdef _DEBUG
void CKEYBOARDView::AssertValid() const
{
	CView::AssertValid();
}

void CKEYBOARDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKEYBOARDDoc* CKEYBOARDView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKEYBOARDDoc)));
	return (CKEYBOARDDoc*)m_pDocument;
}
#endif //_DEBUG


// CKEYBOARDView ��Ϣ�������


void CKEYBOARDView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nChar==VK_SHIFT)//�ж�Shift���Ƿ񱻰���
	{
		shiftup=true;
		shiftdown=false;
	}
	else if(nChar==VK_LEFT)
	{
		left=false;
	}
	Invalidate(true);//��ʾ��Ϣ		
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CKEYBOARDView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nChar==VK_SHIFT)//�ж�Shift���Ƿ��ͷ�
	{
		shiftdown=true;
		shiftup=false;
	}	
	else if(nChar==VK_LEFT)
	{
		left=true;
		m_num++;
	}
	Invalidate(true);  //��ʾ��Ϣ
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CKEYBOARDView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if((nChar=='b')||(nChar=='B'))
	//if((nChar==66)||(nChar==98))
    {
		if(shiftdown)
		{
			shiftb=true;
			shiftdown=false;
			Invalidate(true);   
		}	
	}	

	CView::OnChar(nChar, nRepCnt, nFlags);
}
