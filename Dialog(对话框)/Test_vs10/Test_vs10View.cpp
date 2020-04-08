
// Test_vs10View.cpp : implementation of the CTest_vs10View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Test_vs10.h"
#endif

#include "Test_vs10Doc.h"
#include "Test_vs10View.h"
#include "Example.h"
#include "DlgButton.h"
//#include "ClorDlg.h"
#include "ExampListDlg.h"
#include "ComboDlg.h"
#include "Dlgex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CTest_vs10View

IMPLEMENT_DYNCREATE(CTest_vs10View, CView)

BEGIN_MESSAGE_MAP(CTest_vs10View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTest_vs10View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_DRAW, &CTest_vs10View::OnEditDraw)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CHAR()
	ON_COMMAND(ID_VIEW_SHOWDLG, &CTest_vs10View::OnViewShowdlg)
	ON_COMMAND(IDC_COMBODEMO, &CTest_vs10View::OnCombodemo)
	ON_COMMAND(ID_EDIT_RADIUS, &CTest_vs10View::OnEditRadius)
	ON_COMMAND(IDC_COLORDLG, &CTest_vs10View::OnColordlg)
	ON_COMMAND(ID_LISTDEMO, &CTest_vs10View::OnListdemo)
	ON_COMMAND(ID_VIEW_RADIUS, &CTest_vs10View::OnViewRadius)
	ON_MESSAGE(WM_MYMESSAGE, OnMyMessage)
END_MESSAGE_MAP()

// CTest_vs10View construction/destruction

CTest_vs10View::CTest_vs10View()
{
	// TODO: add construction code here
	m_bKill = true;

	/*m_bDragging=false;  // 初始化拖拽标记	
	// 获得十字光标句柄
	m_hCross=AfxGetApp()->
		     LoadStandardCursor(IDC_CROSS);

	int penstyle[7] = {PS_SOLID,       
	PS_DASH  ,      
	PS_DOT ,        
	PS_DASHDOT  ,   
	PS_DASHDOTDOT , 
	PS_NULL    ,    
	PS_INSIDEFRAME };

	int penwi[7]={1,2,3,4,5,6,7};
	COLORREF col[7];
	col[0]=RGB(255,0,0);
	col[1]= RGB(0,255,0);
	col[2]=RGB(0,0,255);
	col[3]=RGB(255,255,0);
	col[4]=RGB(255,0,255);
	col[5]=RGB(0,255,255);
	col[6]=RGB(192,192,192);
	

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 7; j++)
		{
			switch(i)
			{
			case 0:
				penary[i][j].CreatePen(penstyle[j], 1, RGB(0,0,0));
				break;
			case 1:
				penary[i][j].CreatePen(penstyle[0], penwi[j], RGB(0,0,0));
				break;
			case 2:
				
				penary[i][j].CreatePen(penstyle[0], penwi[3], col[j]);
				break;
			default:
				;//penary[i][j].CreatePen(penstyle[0], penwi[j], col[j]);


			}
			

		}
	}

	*/
	m_nRadius = 0;

}

CTest_vs10View::~CTest_vs10View()
{
}

BOOL CTest_vs10View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTest_vs10View drawing

void CTest_vs10View::OnDraw(CDC* pDC)
{
	CTest_vs10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

/*	CClientDC dc(this);
	CString  str;
	str.Format(_T("%d"),pDoc->m_nCount);
	dc.TextOut(100,200,str);
	str.Format(_T("%d"),pDoc->m_max);
	dc.TextOut(100,100,str);*/

/*	pDC->SetMapMode(MM_TEXT); 
	pDC->Rectangle(CRect(50, 50, 100, 100));

	
	pDC->SetWindowOrg(50, 50); //屏幕左上角点坐标
	pDC->Rectangle(CRect(50, 50, 100, 100));

	pDC->SetViewportOrg(50,50); //输出的坐标原点
	pDC->Rectangle(CRect(50, 50, 100, 100));


	pDC->SetViewportOrg(50,50);
	pDC->SetWindowOrg(50, 50);
	pDC->Rectangle(CRect(50, 50, 100, 100));
*/
	

	/*CString strVer[3]= {_T("Using different stytle"), _T("Using different width"), 
		_T("Using different color")};
	CString str[3][7]= {_T("SOLID"), _T("DOT"),_T("DASH"), _T("DASHDOT"),_T("PS_DASHDOTDOT"),_T("PS_NULL"),_T("PS_INSIDEFRAME"),
		_T("1"), _T("2"),_T("3"), _T("4"),_T("5"),_T("6"),_T("7"),
		_T("红"), _T("绿"),_T("蓝"), _T("黄"),_T("紫"),_T("青"),_T("灰"),};
	 
	

	//CPen pen;//(penstyle, 2, RGB(255, 0,0));
	CPen* poldpen = NULL;//pDC->SelectObject(&pen);
	

	int ix = 200; int iy= 80;
	int ilinesx = 100;int ilinesy = 120;
	int noftx = 100;int nofty = 100;
	int nLineoftx = 160;
	int nLineofty = 30;
	int nCeny = 5;
	int nHorioftx = 300;
	for(int i = 0; i < 3; i++)
	{
		pDC->TextOutW(ix+ i * (nHorioftx+50), iy, strVer[i] );
		if(i == 2)
			pDC->TextOutW(ix+ i * (nHorioftx+50)- 100, iy, strVer[i] );
			
		for(int j = 0; j < 7; j++)
		{
			switch(i)
			{
			case 0:
				pDC->TextOutW(ilinesx+ i * nHorioftx, ilinesy + j*nLineofty, str[i][j]);

				poldpen = pDC->SelectObject(&penary[i][j]);

				pDC->MoveTo(ilinesx + nLineoftx+ i * nHorioftx, ilinesy+ j*nLineofty + nCeny);
				pDC->LineTo(ilinesx+nLineoftx + 150+ i * nHorioftx, ilinesy+ j*nLineofty+ nCeny);
				pDC->SelectObject(poldpen);
				break;
			case 1:
				pDC->TextOutW(ilinesx+ i * nHorioftx + 100, ilinesy + j*nLineofty, str[i][j]);

				poldpen = pDC->SelectObject(&penary[i][j]);

				pDC->MoveTo(ilinesx + nLineoftx+ i * nHorioftx, ilinesy+ j*nLineofty + nCeny);
				pDC->LineTo(ilinesx+nLineoftx + 150+ i * nHorioftx, ilinesy+ j*nLineofty+ nCeny);
				pDC->SelectObject(poldpen);
				break;
			case 2:
				pDC->TextOutW(ilinesx+ i * nHorioftx + 100, ilinesy + j*nLineofty, str[i][j]);

				poldpen = pDC->SelectObject(&penary[i][j]);

				pDC->MoveTo(ilinesx + nLineoftx+ i * nHorioftx , ilinesy+ j*nLineofty + nCeny);
				pDC->LineTo(ilinesx+nLineoftx + 150+ i * nHorioftx, ilinesy+ j*nLineofty+ nCeny);
				pDC->SelectObject(poldpen);
				break;
				
			default:
				;


			}
			

			

		}
	}
	*/

	/*POINT pt[15];
	pt[0].x = 100;pt[0].y = 100;
	pt[1].x = 200;pt[1].y = 30;
	pt[2].x = 300;pt[2].y = 200;
	pt[3].x = 230;pt[3].y = 280;
	pt[4].x = 160;pt[4].y = 268;

	pDC->Polyline(pt, 5);

	int ny = 200;
	pt[0].x = 100;pt[0].y = 100+ ny;
	pt[1].x = 200;pt[1].y = 30+ ny;
	pt[2].x = 300;pt[2].y = 200+ ny;
	pt[3].x = 230;pt[3].y = 280+ ny;
	pt[4].x = 160;pt[4].y = 268+ ny;
	pt[5].x = 160;pt[5].y = 268+ ny;
	pt[6].x = 160;pt[6].y = 268+ ny;

	pDC->PolyBezier(pt, 4);

	int nx = 200; ny = 0;
	pt[0].x = 140+nx;pt[0].y = 200+ ny;
	pt[1].x = 200+nx;pt[1].y = 30+ ny;
	pt[2].x = 300+nx;pt[2].y = 200+ ny;
	pt[3].x = 450+nx;pt[3].y = 100+ ny;
	pDC->PolyBezier(pt, 4);

	CBrush brush;
brush.CreateSolidBrush(RGB(192, 192, 192));
//保存旧画刷
CBrush *pOldBrush = pDC->SelectObject(&brush);
//画图：画矩形

	nx += 400;
	pt[0].x = 140+nx;pt[0].y = 200+ ny;
	pt[1].x = 200+nx;pt[1].y = 30+ ny;
	pt[2].x = 300+nx-80;pt[2].y = 200+ ny;
	pt[3].x = 450+nx-80;pt[3].y = 100+ ny;
	pDC->Rectangle(pt[0].x,pt[0].y, pt[3].x, pt[3].y);

	ny += 200;
	pt[0].x = 140+nx;pt[0].y = 200+ ny;
	pt[1].x = 200+nx;pt[1].y = 30+ ny;
	pt[2].x = 300+nx-80;pt[2].y = 200+ ny;
	pt[3].x = 450+nx-80;pt[3].y = 100+ ny;
	
	CRect rect(pt[0], pt[3]);

	pDC->Chord( &rect, pt[0], pt[3] );

	nx -= 200;
	pt[0].x = 140+nx;pt[0].y = 200+ ny;
	pt[1].x = 200+nx;pt[1].y = 30+ ny;
	pt[2].x = 300+nx-80;pt[2].y = 200+ ny;
	pt[3].x = 450+nx-80;pt[3].y = 100+ ny;
	
	CRect rect1(pt[0], pt[3]);

	pDC->Ellipse( &rect1 );

	nx-=268;
	pt[0].x = 140+nx;pt[0].y = 200+ ny;
	pt[1].x = 200+nx;pt[1].y = 30+ ny;
	pt[2].x = 300+nx-80;pt[2].y = 200+ ny;
	pt[3].x = 450+nx-80;pt[3].y = 100+ ny;
	pt[4].x = 450+nx-80;pt[3].y = 100+ ny;
	
	
	pDC->Polygon(pt, 5);
	

	pDC->SelectObject(pOldBrush);
//销毁画刷
brush.DeleteObject();
*/



//pDC->TextOut(100, 100, _T("使用公用字体对话框."));

     pDC->Ellipse(100 -m_nRadius, 100 - m_nRadius, 
		                       100 +m_nRadius, 100 + m_nRadius );



	// TODO: add draw code for native data here
}


// CTest_vs10View printing


void CTest_vs10View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTest_vs10View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTest_vs10View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTest_vs10View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTest_vs10View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTest_vs10View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{/*
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	*/
	CMenu   menuPopup;  // 声明菜单对象
	if (menuPopup.CreatePopupMenu())  // 创建弹出式菜单
	{
		// 向菜单menuPopup中添加菜单项
		menuPopup.AppendMenu(MF_STRING,
			ID_VIEW_SHOWDLG,_T( "蓝色(&B)\tCtrl+B"));
		menuPopup.AppendMenu(MF_STRING, 
			ID_VIEW_REBAR, _T("绿色(&B)\tCtrl+G"));
		menuPopup.TrackPopupMenu(TPM_LEFTALIGN,
			point.x, point.y, this);
	}

}


// CTest_vs10View diagnostics

#ifdef _DEBUG
void CTest_vs10View::AssertValid() const
{
	CView::AssertValid();
}

void CTest_vs10View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest_vs10Doc* CTest_vs10View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest_vs10Doc)));
	return (CTest_vs10Doc*)m_pDocument;
}
#endif //_DEBUG


// CTest_vs10View message handlers


void CTest_vs10View::OnEditDraw()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("terror"));

	
	if(m_bKill)
	{
		SetTimer(1,200,NULL);
		
	}
	else
	{
		KillTimer(1);

	}

	m_bKill = !m_bKill;
}


void CTest_vs10View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CTest_vs10Doc  *m_pDoc=GetDocument();

	switch( nIDEvent)
	{
	case 1:
		{
			m_pDoc->m_nCount++;

			Invalidate(FALSE);

			if(m_pDoc->m_nCount>=m_pDoc->m_max)
			{
				KillTimer(1);
				m_bKill = true;
			}
		}

		break;

	}


	CView::OnTimer(nIDEvent);
}


void CTest_vs10View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	SetTimer(1,200,NULL);

	m_bKill = false;


	// TODO: Add your specialized code here and/or call the base class
}


void CTest_vs10View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//SetCapture();  // 捕捉鼠标
/*	SetCursor(m_hCross);  	// 设置十字光标
	m_ptOrigin=point;
	m_bDragging=TRUE;  	// 设置拖拽标记	
	*/
	CClientDC dc(this);

	/*dc.SetWindowOrg(50, 50);

	dc.MoveTo(point.x - 5, point.y);
	dc.LineTo(point.x + 5, point.y);

	dc.MoveTo(point.x , point.y- 5);
	dc.LineTo(point.x, point.y + 5);*/

	CDlgex dlg;

	if(dlg.DoModal() ==IDOK)
	{
		m_nRadius = dlg.m_nRadius;
		Invalidate();
	
	}



	

	CView::OnLButtonDown(nFlags, point);
}


void CTest_vs10View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if(m_bDragging)
	{
	      m_bDragging=false;   	// 清拖拽标记	
	  //    ReleaseCapture();    // 释放鼠标，还原鼠标形状
	}


	CView::OnLButtonUp(nFlags, point);
}


void CTest_vs10View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if(m_bDragging)
	{
		/*CClientDC   dc(this);
		dc.MoveTo(m_ptOrigin); 
		dc.LineTo(point);  		// 绘制线段
		m_ptOrigin=point;  */		// 新的起始点

	/*	CWindowDC dc(NULL);
		CPoint pt1, pt2;*/
	
	
		

	}


	CView::OnMouseMove(nFlags, point);
}


void CTest_vs10View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CString str;
	str.Format(_T("%c"), nChar);

	/*if(nChar=='B') 
	{
          MessageBox(_T("你敲击了字符键B"));	
	}	
	*/
	CString strt=_T("你敲击了字符键");
	str = strt+str;
	
	//MessageBox(_T("你敲击了字符键B"));	
	MessageBox(str);	



	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CTest_vs10View::OnViewShowdlg()
{
	// TODO: Add your command handler code here

	//CExample dlg;
	//CDlgButton dlg;
	//CClorDlg dlg;
	/*CComboDlg dlg;

	if(dlg.DoModal() ==IDOK)
	{
		;
	}*/

	CFontDialog dlg;
	LOGFONT lf;
	if (dlg.DoModal() == IDOK)
	{
		
		dlg.GetCurrentFont(&lf);
		HFONT hfont = ::CreateFontIndirect(&lf);  
		
		// Convert the HFONT to CFont*.
		CFont* pfont = CFont::FromHandle(hfont);
		
		// Do something with the font just created...
		CClientDC dc(this);
		CFont* def_font = dc.SelectObject(pfont);
		dc.TextOutW(50, 50, _T("用公用字体对话框选择字体"));
		dc.SelectObject(def_font);
		
		// Done with the font. Delete the font object.
		::DeleteObject(hfont);
	}
}


void CTest_vs10View::OnCombodemo()
{
	// TODO: Add your command handler code here

	
	CComboDlg dlg;

	if(dlg.DoModal() ==IDOK)
	{
		;
	}
}


void CTest_vs10View::OnEditRadius()
{
	// TODO: Add your command handler code here
	CExample dlg;

	if(dlg.DoModal() ==IDOK)
	{
		m_nRadius = dlg.m_nRadius;
		Invalidate();
	}
}


void CTest_vs10View::OnColordlg()
{
	// TODO: Add your command handler code here

	CClorDlg dlg;


	if(dlg.DoModal() ==IDOK)
	{
		;
	}
}


void CTest_vs10View::OnListdemo()
{
	// TODO: Add your command handler code here
	CExampListDlg dlg;

	if(dlg.DoModal() ==IDOK)
	{
		;
	}
}


void CTest_vs10View::OnViewRadius()
{
	// TODO: Add your command handler code here
		CExampListDlg dlg;

	if(dlg.DoModal() ==IDOK)
	{
		;
	}
}


LRESULT CTest_vs10View::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	Invalidate();

	return 0;

}