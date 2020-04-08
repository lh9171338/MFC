#pragma once


// CExample dialog

class CExample : public CDialogEx
{
	DECLARE_DYNAMIC(CExample)



public:
	CExample(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExample();

// Dialog Data
	enum { IDD = IDD_DIALOG_EMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_nRadius;
};
