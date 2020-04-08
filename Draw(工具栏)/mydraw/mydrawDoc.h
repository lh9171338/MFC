
// mydrawDoc.h : CmydrawDoc ��Ľӿ�
//

#include"Line.h"
#include<afxtempl.h>						//ʹ��MFC��ģ����Ҫ������ͷ�ļ�
#pragma once


class CmydrawDoc : public CDocument
{
protected: // �������л�����
	CmydrawDoc();
	DECLARE_DYNCREATE(CmydrawDoc)

	CTypedPtrArray<CObArray,CLine*>m_linearray;			//����߶ζ���Ķ�̬����
// ����
public:
	CLine* getline(int n);								//��ȡָ������߶ζ����ָ��
	void addline(CPoint p1,CPoint p2,COLORREF color);					//��̬������Ӷ���
	int getnumline();									//��ȡ�߶�����

// ����
public:

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
	virtual ~CmydrawDoc();
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
public:
	virtual void DeleteContents();
};
