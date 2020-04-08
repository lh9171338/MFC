#pragma once

// CCircle ÃüÁîÄ¿±ê

class CCircle : public CObject
{
private:
	CPoint m_p1,m_p2;
	COLORREF m_color;
public:
	CCircle();
	CCircle(CPoint p1,CPoint p2,COLORREF color);
	void drawcircle(CDC *pDC,double rate);
	virtual ~CCircle();
};


