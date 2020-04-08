
// mineView.h : CmineView ��Ľӿ�
//
#include<time.h>
#include<stdlib.h>
#pragma once


#define IDB_START 134
#define IDB_RSTART 135

class Cpoint{
public:
	CPoint p;
	int num;
	bool mine,dig,flag;
};


class CmineView : public CView
{
private:
	CButton b1,b2;
	int m_time,m_num,MINE;
	Cpoint p[20][20];
	bool life,bagin;
protected: // �������л�����
	CmineView();
	void set();
	DECLARE_DYNCREATE(CmineView)

// ����
public:
	CmineDoc* GetDocument() const;

// ����
public:
	void init();
	void show(Cpoint q);
	void showall();
	void showsome(Cpoint q,int i,int j);
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
	virtual ~CmineView();
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
	afx_msg void ONSTARTDOWN();
	afx_msg void ONRSTARTDOWN();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnE();
	afx_msg void OnUpdateE(CCmdUI *pCmdUI);
	afx_msg void OnN();
	afx_msg void OnUpdateN(CCmdUI *pCmdUI);
	afx_msg void OnH();
	afx_msg void OnUpdateH(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // mineView.cpp �еĵ��԰汾
inline CmineDoc* CmineView::GetDocument() const
   { return reinterpret_cast<CmineDoc*>(m_pDocument); }
#endif

