#pragma once

// CRectange ÃüÁîÄ¿±ê

class CRectange : public CObject
{
private:
	CPoint m_p1,m_p2;
	COLORREF m_color;
public:
	CRectange();
	CRectange(CPoint p1,CPoint p2,COLORREF color);
	void drawrectange(CDC *pDC,double rate);
	virtual ~CRectange();
};


