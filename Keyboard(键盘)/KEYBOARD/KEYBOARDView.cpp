
// KEYBOARDView.cpp : CKEYBOARDView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKEYBOARDView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CKEYBOARDView 构造/析构

CKEYBOARDView::CKEYBOARDView()
{
	// TODO: 在此处添加构造代码
	shiftup=shiftdown=shiftb=left=false;
	m_num=0;
}

CKEYBOARDView::~CKEYBOARDView()
{
}

BOOL CKEYBOARDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CKEYBOARDView 绘制

void CKEYBOARDView::OnDraw(CDC* pDC)
{
	CKEYBOARDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(shiftdown)//按下了Shift键	
	{
		pDC->TextOut(20,20,_T("用户按下了Shift键!"));
	}
	if(shiftup)//释放了Shift键    
	{
		pDC->TextOut(20,20,_T("用户释放了Shift键!"));
	}
	if(shiftb)//同时按下了Shift键和B键 
	{
		pDC->TextOut(20,20,_T("用户同时按下Shift键和B键!"));
		shiftb=false;
	}
	CString str;
	str.Format(_T("%d"),m_num);
	pDC->TextOutW(400,400,str);
	//MessageBox(_T("你敲击了字符键B"));	
	// TODO: 在此处为本机数据添加绘制代码
}


// CKEYBOARDView 打印


void CKEYBOARDView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKEYBOARDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CKEYBOARDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CKEYBOARDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CKEYBOARDView 诊断

#ifdef _DEBUG
void CKEYBOARDView::AssertValid() const
{
	CView::AssertValid();
}

void CKEYBOARDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKEYBOARDDoc* CKEYBOARDView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKEYBOARDDoc)));
	return (CKEYBOARDDoc*)m_pDocument;
}
#endif //_DEBUG


// CKEYBOARDView 消息处理程序


void CKEYBOARDView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nChar==VK_SHIFT)//判断Shift键是否被按下
	{
		shiftup=true;
		shiftdown=false;
	}
	else if(nChar==VK_LEFT)
	{
		left=false;
	}
	Invalidate(true);//显示信息		
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CKEYBOARDView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nChar==VK_SHIFT)//判断Shift键是否被释放
	{
		shiftdown=true;
		shiftup=false;
	}	
	else if(nChar==VK_LEFT)
	{
		left=true;
		m_num++;
	}
	Invalidate(true);  //显示信息
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CKEYBOARDView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
