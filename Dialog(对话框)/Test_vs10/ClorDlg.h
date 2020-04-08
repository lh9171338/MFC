#pragma once
#define WM_MYMESSAGE  WM_USER+1

// CClorDlg dialog

class CClorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CClorDlg)

public:
	CClorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CClorDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_iColor;
	BOOL m_bBlue;
	BOOL m_bRed;
	BOOL m_bGreen;
	COLORREF m_clrButn;
	BOOL m_bCorlorDlgUsed;

	afx_msg void OnBnClickedRadioclr();
	afx_msg void OnRadioblk();
	afx_msg void OnBnClickedButtondraw();
	afx_msg void OnBnClickedButtonbitmap();
	afx_msg void OnBnClickedButtonapply();
	afx_msg void OnBnClickedButtoncol();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckred();
	afx_msg void OnBnClickedCheckgre();
	afx_msg void OnBnClickedCheckblu();
};
