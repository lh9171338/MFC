#pragma once


// CExampListDlg dialog

class CExampListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExampListDlg)


private:
	struct SState
	{
		CString strName;
		CString strCap;
		DWORD nPopu;
		DWORD nArea;
	};

public:
	CExampListDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExampListDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	DWORD m_nArea;
	DWORD m_nPopulat;

	CString	m_strCapitao;
	CString	m_strName;

	CListCtrl	m_listCountry;
	CListBox	m_ListBx;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedListCtrlcountry(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnSelchangeListstate();
};
