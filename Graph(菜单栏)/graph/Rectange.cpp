// Rectange.cpp : 实现文件
//

#include "stdafx.h"
#include "graph.h"
#include "Rectange.h"


// CRectange

CRectange::CRectange()
{
}
CRectange::CRectange(CPoint p1,CPoint p2,COLORREF color)
{
	m_p1=p1;
	m_p2=p2;
	m_color=color;
}
void CRectange::drawrectange(CDC *pDC,double rate)
{
	CPen pen(PS_SOLID,1,m_color);
	pDC->SelectObject(&pen);
	pDC->SelectStockObject(NULL_BRUSH);
	m_p2.x=(m_p2.x-m_p1.x)*rate+m_p1.x;
	m_p2.y=(m_p2.y-m_p1.y)*rate+m_p1.y;
	pDC->Rectangle(m_p1.x,m_p1.y,m_p2.x,m_p2.y);
}
CRectange::~CRectange()
{
}


// CRectange 成员函数
