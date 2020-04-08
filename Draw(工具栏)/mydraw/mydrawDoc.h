
// mydrawDoc.h : CmydrawDoc 类的接口
//

#include"Line.h"
#include<afxtempl.h>						//使用MFC类模板需要包含该头文件
#pragma once


class CmydrawDoc : public CDocument
{
protected: // 仅从序列化创建
	CmydrawDoc();
	DECLARE_DYNCREATE(CmydrawDoc)

	CTypedPtrArray<CObArray,CLine*>m_linearray;			//存放线段对象的动态数组
// 特性
public:
	CLine* getline(int n);								//获取指定序号线段对象的指针
	void addline(CPoint p1,CPoint p2,COLORREF color);					//向动态数组添加对象
	int getnumline();									//获取线段数量

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
	virtual ~CmydrawDoc();
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
public:
	virtual void DeleteContents();
};
