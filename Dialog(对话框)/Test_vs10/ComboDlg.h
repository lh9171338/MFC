#pragma once


// CComboDlg dialog

class CComboDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CComboDlg)

private:
	CWnd* m_pwnd;

public:
	CComboDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CComboDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_COMBO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCtrlName;
	CString m_straddcombo;
	CComboBox	m_ComboBx;
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelchangeComboCtrname();
	afx_msg void OnBnClickedApply();
};
