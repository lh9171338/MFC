// Line.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mydraw.h"
#include "Line.h"


// CLine
IMPLEMENT_SERIAL(CLine,CObject,1)
CLine::CLine()
{
}

CLine::~CLine()
{
}


// CLine ��Ա����
CLine::CLine(CPoint p1,CPoint p2,COLORREF color)
{
	m_p1=p1;
	m_p2=p2;
	m_color=color;
}
void CLine::drawline(CDC *pDC)
{
	CPen pen(PS_SOLID,10,m_color);
	pDC->SelectObject(&pen);
	pDC->MoveTo(m_p1);
	pDC->LineTo(m_p2);
	CFont font;
	font.CreatePointFont(240,_T("����"));
	pDC->SelectObject(&font);
	pDC->TextOut(500,400,_T("���"));
	CFont font2;
	font2.CreatePointFont(120,_T("����"));
	CFont* pOldFont = pDC->SelectObject(&font2);
	pDC->TextOut(600,400,_T("���"));
	pDC->SelectObject(pOldFont);
	pDC->TextOut(700,400,_T("���"));
}
void CLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		ar<<m_p1<<m_p2<<m_color;						//����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		ar>>m_p1>>m_p2>>m_color;						//����
	}
}
