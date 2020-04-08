
// colortextView.cpp : CcolortextView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CcolortextView 构造/析构

CcolortextView::CcolortextView()
{
	// TODO: 在此处添加构造代码
	m_color=RGB(255,0,0);
}

CcolortextView::~CcolortextView()
{
}

BOOL CcolortextView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CcolortextView 绘制

void CcolortextView::OnDraw(CDC* /*pDC*/)
{
	CcolortextDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	

	// TODO: 在此处为本机数据添加绘制代码
}


// CcolortextView 打印


void CcolortextView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CcolortextView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CcolortextView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CcolortextView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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
	menupopup.AppendMenuW(MF_STRING,ID_RED,_T("红色\tCtrl+R"));
	menupopup.AppendMenuW(MF_STRING,ID_GREEN,_T("绿色\tCtrl+G"));
	menupopup.AppendMenuW(MF_STRING,ID_BLUE,_T("蓝色\tCtrl+B"));
	menupopup.AppendMenuW(MF_STRING,ID_PURPLE,_T("紫色\tCtrl+P"));
	menupopup.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);			//显示菜单
	}
}


// CcolortextView 诊断

#ifdef _DEBUG
void CcolortextView::AssertValid() const
{
	CView::AssertValid();
}

void CcolortextView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcolortextDoc* CcolortextView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcolortextDoc)));
	return (CcolortextDoc*)m_pDocument;
}
#endif //_DEBUG


// CcolortextView 消息处理程序


void CcolortextView::OnRed()
{
	// TODO: 在此添加命令处理程序代码
	m_color=RGB(255,0,0);
	showcolor();
}


void CcolortextView::OnUpdateRed(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(m_color==RGB(255,0,0))
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CcolortextView::OnBlue()
{
	// TODO: 在此添加命令处理程序代码
	m_color=RGB(0,0,255);
	showcolor();
}


void CcolortextView::OnUpdateBlue(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(m_color==RGB(0,0,255))
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CcolortextView::OnGreen()
{
	// TODO: 在此添加命令处理程序代码
	m_color=RGB(0,255,0);
	showcolor();
}


void CcolortextView::OnUpdateGreen(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(m_color==RGB(0,255,0))
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CcolortextView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString s;
	s.Format(_T("点击坐标为： (%d，%d)"),point.x,point.y);
	CClientDC dc(this);
	dc.SetTextColor(m_color);
	dc.TextOutW(point.x,point.y,s);
	/*CString strcolor;
	CMFCStatusBar* pStatus=(CMFCStatusBar* )AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	if(pStatus)
	{
		if(m_color==RGB(255,0,0))
			strcolor=_T("红色");
		else if(m_color==RGB(0,255,0))
			strcolor=_T("绿色");
		else if(m_color==RGB(0,0,255))
			strcolor=_T("蓝色");
		else if(m_color==RGB(153,0,102))
			strcolor=_T("紫色");
		pStatus->SetPaneWidth(1,500);
		pStatus->SetPaneTextColor(3,m_color);
	    pStatus->SetPaneText(1,_T("颜色：")+strcolor);
	}*/
	CView::OnLButtonUp(nFlags, point);
}


void CcolortextView::OnPurple()
{
	// TODO: 在此添加命令处理程序代码
	m_color=RGB(153,0,102);
	showcolor();
}


void CcolortextView::OnUpdatePurple(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
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
			strcolor=_T("红色");
		else if(m_color==RGB(0,255,0))
			strcolor=_T("绿色");
		else if(m_color==RGB(0,0,255))
			strcolor=_T("蓝色");
		else if(m_color==RGB(153,0,102))
			strcolor=_T("紫色");
		pStatus->SetPaneWidth(1,100);
		pStatus->SetPaneWidth(2,100);
		pStatus->SetPaneTextColor(1,m_color);
		pStatus->SetPaneBackgroundColor(2,m_color);
	    pStatus->SetPaneText(1,_T("颜色：")+strcolor);
	}
}

