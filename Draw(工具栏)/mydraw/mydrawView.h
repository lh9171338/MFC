
// mydrawView.h : CmydrawView 类的接口
//

#pragma once


class CmydrawView : public CView
{
protected: // 仅从序列化创建
	COLORREF m_color;
	CPoint m_pstart;
	bool m_bdrag;
	HCURSOR m_hcross;
	CmydrawView();
	DECLARE_DYNCREATE(CmydrawView)

// 特性
public:
	CmydrawDoc* GetDocument() const;

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
	virtual ~CmydrawView();
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRed();
	afx_msg void OnGreen();
	afx_msg void OnBlue();
};

#ifndef _DEBUG  // mydrawView.cpp 中的调试版本
inline CmydrawDoc* CmydrawView::GetDocument() const
   { return reinterpret_cast<CmydrawDoc*>(m_pDocument); }
#endif

