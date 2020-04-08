#pragma once

// CChessman 命令目标

enum chessman_name{
	Caocao=0,
	Zhangfei,
	Zhangfei1,
	Zhaoyun,
	Zhaoyun1,
	Machao,
	Machao1,
	Huangzhong,
	Huangzhong1,
	Guanyu,
	Guanyu1,
	Zu
};
class CChessman : public CObject
{
public:
	int m_x,m_y,m_width,m_height;		//坐标
	int m_name;
	bool m_clickflag;						//选中标记	
	bool m_finishset;
public:
	CChessman();
	void set(int width,int height,int name,int x=0,int y=0,bool clickflag=false,bool m_finishset=true);
	void move(char d);
	void draw(CDC *pDC,bool drag=false);
	virtual ~CChessman();
};
