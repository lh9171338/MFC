#pragma once


// CComboDlg 对话框

class CComboDlg : public CDialog
{
	DECLARE_DYNAMIC(CComboDlg)

public:
	CComboDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CComboDlg();

// 对话框数据
	enum { IDD = IDD_DIALOGCOMBO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CWnd *pwnd;
	CComboBox m_combobox;
	CString m_name;
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeCombo();
	afx_msg void OnClickedButtonapply();
};
