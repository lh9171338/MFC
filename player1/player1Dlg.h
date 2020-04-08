
// player1Dlg.h : ͷ�ļ�
//

#pragma once

#include"CWMPPlayer4.h"
#include"CWMPSettings.h"
#include"CWMPMedia.h"
#include"CWMPControls.h"


// Cplayer1Dlg �Ի���
class Cplayer1Dlg : public CDialogEx
{
private:
	CString filename,name;
// ����
public:
	Cplayer1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PLAYER1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CWMPPlayer4 m_player;    //���ŵ�ַ����
	CWMPControls m_control;  //���ư�ť����
	CWMPSettings m_setting;   //���ð�ť����
	CWMPMedia m_media;			//ý��
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
