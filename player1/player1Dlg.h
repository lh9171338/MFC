
// player1Dlg.h : 头文件
//

#pragma once

#include"CWMPPlayer4.h"
#include"CWMPSettings.h"
#include"CWMPMedia.h"
#include"CWMPControls.h"


// Cplayer1Dlg 对话框
class Cplayer1Dlg : public CDialogEx
{
private:
	CString filename,name;
// 构造
public:
	Cplayer1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PLAYER1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonopen();
	afx_msg void OnClickedButtonminus();
	afx_msg void OnClickedButtongo();
	afx_msg void OnClickedButtonfull();
	afx_msg void OnClickedButtonback();
	afx_msg void OnClickedButtonadd();
	afx_msg void OnClickedButtonpause();
	afx_msg void OnClickedButtonplay();
	afx_msg void OnClickedButtonstop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	CWMPPlayer4 m_player;    //播放地址关联
	CWMPControls m_control;  //控制按钮关联
	CWMPSettings m_setting;   //设置按钮关联
	CWMPMedia m_media;			//媒体
	CProgressCtrl m_progress;
	CListBox m_listsong;
	DECLARE_EVENTSINK_MAP()
	void PlayStateChangeOcx1(long NewState);
	
	afx_msg void OnDblclkListsong();
	afx_msg void OnClickedButtonaddsong();
	afx_msg void OnClickedButtondeletesong();
	void Serialize(CArchive &ar);
	void read();
	void save();
	afx_msg void OnDestroy();
};
