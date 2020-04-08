
// KEYBOARDView.h : CKEYBOARDView ��Ľӿ�
//

#pragma once


class CKEYBOARDView : public CView
{
private:
	int m_num;
	bool shiftup,shiftdown,shiftb,left;
protected: // �������л�����
	CKEYBOARDView();
	DECLARE_DYNCREATE(CKEYBOARDView)

// ����
public:
	CKEYBOARDDoc* GetDocument() const;

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
	virtual ~CKEYBOARDView();
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
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // KEYBOARDView.cpp �еĵ��԰汾
inline CKEYBOARDDoc* CKEYBOARDView::GetDocument() const
   { return reinterpret_cast<CKEYBOARDDoc*>(m_pDocument); }
#endif

