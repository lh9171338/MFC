
// colorbuttonDlg.h : 头文件
//

#pragma once


// CcolorbuttonDlg 对话框
class CcolorbuttonDlg : public CDialogEx
{
// 构造
public:
	CcolorbuttonDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COLORBUTTON_DIALOG };

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
	int m_color;
	BOOL m_RED;
	BOOL m_GREEN;
	BOOL m_BLUE;
//	afx_msg void OnClickedRadiocolor();
	afx_msg void OnClickedRadiocolor();
	afx_msg void OnRadioblack();
	afx_msg void OnClickedButtonapply();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
