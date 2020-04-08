#pragma once

// CLine ÃüÁîÄ¿±ê

class CLine : public CObject
{
private:
	CPoint m_p1,m_p2;
	COLORREF m_color;
public:
	CLine();
	virtual ~CLine();
	CLine(CPoint p1,CPoint p2,COLORREF color);
	void drawline(CDC *pDC);
	void Serialize(CArchive &ar);
	DECLARE_SERIAL(CLine);
};


