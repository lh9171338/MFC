
// colortextView.h : CcolortextView 类的接口
//

#pragma once


class CcolortextView : public CView
{
private:
	COLORREF m_color;
protected: // 仅从序列化创建
	CcolortextView();
	DECLARE_DYNCREATE(CcolortextView)

// 特性
public:
	CcolortextDoc* GetDocument() const;
	void showcolor();
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
	virtual ~CcolortextView();
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
	afx_msg void OnRed();
	afx_msg void OnUpdateRed(CCmdUI *pCmdUI);
	afx_msg void OnBlue();
	afx_msg void OnUpdateBlue(CCmdUI *pCmdUI);
	afx_msg void OnGreen();
	afx_msg void OnUpdateGreen(CCmdUI *pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPurple();
	afx_msg void OnUpdatePurple(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // colortextView.cpp 中的调试版本
inline CcolortextDoc* CcolortextView::GetDocument() const
   { return reinterpret_cast<CcolortextDoc*>(m_pDocument); }
#endif

