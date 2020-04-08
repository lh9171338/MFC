
// tankView.h : CtankView ��Ľӿ�
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
protected: // �������л�����
	CtankView();
	DECLARE_DYNCREATE(CtankView)

// ����
public:
	CtankDoc* GetDocument() const;

// ����
public:
	void init(int i,int j,int type,CT &t);
	int bornplace();
	void produced(CT &t);
	void Pmove(CT &t,int m_time);
	void Pfire(CT &t);
	void zmove(CT &t);
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
	virtual ~CtankView();
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
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // tankView.cpp �еĵ��԰汾
inline CtankDoc* CtankView::GetDocument() const
   { return reinterpret_cast<CtankDoc*>(m_pDocument); }
#endif

