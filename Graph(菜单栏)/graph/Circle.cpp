// Circle.cpp : 实现文件
//

#include "stdafx.h"
#include "graph.h"
#include "Circle.h"


// CCircle

CCircle::CCircle()
{
}
CCircle::CCircle(CPoint p1,CPoint p2,COLORREF color)
{
	m_p1=p1;
	m_p2=p2;
	m_color=color;
}
void CCircle::drawcircle(CDC *pDC,double rate)
{
	CPen pen(PS_SOLID,1,m_color);
	pDC->SelectObject(&pen);
	pDC->SelectStockObject(NULL_BRUSH);
	CPoint p;
	int r;
	r=(m_p2.x-m_p1.x)/2;
	p.x=(m_p2.x+m_p1.x)/2;
	p.y=(m_p2.y+m_p1.y)/2;
	m_p1.x=p.x-r*rate;
	m_p1.y=p.y-r*rate;
	m_p2.x=p.x+r*rate;
	m_p2.y=p.y+r*rate;
	pDC->Ellipse(m_p1.x,m_p1.y,m_p2.x,m_p2.y);
}
CCircle::~CCircle()
{
}


// CCircle 成员函数
