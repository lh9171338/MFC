// Movement.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HuaRongDao.h"
#include "Movement.h"


// CMovement
int m_stepnumber=0;
CMovement::CMovement()
{
}
CMovement::CMovement(int chessmannumber,char d,int stepnumber)
{
	m_chessmannumber=chessmannumber;
	m_d=d;
	m_stepnumber=stepnumber;
}
CMovement::~CMovement()
{
}


// CMovement ��Ա����
