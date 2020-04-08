
// exmpcomboView.cpp : CexmpcomboView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CexmpcomboView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CexmpcomboView 构造/析构

CexmpcomboView::CexmpcomboView()
{
	// TODO: 在此处添加构造代码

}

CexmpcomboView::~CexmpcomboView()
{
}

BOOL CexmpcomboView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CexmpcomboView 绘制

void CexmpcomboView::OnDraw(CDC* /*pDC*/)
{
	CexmpcomboDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CexmpcomboView 打印


void CexmpcomboView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CexmpcomboView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CexmpcomboView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CexmpcomboView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CexmpcomboView 诊断

#ifdef _DEBUG
void CexmpcomboView::AssertValid() const
{
	CView::AssertValid();
}

void CexmpcomboView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CexmpcomboDoc* CexmpcomboView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CexmpcomboDoc)));
	return (CexmpcomboDoc*)m_pDocument;
}
#endif //_DEBUG


// CexmpcomboView 消息处理程序
