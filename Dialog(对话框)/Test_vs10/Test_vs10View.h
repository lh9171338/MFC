
// Test_vs10View.h : interface of the CTest_vs10View class
//

#pragma once
#include "ClorDlg.h"

class CTest_vs10View : public CView
{
protected: // create from serialization only
	CTest_vs10View();
	DECLARE_DYNCREATE(CTest_vs10View)

// Attributes
public:
	bool m_bKill;
	CPen penary[3][7];

	int m_nRadius;
protected:

	CPoint   m_ptOrigin;  // 起始点坐标
	bool   m_bDragging;   // 拖拽标记	
	HCURSOR   m_hCross;   // 光标句柄

// Operations
public:
	CTest_vs10Doc* GetDocument() const;
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTest_vs10View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditDraw();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnViewShowdlg();
	afx_msg void OnCombodemo();
	afx_msg void OnEditRadius();
	afx_msg void OnColordlg();
	afx_msg void OnListdemo();
	afx_msg void OnViewRadius();

	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // debug version in Test_vs10View.cpp
inline CTest_vs10Doc* CTest_vs10View::GetDocument() const
   { return reinterpret_cast<CTest_vs10Doc*>(m_pDocument); }
#endif

