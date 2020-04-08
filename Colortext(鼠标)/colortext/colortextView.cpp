
// colortextView.cpp : CcolortextView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "colortext.h"
#endif

#include "colortextDoc.h"
#include "colortextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcolortextView

IMPLEMENT_DYNCREATE(CcolortextView, CView)

BEGIN_MESSAGE_MAP(CcolortextView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CcolortextView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_RED, &CcolortextView::OnRed)
	ON_UPDATE_COMMAND_UI(ID_RED, &CcolortextView::OnUpdateRed)
	ON_COMMAND(ID_BLUE, &CcolortextView::OnBlue)
	ON_UPDATE_COMMAND_UI(ID_BLUE, &CcolortextView::OnUpdateBlue)
	ON_COMMAND(ID_GREEN, &CcolortextView::OnGreen)
	ON_UPDATE_COMMAND_UI(ID_GREEN, &CcolortextView::OnUpdateGreen)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_PURPLE, &CcolortextView::OnPurple)
	ON_UPDATE_COMMAND_UI(ID_PURPLE, &CcolortextView::OnUpdatePurple)
END_MESSAGE_MAP()

// CcolortextView ����/����

CcolortextView::CcolortextView()
{
	// TODO: �ڴ˴���ӹ������
	m_color=RGB(255,0,0);
}

CcolortextView::~CcolortextView()
{
}

BOOL CcolortextView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CcolortextView ����

void CcolortextView::OnDraw(CDC* /*pDC*/)
{
	CcolortextDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CcolortextView ��ӡ


void CcolortextView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CcolortextView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CcolortextView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CcolortextView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CcolortextView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CcolortextView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
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
	menupopup.AppendMenuW(MF_STRING,ID_PURPLE,_T("��ɫ\tCtrl+P"));
	menupopup.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);			//��ʾ�˵�
	}
}


// CcolortextView ���

#ifdef _DEBUG
void CcolortextView::AssertValid() const
{
	CView::AssertValid();
}

void CcolortextView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcolortextDoc* CcolortextView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcolortextDoc)));
	return (CcolortextDoc*)m_pDocument;
}
#endif //_DEBUG


// CcolortextView ��Ϣ�������


void CcolortextView::OnRed()
{
	// TODO: �ڴ���������������
	m_color=RGB(255,0,0);
	showcolor();
}


void CcolortextView::OnUpdateRed(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(m_color==RGB(255,0,0))
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CcolortextView::OnBlue()
{
	// TODO: �ڴ���������������
	m_color=RGB(0,0,255);
	showcolor();
}


void CcolortextView::OnUpdateBlue(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(m_color==RGB(0,0,255))
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CcolortextView::OnGreen()
{
	// TODO: �ڴ���������������
	m_color=RGB(0,255,0);
	showcolor();
}


void CcolortextView::OnUpdateGreen(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(m_color==RGB(0,255,0))
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CcolortextView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString s;
	s.Format(_T("�������Ϊ�� (%d��%d)"),point.x,point.y);
	CClientDC dc(this);
	dc.SetTextColor(m_color);
	dc.TextOutW(point.x,point.y,s);
	/*CString strcolor;
	CMFCStatusBar* pStatus=(CMFCStatusBar* )AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	if(pStatus)
	{
		if(m_color==RGB(255,0,0))
			strcolor=_T("��ɫ");
		else if(m_color==RGB(0,255,0))
			strcolor=_T("��ɫ");
		else if(m_color==RGB(0,0,255))
			strcolor=_T("��ɫ");
		else if(m_color==RGB(153,0,102))
			strcolor=_T("��ɫ");
		pStatus->SetPaneWidth(1,500);
		pStatus->SetPaneTextColor(3,m_color);
	    pStatus->SetPaneText(1,_T("��ɫ��")+strcolor);
	}*/
	CView::OnLButtonUp(nFlags, point);
}


void CcolortextView::OnPurple()
{
	// TODO: �ڴ���������������
	m_color=RGB(153,0,102);
	showcolor();
}


void CcolortextView::OnUpdatePurple(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(m_color==RGB(153,0,102))
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}
void CcolortextView::showcolor()
{
	CString strcolor;
	CMFCStatusBar* pStatus=(CMFCStatusBar* )AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	if(pStatus)
	{
		if(m_color==RGB(255,0,0))
			strcolor=_T("��ɫ");
		else if(m_color==RGB(0,255,0))
			strcolor=_T("��ɫ");
		else if(m_color==RGB(0,0,255))
			strcolor=_T("��ɫ");
		else if(m_color==RGB(153,0,102))
			strcolor=_T("��ɫ");
		pStatus->SetPaneWidth(1,100);
		pStatus->SetPaneWidth(2,100);
		pStatus->SetPaneTextColor(1,m_color);
		pStatus->SetPaneBackgroundColor(2,m_color);
	    pStatus->SetPaneText(1,_T("��ɫ��")+strcolor);
	}
}

