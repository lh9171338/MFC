#pragma once
#include"Chessman.h"
// CMovement ����Ŀ��

class CMovement : public CObject
{
public:
	int m_chessmannumber;		//�ƶ��������
	char m_d;					//�ƶ�����
	int m_stepnumber;
public:
	CMovement();
	CMovement(int chessmannumber,char d,int stepnumber);
	virtual ~CMovement();
};


