
// moveView.h : CmoveView ��Ľӿ�
//
#define IDB_L 130
#define IDB_R 131
#define IDB_U 132
#define IDB_D 133
#define IDB_START 134
#define IDB_STOP 135
#pragma once

#include"Cpoint.h"
#include<afxtempl.h>								//ʹ��MFC��ģ����Ҫ������ͷ�ļ�
#include<time.h>
#include<stdlib.h>

class CmoveView : public CView
{
private:
	CButton b1,b2,b3,b4,b5,b6;
	char d;
	bool sign,life,bagin,faster,lastfaster;
	int hard,score;
	CPoint m_food,m_tail,m_head;
protected: // �������л�����
	CmoveView();
	DECLARE_DYNCREATE(CmoveView)

// ����
public:
	CmoveDoc* GetDocument() const;

// ����
public:
	CTypedPtrArray<CObArray,Cpoint*>pointarray;			//��ŵ����Ķ�̬����
	Cpoint* getpoint(int n);							//��ȡָ����ŵ�����ָ��
	void addpoint(CPoint p);							//��̬������Ӷ���
	int getnumpoint();									//��ȡ������
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
	virtual ~CmoveView();
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
	afx_msg void ONSTARTDOWN();
	afx_msg void ONSTOPDOWN();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHard();
	afx_msg void OnUpdateHard(CCmdUI *pCmdUI);
	afx_msg void OnEasy();
	afx_msg void OnUpdateEasy(CCmdUI *pCmdUI);
	afx_msg void OnNormal();
	afx_msg void OnUpdateNormal(CCmdUI *pCmdUI);
	afx_msg void OnVeryhard();
	afx_msg void OnUpdateVeryhard(CCmdUI *pCmdUI);
	afx_msg void food();
	afx_msg void eat();
	afx_msg void run();
	afx_msg void draw();
};

#ifndef _DEBUG  // moveView.cpp �еĵ��԰汾
inline CmoveDoc* CmoveView::GetDocument() const
   { return reinterpret_cast<CmoveDoc*>(m_pDocument); }
#endif

