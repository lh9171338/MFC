
// graphView.h : CgraphView 类的接口
//

#pragma once


class CgraphView : public CView
{
protected: // 仅从序列化创建
	CgraphView();
	DECLARE_DYNCREATE(CgraphView)

// 特性
public:
	CPoint m_p1,m_p2,m_p3;
	bool m_drag,m_time;
	int m_sign;
	COLORREF m_color;
	double m_rate;
	HCURSOR m_hcross;
	CgraphDoc* GetDocument() const;

// 操作
public:

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
	virtual ~CgraphView();
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
	afx_msg void OnRect();
	afx_msg void OnCircle();
	afx_msg void OnBigger();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBlue();
	afx_msg void OnGreen();
	afx_msg void OnRed();
	afx_msg void OnSmaller();
};

#ifndef _DEBUG  // graphView.cpp 中的调试版本
inline CgraphDoc* CgraphView::GetDocument() const
   { return reinterpret_cast<CgraphDoc*>(m_pDocument); }
#endif

