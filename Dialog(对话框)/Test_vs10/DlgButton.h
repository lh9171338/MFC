#pragma once


// CDlgButton dialog

class CDlgButton : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgButton)

public:
	CDlgButton(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgButton();

// Dialog Data
	enum { IDD = IDD_DIALOG_BUTTON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio3();
};
