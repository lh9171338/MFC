#pragma once

// Cmap ÃüÁîÄ¿±ê

class Cmap : public CObject
{
public:
	CPoint m_p;
	bool m_wall,m_tank,m_zidan;
	int m_typewall,m_typetank,m_zidantype;
	Cmap();
	void init1map(Cmap p[][26]);
	void drawmap(CDC* pDC);
	virtual ~Cmap();
};


