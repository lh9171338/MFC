
// graphDoc.h : CgraphDoc ��Ľӿ�
//
#include"Circle.h"
#include"Rectange.h"
#include<afxtempl.h>						//ʹ��MFC��ģ����Ҫ������ͷ�ļ�




#pragma once


class CgraphDoc : public CDocument
{
protected: // �������л�����
	CgraphDoc();
	DECLARE_DYNCREATE(CgraphDoc)

// ����
public:
// ����
public:
	CTypedPtrArray<CObArray,CCircle*>m_circlearray;			//����߶ζ���Ķ�̬����
	CCircle* getcircle(int n);								//��ȡָ�����Բ�����ָ��
	void addcircle(CPoint p1,CPoint p2,COLORREF color);					//��̬������Ӷ���
	int getnumcircle();										//��ȡԲ����

	CTypedPtrArray<CObArray,CRectange*>m_rectangearray;			//����߶ζ���Ķ�̬����
	CRectange* getrectange(int n);								//��ȡָ�����Բ�����ָ��
	void addrectange(CPoint p1,CPoint p2,COLORREF color);					//��̬������Ӷ���
	int getnumrectange();										//��ȡԲ����

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CgraphDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
