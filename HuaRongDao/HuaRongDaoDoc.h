
// HuaRongDaoDoc.h : CHuaRongDaoDoc ��Ľӿ�
//

#include"Movement.h"
#include<afxtempl.h>						//ʹ��MFC��ģ����Ҫ������ͷ�ļ�
#pragma once


class CHuaRongDaoDoc : public CDocument
{
protected: // �������л�����
	CHuaRongDaoDoc();
	DECLARE_DYNCREATE(CHuaRongDaoDoc)

	CTypedPtrArray<CObArray,CMovement*>m_movementarray;			//����ƶ������Ķ�̬����
// ����
public:
	void addmovement(int chessmannumber,char d,int stepnumber);				//��̬������Ӷ���
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
	virtual ~CHuaRongDaoDoc();
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
