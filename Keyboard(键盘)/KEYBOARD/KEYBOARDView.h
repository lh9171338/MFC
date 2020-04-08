
// KEYBOARDView.h : CKEYBOARDView 类的接口
//

#pragma once


class CKEYBOARDView : public CView
{
private:
	int m_num;
	bool shiftup,shiftdown,shiftb,left;
protected: // 仅从序列化创建
	CKEYBOARDView();
	DECLARE_DYNCREATE(CKEYBOARDView)

// 特性
public:
	CKEYBOARDDoc* GetDocument() const;

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
	virtual ~CKEYBOARDView();
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
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // KEYBOARDView.cpp 中的调试版本
inline CKEYBOARDDoc* CKEYBOARDView::GetDocument() const
   { return reinterpret_cast<CKEYBOARDDoc*>(m_pDocument); }
#endif

