#pragma once
#include"Chessman.h"
// CMovement 命令目标

class CMovement : public CObject
{
public:
	int m_chessmannumber;		//移动对象序号
	char m_d;					//移动方向
	int m_stepnumber;
public:
	CMovement();
	CMovement(int chessmannumber,char d,int stepnumber);
	virtual ~CMovement();
};


