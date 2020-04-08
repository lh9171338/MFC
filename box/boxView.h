
// boxView.h : CboxView ��Ľӿ�
//
#include"Cway.h"
#include<afxtempl.h>						//ʹ��MFC��ģ����Ҫ������ͷ�ļ�


#define IDB_L 130
#define IDB_R 131
#define IDB_U 132
#define IDB_D 133
#define IDB_BACK 134
#define IDB_RSTART 135
#define IDB_NEXT 136
#pragma once

class Cmap{
public:
	CPoint p;
	bool wall,box,place;
};
class CboxView : public CView
{
private:
	CButton b1,b2,b3,b4,b5,b6,b7;
	Cmap map[20][20];
	int I,J,L,W,BOXNUM,stepnum,test,atplacenum; 
	bool success,m_move,boxmove;
	char d;
protected: // �������л�����
	CboxView();
	DECLARE_DYNCREATE(CboxView)
	CTypedPtrArray<CObArray,Cway*>m_wayarray;			
// ����
public:
	CboxDoc* GetDocument() const;

// ����
public:
	void set(int test);
	void init1();
	void init2();
	void move();		
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
	virtual ~CboxView();
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
	afx_msg void ONLDOWN();
	afx_msg void ONRDOWN();
	afx_msg void ONUDOWN();
	afx_msg void ONDDOWN();
	afx_msg void ONBACKDOWN();
	afx_msg void ONRSTARTDOWN();
	afx_msg void ONNEXTDOWN();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // boxView.cpp �еĵ��԰汾
inline CboxDoc* CboxView::GetDocument() const
   { return reinterpret_cast<CboxDoc*>(m_pDocument); }
#endif

