// Cmap.cpp : 实现文件
//

#include "stdafx.h"
#include "tank.h"
#include "Cmap.h"


// Cmap

Cmap::Cmap()
{
}
void Cmap::init1map(Cmap p[][26])
{
	int i,j;
	for(i=0;i<26;i++)
	{
		for(j=0;j<26;j++)
		{
			p[i][j].m_p.x=i*20+1;
			p[i][j].m_p.y=j*20+1;
			p[i][j].m_wall=p[i][j].m_tank=p[i][j].m_zidan=false;
		}
	}
	for(i=0;i<26;i++)
	{
		if((i>1&&i<11)||(i>16&&i<24))
		{
			p[2][i].m_wall=p[3][i].m_wall=p[6][i].m_wall=p[7][i].m_wall=p[18][i].m_wall=p[19][i].m_wall=p[22][i].m_wall=p[23][i].m_wall=true;
			p[2][i].m_typewall=p[3][i].m_typewall=p[6][i].m_typewall=p[7][i].m_typewall=p[18][i].m_typewall=p[19][i].m_typewall=p[22][i].m_typewall=p[23][i].m_typewall=2;
		}
	}
	for(i=0;i<26;i++)
	{
		if((i>1&&i<9)||(i>10&&i<13)||(i>14&&i<21))
		{
			p[10][i].m_wall=p[11][i].m_wall=p[14][i].m_wall=p[15][i].m_wall=true;
			p[10][i].m_typewall=p[11][i].m_typewall=p[14][i].m_typewall=p[15][i].m_typewall=2;
		}
	}
	for(i=3;i<22;i++)
	{
		if((i>3&&i<8)||(i>17&&i<22))
		{
			p[i][13].m_wall=p[i][14].m_wall=true;
			p[i][13].m_typewall=p[i][14].m_typewall=2;
		}
	}
	for(i=23;i<26;i++)
	{
		p[11][i].m_wall=p[14][i].m_wall=true;
		p[11][i].m_typewall=p[14][i].m_typewall=2;
	}
	p[12][23].m_wall=p[12][16].m_wall=p[12][17].m_wall=p[13][23].m_wall=p[13][16].m_wall=p[13][17].m_wall=true;
	p[12][23].m_typewall=p[12][16].m_typewall=p[12][17].m_typewall=p[13][23].m_typewall=p[13][16].m_typewall=p[13][17].m_typewall=2;
	p[0][14].m_wall=p[1][14].m_wall=p[24][14].m_wall=p[25][14].m_wall=p[12][6].m_wall=p[13][6].m_wall=p[12][7].m_wall=p[13][7].m_wall=true;
	p[0][14].m_typewall=p[1][14].m_typewall=p[24][14].m_typewall=p[25][14].m_typewall=p[12][6].m_typewall=p[13][6].m_typewall=p[12][7].m_typewall=p[13][7].m_typewall=1;
	p[13][25].m_wall=true;
	p[13][25].m_typewall=5;
}
void Cmap::drawmap(CDC* pDC)
{
	if(m_wall)
	{
		switch(m_typewall)
		{
		case 1:											//白铁
			{
			CPen pen1(PS_SOLID,1,RGB(182,182,182));	
			pDC->SelectObject(&pen1); 
			CBrush brush1(RGB(218,218,218));
			pDC->SelectObject(&brush1);
			pDC->Rectangle(m_p.x,m_p.y,m_p.x+20,m_p.y+20);
			CBrush brush2(RGB(255,255,255));
			pDC->SelectObject(&brush2);
			CPen pen2(PS_SOLID,1,RGB(218,218,218));	
			pDC->SelectObject(&pen2); 
			pDC->Rectangle(m_p.x+3,m_p.y+3,m_p.x+17,m_p.y+17);
			}
			break;
		case 2:
			{
				CPen pen1(PS_SOLID,1,RGB(204,102,0));	
				pDC->SelectObject(&pen1); 
				CBrush brush1(RGB(204,102,0));
				pDC->SelectObject(&brush1);
				pDC->Rectangle(m_p.x,m_p.y,m_p.x+20,m_p.y+20);
				CPen pen2(PS_SOLID,1,RGB(255,204,51));	
				pDC->SelectObject(&pen2); 
				pDC->MoveTo(m_p.x+19,m_p.y);
				pDC->LineTo(m_p.x,m_p.y);
				pDC->LineTo(m_p.x,m_p.y+10);
				pDC->LineTo(m_p.x+20,m_p.y+10);
				pDC->MoveTo(m_p.x+10,m_p.y+10);
				pDC->LineTo(m_p.x+10,m_p.y+20);
			}
			break;
		case 3:
			{
				int i,j;
				for(i=0;i<5;i++)
				{
					for(j=0;j<5;j++)
					{
						if(i+j<8)
						{
							if((j==0&&i!=3&&i!=4)||(j==1&&i!=2)||(j==2&&(i==0||i==2))||(j==3&&(i==0||i==1))||(j==4&&i==2))
							{
								CPen pen1(PS_SOLID,1,RGB(51,102,0));	
								pDC->SelectObject(&pen1); 
								CBrush brush1(RGB(51,102,0));
								pDC->SelectObject(&brush1);
								pDC->Rectangle(m_p.x+i*4,m_p.y+j*4,m_p.x+i*4+4,m_p.y+j*4+4);
							}
							else if(j==3&&i==3)
							{
								CPen pen1(PS_SOLID,1,RGB(255,255,0));	
								pDC->SelectObject(&pen1); 
								CBrush brush1(RGB(255,255,0));
								pDC->SelectObject(&brush1);
								pDC->Rectangle(m_p.x+i*4,m_p.y+j*4,m_p.x+i*4+4,m_p.y+j*4+4);
							}
							else
							{
								CPen pen1(PS_SOLID,1,RGB(204,225,0));	
								pDC->SelectObject(&pen1); 
								CBrush brush1(RGB(204,255,0));
								pDC->SelectObject(&brush1);
								pDC->Rectangle(m_p.x+i*4,m_p.y+j*4,m_p.x+i*4+4,m_p.y+j*4+4);
							}
						}
					}
				}
			}
			break;
		case 4:
			{
				CPen pen1(PS_SOLID,1,RGB(0,0,255));	
				pDC->SelectObject(&pen1); 
				CBrush brush1(RGB(0,0,255));
				pDC->SelectObject(&brush1);
				pDC->Rectangle(m_p.x,m_p.y,m_p.x+20,m_p.y+20);
			}
			break;
		case 5:
			{
				CPen pen1(PS_SOLID,1,RGB(255,255,255));	
				pDC->SelectObject(&pen1); 
				CBrush brush1(RGB(255,255,255));
				pDC->SelectObject(&brush1);
				pDC->BeginPath();
				pDC->MoveTo(m_p.x-4,m_p.y-10);
				pDC->LineTo(m_p.x-18,m_p.y-15);
				pDC->LineTo(m_p.x-18,m_p.y-10);
				pDC->LineTo(m_p.x-4,m_p.y);
				pDC->LineTo(m_p.x-15,m_p.y+10);
				pDC->LineTo(m_p.x-4,m_p.y+2);
				pDC->LineTo(m_p.x-7,m_p.y+12);
				pDC->LineTo(m_p.x,m_p.y+18);
				pDC->LineTo(m_p.x+7,m_p.y+12);
				pDC->LineTo(m_p.x+4,m_p.y+2);
				pDC->LineTo(m_p.x+12,m_p.y+10);
				pDC->LineTo(m_p.x+4,m_p.y);
				pDC->LineTo(m_p.x+18,m_p.y-10);
				pDC->LineTo(m_p.x+18,m_p.y-15);
				pDC->LineTo(m_p.x+4,m_p.y-10);
				pDC->LineTo(m_p.x+4,m_p.y-18);
				pDC->LineTo(m_p.x-4,m_p.y-18);
				pDC->LineTo(m_p.x-4,m_p.y-15);
				pDC->LineTo(m_p.x-2,m_p.y-16);
				pDC->LineTo(m_p.x+2,m_p.y-16);
				pDC->LineTo(m_p.x-4,m_p.y-10);
				pDC->EndPath();
				pDC->FillPath();
				CBrush brush2(RGB(0,0,0));
				pDC->SelectObject(&brush2);
				pDC->Ellipse(m_p.x+1,m_p.y-17,m_p.x+3,m_p.y-15);
			}
			break;
		case 6:
			{
			CBrush brush1(RGB(236,236,236));
			pDC->SelectObject(&brush1);
			pDC->Rectangle(m_p.x-20,m_p.y-20,m_p.x+20,m_p.y+20);
			}
			break;
		default:break;
		}
	}
}
Cmap::~Cmap()
{
}


// Cmap 成员函数
