
// ExmpListDlg.h : ͷ�ļ�
//

#pragma once

struct sstate
{
	CString name,capital,populat,area;
};
// CExmpListDlg �Ի���
class CExmpListDlg : public CDialogEx
{
private:
	sstate state;
// ����
public:
	CExmpListDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXMPLIST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
