
// HuaRongDaoView.h : CHuaRongDaoView 类的接口
//

#pragma once

#include"Chessman.h"
#include"Chessboard.h"
#include"Movement.h"

#define IDB_RESTART 130
#define IDB_SAVE 131
#define IDB_LOAD 132
#define IDB_NEXT 133
#define IDB_HELP 134
#define IDB_LEVEL 135
#define IDB_VIDEO 136
#define IDC_LISTLEVEL 137
#define IDC_LISTVIDEO 138
#define IDC_EDIT 139

struct Person{
	int m_chessmannumber;
	CString m_name;
};

class CHuaRongDaoView : public CView
{
private:
	CButton b1,b2,b3,b4,b5,b6,b7;				//按键
	CStatic m_static;							//文本框

	CChessman m_chessman[10];
	CChessboard m_chessboard[4][5];		//4*5
	int m_chessmannumber;
	char m_d;							//方向
	int m_stepnumber;					//步数
	int m_level;						//关卡
	CString m_levelname;				//关卡名称
	int m_time;							//时间
	bool playflag;						//播放状态标记
	bool timeflag;
	bool successflag;					//过关状态标记
	bool makeflag;						//自制状态标记
	bool dragflag;						//拖动状态标记
	CString solutionfilename;
	CString levelfilename;
	int m_levelnumber;
	int m_solutionnumber;
	int *psolution;
	int m_wDeviceID;

	CString m_date1;					//存档时间
	CString m_date2;					//存档时间
	CStatic *pwndstatic;				//静态文本框
	CEdit *pwndedit;					//编辑框
	CListBox *pwndlevel_list;				//关卡列表框
	CListBox *pwndvideo_list;				//解法视频文本框
protected: // 仅从序列化创建
	CHuaRongDaoView();
	DECLARE_DYNCREATE(CHuaRongDaoView)

// 特性
public:
	CHuaRongDaoDoc* GetDocument() const;

// 操作
public:
	void initselect(int level);
	void draw(CDC *pDC);
	void reflesh();
	void move(char d);
	int getchessmannumber(int x,int y);			//获得棋子序号
	char getderection(int x,int y);				//获得方向
	void setchess(int x,int y);					//摆放棋子
	void succeed();								//判断是否过关
	void save();
	void load();
	void save_solution(int level);
	void load_solution(int level);
	void save_level_solution();	
	void load_level_solution();		
	void save_level(int level);	
	void load_level(int level);		
	void Iscanload();
	int Iscannext();
	void Ismakefinish();
	int clearmovement();
	void Timer(int n);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CHuaRongDaoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void ONRESTART();
	afx_msg void ONSAVE();
	afx_msg void ONLOAD();
	afx_msg void ONNEXT();
	afx_msg void ONHELP();
	afx_msg void ONLEVEL();
	afx_msg void ONVIDEO();
	afx_msg void OnSelchangeListlevel();
	afx_msg void OnSelchangeListvideo();
	afx_msg void OnDblclkListlevel();
	afx_msg void OnDblclkListvideo();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void Serialize(CArchive& ar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // HuaRongDaoView.cpp 中的调试版本
inline CHuaRongDaoDoc* CHuaRongDaoView::GetDocument() const
   { return reinterpret_cast<CHuaRongDaoDoc*>(m_pDocument); }
#endif

