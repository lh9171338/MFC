#pragma once


// CComboDlg �Ի���

class CComboDlg : public CDialog
{
	DECLARE_DYNAMIC(CComboDlg)

public:
	CComboDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CComboDlg();

// �Ի�������
	enum { IDD = IDD_DIALOGCOMBO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
