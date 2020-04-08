
// HuaRongDaoView.h : CHuaRongDaoView ��Ľӿ�
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
	CButton b1,b2,b3,b4,b5,b6,b7;				//����
	CStatic m_static;							//�ı���

	CChessman m_chessman[10];
	CChessboard m_chessboard[4][5];		//4*5
	int m_chessmannumber;
	char m_d;							//����
	int m_stepnumber;					//����
	int m_level;						//�ؿ�
	CString m_levelname;				//�ؿ�����
	int m_time;							//ʱ��
	bool playflag;						//����״̬���
	bool timeflag;
	bool successflag;					//����״̬���
	bool makeflag;						//����״̬���
	bool dragflag;						//�϶�״̬���
	CString solutionfilename;
	CString levelfilename;
	int m_levelnumber;
	int m_solutionnumber;
	int *psolution;
	int m_wDeviceID;

	CString m_date1;					//�浵ʱ��
	CString m_date2;					//�浵ʱ��
	CStatic *pwndstatic;				//��̬�ı���
	CEdit *pwndedit;					//�༭��
	CListBox *pwndlevel_list;				//�ؿ��б��
	CListBox *pwndvideo_list;				//�ⷨ��Ƶ�ı���
protected: // �������л�����
	CHuaRongDaoView();
	DECLARE_DYNCREATE(CHuaRongDaoView)

// ����
public:
	CHuaRongDaoDoc* GetDocument() const;

// ����
public:
	void initselect(int level);
	void draw(CDC *pDC);
	void reflesh();
	void move(char d);
	int getchessmannumber(int x,int y);			//����������
	char getderection(int x,int y);				//��÷���
	void setchess(int x,int y);					//�ڷ�����
	void succeed();								//�ж��Ƿ����
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
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CHuaRongDaoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // HuaRongDaoView.cpp �еĵ��԰汾
inline CHuaRongDaoDoc* CHuaRongDaoView::GetDocument() const
   { return reinterpret_cast<CHuaRongDaoDoc*>(m_pDocument); }
#endif

