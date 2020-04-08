#pragma once

// CT ÃüÁîÄ¿±ê

class CT : public CObject
{
public:
	int I,J,m_move,m_type,ZI,ZJ;
	CPoint m_p,m_pzidan;
	COLORREF m_color;
	char m_oldd,m_d,m_dzidan;
	bool m_zidan,m_alive;
	CT();
	void set(int i,int j,COLORREF color,char oldd,int type=1);
	void draw(CDC* pDC);
	virtual ~CT();
};


 