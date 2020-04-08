
// ExmpListDlg.h : 头文件
//

#pragma once

struct sstate
{
	CString name,capital,populat,area;
};
// CExmpListDlg 对话框
class CExmpListDlg : public CDialogEx
{
private:
	sstate state;
// 构造
public:
	CExmpListDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXMPLIST_DIALOG };

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
	CListBox m_ListBx;
	CString m_name;
	CString m_capital;
	CString m_populat;
	CString m_area;


	void Serialize(CArchive &ar);
	void read();
	void save();


	afx_msg void OnClickedButtonadd();
	afx_msg void OnClickedButtondel();
	afx_msg void OnSelchangeListstate();
	afx_msg void OnDestroy();
};
