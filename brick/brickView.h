
// brickView.h : CbrickView ��Ľӿ�
//
#include<time.h>
#include<stdlib.h>
#pragma once
#define L 12
#define H 20

#define IDB_L 130
#define IDB_R 131
#define IDB_TURN 132
#define IDB_D 133
#define IDB_START 134
#define IDB_STOP 135
class map{
public:
	CPoint m_p;
	COLORREF m_color;
	bool brick,moveb;
};
class brick{
public:
	int I1,I2,I3,I4,J1,J2,J3,J4,m_type;
	COLORREF m_color;
	bool hang;
};

class CbrickView : public CView
{
private:
	CButton b1,b2,b3,b4,b5,b6;
	map M[L][H];
	brick B;
	bool bagin,life,m_move,first;
	int m_hard,m_score,m_type,m_num[H];
	char d;
protected: // �������л�����
	CbrickView();
	DECLARE_DYNCREATE(CbrickView)

// ����
public:
	CbrickDoc* GetDocument() const;

// ����
public:
	void init();
	void move();
	void draw(CDC *pDC);
	void pro();
	int turnl();
	int turnr();
	void full();
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
	virtual ~CbrickView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void ONLDOWN();
	afx_msg void ONRDOWN();
	afx_msg void ONTURNDOWN();
	afx_msg void ONDDOWN();
	afx_msg void ONSTARTDOWN();
	afx_msg void ONSTOPDOWN();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // brickView.cpp �еĵ��԰汾
inline CbrickDoc* CbrickView::GetDocument() const
   { return reinterpret_cast<CbrickDoc*>(m_pDocument); }
#endif

