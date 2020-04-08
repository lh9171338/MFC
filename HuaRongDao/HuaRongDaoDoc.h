
// HuaRongDaoDoc.h : CHuaRongDaoDoc 类的接口
//

#include"Movement.h"
#include<afxtempl.h>						//使用MFC类模板需要包含该头文件
#pragma once


class CHuaRongDaoDoc : public CDocument
{
protected: // 仅从序列化创建
	CHuaRongDaoDoc();
	DECLARE_DYNCREATE(CHuaRongDaoDoc)

	CTypedPtrArray<CObArray,CMovement*>m_movementarray;			//存放移动操作的动态数组
// 特性
public:
	void addmovement(int chessmannumber,char d,int stepnumber);				//向动态数组添加对象
// 操作
public:
	
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CHuaRongDaoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
