
// graphDoc.cpp : CgraphDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "graph.h"
#endif

#include "graphDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CgraphDoc

IMPLEMENT_DYNCREATE(CgraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CgraphDoc, CDocument)
END_MESSAGE_MAP()


// CgraphDoc ����/����

CgraphDoc::CgraphDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CgraphDoc::~CgraphDoc()
{
}

BOOL CgraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CgraphDoc ���л�

void CgraphDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CgraphDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CgraphDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CgraphDoc::SetSearchContent(const CString& value)
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

// CgraphDoc ���

#ifdef _DEBUG
void CgraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CgraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CgraphDoc ����


CCircle* CgraphDoc::getcircle(int n)								//��ȡָ������߶ζ����ָ��
{
	if(n<0||n>m_circlearray.GetUpperBound())
		return NULL;
	return m_circlearray.GetAt(n);
}
void CgraphDoc::addcircle(CPoint p1,CPoint p2,COLORREF color)					//��̬������Ӷ���
{
	CCircle *pcircle=new CCircle(p1,p2,color);
	m_circlearray.Add(pcircle);
}
int CgraphDoc::getnumcircle()									//��ȡ�߶�����
{
	return m_circlearray.GetSize();
}

CRectange* CgraphDoc::getrectange(int n)								//��ȡָ������߶ζ����ָ��
{
	if(n<0||n>m_rectangearray.GetUpperBound())
		return NULL;
	return m_rectangearray.GetAt(n);
}
void CgraphDoc::addrectange(CPoint p1,CPoint p2,COLORREF color)					//��̬������Ӷ���
{
	CRectange *prectange=new CRectange(p1,p2,color);
	m_rectangearray.Add(prectange);
}
int CgraphDoc::getnumrectange()									//��ȡ�߶�����
{
	return m_rectangearray.GetSize();
}