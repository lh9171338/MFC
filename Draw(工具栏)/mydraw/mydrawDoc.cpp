
// mydrawDoc.cpp : CmydrawDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CmydrawDoc ����/����

CmydrawDoc::CmydrawDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CmydrawDoc::~CmydrawDoc()
{
}

BOOL CmydrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CmydrawDoc ���л�

void CmydrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		m_linearray.Serialize(ar);
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		m_linearray.Serialize(ar);
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CmydrawDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CmydrawDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CmydrawDoc ���

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


// CmydrawDoc ����


CLine* CmydrawDoc::getline(int n)								//��ȡָ������߶ζ����ָ��
{
	if(n<0||n>m_linearray.GetUpperBound())
		return NULL;
	return m_linearray.GetAt(n);
}
void CmydrawDoc::addline(CPoint p1,CPoint p2,COLORREF color)					//��̬������Ӷ���
{
	CLine *pline=new CLine(p1,p2,color);
	m_linearray.Add(pline);
	SetModifiedFlag();
}
int CmydrawDoc::getnumline()									//��ȡ�߶�����
{
	return m_linearray.GetSize();
}




void CmydrawDoc::DeleteContents()
{
	// TODO: �ڴ����ר�ô����/����û���
	int n=getnumline();
	while(n--)
		delete getline(n);
	m_linearray.RemoveAll();
	CDocument::DeleteContents();
}
