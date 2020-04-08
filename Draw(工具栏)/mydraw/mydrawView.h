
// mydrawView.h : CmydrawView ��Ľӿ�
//

#pragma once


class CmydrawView : public CView
{
protected: // �������л�����
	COLORREF m_color;
	CPoint m_pstart;
	bool m_bdrag;
	HCURSOR m_hcross;
	CmydrawView();
	DECLARE_DYNCREATE(CmydrawView)

// ����
public:
	CmydrawDoc* GetDocument() const;

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
	virtual ~CmydrawView();
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRed();
	afx_msg void OnGreen();
	afx_msg void OnBlue();
};

#ifndef _DEBUG  // mydrawView.cpp �еĵ��԰汾
inline CmydrawDoc* CmydrawView::GetDocument() const
   { return reinterpret_cast<CmydrawDoc*>(m_pDocument); }
#endif

