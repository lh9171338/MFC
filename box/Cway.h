#pragma once

// Cway ����Ŀ��

class Cway : public CObject
{
public:
	char m_d;
	bool m_boxmove;
	Cway();
	Cway(char d,bool boxmove);
	virtual ~Cway();
};


