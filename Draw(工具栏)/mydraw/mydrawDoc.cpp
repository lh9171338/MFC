
// mydrawDoc.cpp : CmydrawDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "mydraw.h"
#endif

#include "mydrawDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CmydrawDoc

IMPLEMENT_DYNCREATE(CmydrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CmydrawDoc, CDocument)
END_MESSAGE_MAP()


// CmydrawDoc 构造/析构

CmydrawDoc::CmydrawDoc()
{
	// TODO: 在此添加一次性构造代码

}

CmydrawDoc::~CmydrawDoc()
{
}

BOOL CmydrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CmydrawDoc 序列化

void CmydrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		m_linearray.Serialize(ar);
	}
	else
	{
		// TODO: 在此添加加载代码
		m_linearray.Serialize(ar);
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CmydrawDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CmydrawDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CmydrawDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CmydrawDoc 诊断

#ifdef _DEBUG
void CmydrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CmydrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CmydrawDoc 命令


CLine* CmydrawDoc::getline(int n)								//获取指定序号线段对象的指针
{
	if(n<0||n>m_linearray.GetUpperBound())
		return NULL;
	return m_linearray.GetAt(n);
}
void CmydrawDoc::addline(CPoint p1,CPoint p2,COLORREF color)					//向动态数组添加对象
{
	CLine *pline=new CLine(p1,p2,color);
	m_linearray.Add(pline);
	SetModifiedFlag();
}
int CmydrawDoc::getnumline()									//获取线段数量
{
	return m_linearray.GetSize();
}




void CmydrawDoc::DeleteContents()
{
	// TODO: 在此添加专用代码和/或调用基类
	int n=getnumline();
	while(n--)
		delete getline(n);
	m_linearray.RemoveAll();
	CDocument::DeleteContents();
}
