// T.cpp : 实现文件
//

#include "stdafx.h"
#include "tank.h"
#include "T.h"
// CT

CT::CT()
{
}
void CT::set(int i,int j,COLORREF color,char oldd,int type)
{
	I=i;
	J=j;
	m_move=0;
	m_p.x=i*20+1;
	m_p.y=j*20+1;
	m_color=color;
	m_oldd=m_d=oldd;
	m_alive=true;
	m_zidan=false;
	m_type=type;
}

void CT::draw(CDC* pDC)
{
	CPen pen(PS_SOLID,1,RGB(0,0,0));	
	CBrush brush(m_color);
	pDC->SelectObject(&brush);
	pDC->SelectObject(&pen); 
	switch(m_oldd)
	{
	case 'U':
	pDC->Rectangle(m_p.x-20,m_p.y-20,m_p.x-10,m_p.y+20);
	pDC->Rectangle(m_p.x+10,m_p.y-20,m_p.x+20,m_p.y+20);
	pDC->Rectangle(m_p.x-10,m_p.y-10,m_p.x+10,m_p.y+10);
	pDC->Rectangle(m_p.x-2,m_p.y-20,m_p.x+2,m_p.y);
	pDC->Ellipse(m_p.x-5,m_p.y-5,m_p.x+5,m_p.y+5);
	break;
	case 'D':
	pDC->Rectangle(m_p.x-20,m_p.y-20,m_p.x-10,m_p.y+20);
	pDC->Rectangle(m_p.x+10,m_p.y-20,m_p.x+20,m_p.y+20);
	pDC->Rectangle(m_p.x-10,m_p.y-10,m_p.x+10,m_p.y+10);
	pDC->Rectangle(m_p.x-2,m_p.y,m_p.x+2,m_p.y+20);
	pDC->Ellipse(m_p.x-5,m_p.y-5,m_p.x+5,m_p.y+5);
	break;
	case 'L':
	pDC->Rectangle(m_p.x-20,m_p.y-20,m_p.x+20,m_p.y-10);
	pDC->Rectangle(m_p.x-20,m_p.y+10,m_p.x+20,m_p.y+20);
	pDC->Rectangle(m_p.x-10,m_p.y-10,m_p.x+10,m_p.y+10);
	pDC->Rectangle(m_p.x-20,m_p.y-2,m_p.x,m_p.y+2);
	pDC->Ellipse(m_p.x-5,m_p.y-5,m_p.x+5,m_p.y+5);
	break;
	case 'R':
	pDC->Rectangle(m_p.x-20,m_p.y-20,m_p.x+20,m_p.y-10);
	pDC->Rectangle(m_p.x-20,m_p.y+10,m_p.x+20,m_p.y+20);
	pDC->Rectangle(m_p.x-10,m_p.y-10,m_p.x+10,m_p.y+10);
	pDC->Rectangle(m_p.x,m_p.y-2,m_p.x+20,m_p.y+2);
	pDC->Ellipse(m_p.x-5,m_p.y-5,m_p.x+5,m_p.y+5);
	break;
	default:break;
	}
	if(m_oldd=='U'||m_oldd=='D')
	{
		for(int i=0;i<10;i++)
		{
			pDC->MoveTo(m_p.x-20,m_p.y-20+i*4+m_move*2);
			pDC->LineTo(m_p.x-10,m_p.y-20+i*4+m_move*2);
			pDC->MoveTo(m_p.x+10,m_p.y-20+i*4+m_move*2);
			pDC->LineTo(m_p.x+20,m_p.y-20+i*4+m_move*2);
		}
	}
	else
	{
		for(int i=0;i<10;i++)
		{
			pDC->MoveTo(m_p.x-20+i*4+m_move*2,m_p.y-20);
			pDC->LineTo(m_p.x-20+i*4+m_move*2,m_p.y-10);
			pDC->MoveTo(m_p.x-20+i*4+m_move*2,m_p.y+10);
			pDC->LineTo(m_p.x-20+i*4+m_move*2,m_p.y+20);
		}
	}
	/*CBrush brush1(RGB(255,0,255));
	pDC->SelectObject(&brush1);
	pDC->Ellipse(I*20+1-3,J*20+1-3,I*20+1+3,J*20+1+3);*/
	m_move=1-m_move;
	if(m_zidan)
	{
		m_pzidan.x=ZI*20+1;
		m_pzidan.y=ZJ*20+1;
		CBrush brush1(RGB(255,255,255));
		pDC->SelectObject(&brush1);
		pDC->Ellipse(m_pzidan.x-3,m_pzidan.y-3,m_pzidan.x+3,m_pzidan.y+3);
	}
}
CT::~CT()
{
}


// CT 成员函数
