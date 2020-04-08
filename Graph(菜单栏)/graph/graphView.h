
// graphView.h : CgraphView ��Ľӿ�
//

#pragma once


class CgraphView : public CView
{
protected: // �������л�����
	CgraphView();
	DECLARE_DYNCREATE(CgraphView)

// ����
public:
	CPoint m_p1,m_p2,m_p3;
	bool m_drag,m_time;
	int m_sign;
	COLORREF m_color;
	double m_rate;
	HCURSOR m_hcross;
	CgraphDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CgraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // graphView.cpp �еĵ��԰汾
inline CgraphDoc* CgraphView::GetDocument() const
   { return reinterpret_cast<CgraphDoc*>(m_pDocument); }
#endif

