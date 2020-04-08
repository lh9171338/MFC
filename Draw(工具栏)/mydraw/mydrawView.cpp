
// mydrawView.cpp : CmydrawView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CmydrawView 构造/析构

CmydrawView::CmydrawView()
{
	// TODO: 在此处添加构造代码
	m_color=(RGB(255,0,0));
	m_bdrag=false;
	m_hcross=AfxGetApp()->LoadStandardCursor(IDC_CROSS);	//	获得十字光标
}

CmydrawView::~CmydrawView()
{
}

BOOL CmydrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CmydrawView 绘制

void CmydrawView::OnDraw(CDC* pDC)
{
	CmydrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	int n=pDoc->getnumline();
	//TRACE("n1=%d",n);									//调试时用
	while(n--)
	{
		//TRACE("n2=%d",n);
		pDoc->getline(n)->drawline(pDC);
	}
}


// CmydrawView 打印


void CmydrawView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CmydrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CmydrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CmydrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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
		menupopup.AppendMenuW(MF_STRING,ID_RED,_T("红色\tCtrl+R"));
		menupopup.AppendMenuW(MF_STRING,ID_GREEN,_T("绿色\tCtrl+G"));
		menupopup.AppendMenuW(MF_STRING,ID_BLUE,_T("蓝色\tCtrl+B"));
		menupopup.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);			//显示菜单
	}
}


// CmydrawView 诊断

#ifdef _DEBUG
void CmydrawView::AssertValid() const
{
	CView::AssertValid();
}

void CmydrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmydrawDoc* CmydrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmydrawDoc)));
	return (CmydrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CmydrawView 消息处理程序


void CmydrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCapture();
	::SetCursor(m_hcross);
	m_pstart=point;
	m_bdrag=true;
	//CView::OnLButtonDown(nFlags, point);
}


void CmydrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bdrag)
	{
		CmydrawDoc* pDoc=GetDocument();
		ASSERT_VALID(pDoc);								//测试文档对象是否运行有效
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bdrag)
	{
		m_bdrag=false;
		ReleaseCapture();
	}
	//CView::OnLButtonUp(nFlags, point);
}


void CmydrawView::OnRed()
{
	// TODO: 在此添加命令处理程序代码
	m_color=(RGB(255,0,0));
}


void CmydrawView::OnGreen()
{
	// TODO: 在此添加命令处理程序代码
	m_color=(RGB(0,255,0));
}


void CmydrawView::OnBlue()
{
	// TODO: 在此添加命令处理程序代码
	m_color=(RGB(0,0,255));
}
