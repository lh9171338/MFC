
// colorbuttonDlg.h : ͷ�ļ�
//

#pragma once


// CcolorbuttonDlg �Ի���
class CcolorbuttonDlg : public CDialogEx
{
// ����
public:
	CcolorbuttonDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COLORBUTTON_DIALOG };

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
	int m_color;
	BOOL m_RED;
	BOOL m_GREEN;
	BOOL m_BLUE;
//	afx_msg void OnClickedRadiocolor();
	afx_msg void OnClickedRadiocolor();
	afx_msg void OnRadioblack();
	afx_msg void OnClickedButtonapply();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
