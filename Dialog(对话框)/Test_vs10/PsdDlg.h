#pragma once


// CPsdDlg dialog

class CPsdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPsdDlg)

public:
	CPsdDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPsdDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ctrlCheck;
	CString m_strPsdShow;
	CString m_strPsd;
	CString m_strUsername;
	afx_msg void OnEnChangeEditPsdword();
};
