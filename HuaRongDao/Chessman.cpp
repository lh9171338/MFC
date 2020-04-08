// Chessman.cpp : 实现文件
//

#include "stdafx.h"
#include "HuaRongDao.h"
#include "Chessman.h"


// CChessman

CChessman::CChessman()
{
}
void CChessman::set(int width,int height,int name,int x,int y,bool clickflag,bool finishset)
{
	m_x=x;
	m_y=y;
	m_width=width;
	m_height=height;
	m_name=name;
	m_clickflag=clickflag;
	m_finishset=finishset;
}
void CChessman::move(char d)
{
	switch(d)
	{
	case 'L':				//左
	case 'r':
		m_x--;
		break;
	case 'R':				//右
	case 'l':
		m_x++;
		break;
	case 'U':				//上
	case 'd':
		m_y--;
		break;
	case 'D':				//下
	case 'u':
		m_y++;
		break;
	default:break;
	}
}
void CChessman::draw(CDC *pDC,bool drag)
{
	if(m_finishset||drag)
	{
		CDC MemDC;
		CBitmap MemBitmap;
		MemDC.CreateCompatibleDC(NULL); 
		switch(m_name)
		{
		case Caocao:
			MemBitmap.LoadBitmap(IDB_BITMAP3);
			break;
		case Huangzhong:
			MemBitmap.LoadBitmap(IDB_BITMAP4);
			break;
		case Zhaoyun:
			MemBitmap.LoadBitmap(IDB_BITMAP5);
			break;
		case Zhangfei:
			MemBitmap.LoadBitmap(IDB_BITMAP6);
			break;
		case Machao:
			MemBitmap.LoadBitmap(IDB_BITMAP7);
			break;
		case Guanyu:
			MemBitmap.LoadBitmap(IDB_BITMAP8);
			break;
		case Zu:
			MemBitmap.LoadBitmap(IDB_BITMAP9);
			break;
		case Zhangfei1:
			MemBitmap.LoadBitmap(IDB_BITMAP10);
			break;
		case Machao1:
			MemBitmap.LoadBitmap(IDB_BITMAP11);
			break;
		case Huangzhong1:
			MemBitmap.LoadBitmap(IDB_BITMAP12);
			break;
		case Zhaoyun1:
			MemBitmap.LoadBitmap(IDB_BITMAP13);
			break;
		case Guanyu1:
			MemBitmap.LoadBitmap(IDB_BITMAP14);
			break;
		default:break;
		}
		MemDC.SelectObject(&MemBitmap); 
		pDC->BitBlt(m_x*100+200,m_y*100+50,m_width,m_height,&MemDC,0,0,SRCCOPY); 
		MemBitmap.DeleteObject(); 
		MemDC.DeleteDC(); 

	

		CPen pen1(PS_SOLID,1,RGB(0,0,0));
		CPen pen2(PS_SOLID,3,RGB(255,0,0));
		pDC->SelectStockObject(NULL_BRUSH);
		if(m_clickflag)								//被选中
			pDC->SelectObject(&pen2);
		else
			pDC->SelectObject(&pen1);
		pDC->Rectangle(m_x*100+200,m_y*100+50,m_x*100+200+m_width,m_y*100+50+m_height);
	}
}
CChessman::~CChessman()
{
}


// CChessman 成员函数
