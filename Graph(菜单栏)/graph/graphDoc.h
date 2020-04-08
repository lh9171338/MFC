
// graphDoc.h : CgraphDoc 类的接口
//
#include"Circle.h"
#include"Rectange.h"
#include<afxtempl.h>						//使用MFC类模板需要包含该头文件




#pragma once


class CgraphDoc : public CDocument
{
protected: // 仅从序列化创建
	CgraphDoc();
	DECLARE_DYNCREATE(CgraphDoc)

// 特性
public:
// 操作
public:
	CTypedPtrArray<CObArray,CCircle*>m_circlearray;			//存放线段对象的动态数组
	CCircle* getcircle(int n);								//获取指定序号圆对象的指针
	void addcircle(CPoint p1,CPoint p2,COLORREF color);					//向动态数组添加对象
	int getnumcircle();										//获取圆数量

	CTypedPtrArray<CObArray,CRectange*>m_rectangearray;			//存放线段对象的动态数组
	CRectange* getrectange(int n);								//获取指定序号圆对象的指针
	void addrectange(CPoint p1,CPoint p2,COLORREF color);					//向动态数组添加对象
	int getnumrectange();										//获取圆数量

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
	virtual ~CgraphDoc();
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
