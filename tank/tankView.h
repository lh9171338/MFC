
// tankView.h : CtankView 类的接口
//

#pragma once
#include"T.h"
#include"Cmap.h"

class CtankView : public CView
{
private:
	CT P1,A[4];
	Cmap map[26][26];
	bool m_move,m_start,m_first;
	int m_score,m_life,m_time1,m_time2,m_type;
protected: // 仅从序列化创建
	CtankView();
	DECLARE_DYNCREATE(CtankView)

// 特性
public:
	CtankDoc* GetDocument() const;

// 操作
public:
	void init(int i,int j,int type,CT &t);
	int bornplace();
	void produced(CT &t);
	void Pmove(CT &t,int m_time);
	void Pfire(CT &t);
	void zmove(CT &t);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CtankView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // tankView.cpp 中的调试版本
inline CtankDoc* CtankView::GetDocument() const
   { return reinterpret_cast<CtankDoc*>(m_pDocument); }
#endif

