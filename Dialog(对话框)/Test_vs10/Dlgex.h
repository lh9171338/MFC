#pragma once


// CDlgex dialog

class CDlgex : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgex)

public:
	CDlgex(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgex();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	int m_nRadius;
};
