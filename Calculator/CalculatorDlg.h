
// CalculatorDlg.h : ͷ�ļ�
//

#pragma once

#include "Stack.h"
#include <Cmath>

// CCalculatorDlg �Ի���
class CCalculatorDlg : public CDialogEx
{
// ����
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CALCULATOR_DIALOG };

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
	CString m_equation;									//ʽ��
	CString m_expression;
	CString m_result;									//���

	CStatic m_static_eq;
	CStatic m_static_re;

	CButton m_bt_0;
	CButton m_bt_1;
	CButton m_bt_2;
	CButton m_bt_3;
	CButton m_bt_4;
	CButton m_bt_5;
	CButton m_bt_6;
	CButton m_bt_7;
	CButton m_bt_8;
	CButton m_bt_9;
	CButton m_bt_clean;
	CButton m_bt_delete;
	CButton m_bt_div;
	CButton m_bt_equal;
	CButton m_bt_left;
	CButton m_bt_minus;
	CButton m_bt_mul;
	CButton m_bt_plus;
	CButton m_bt_point;
	CButton m_bt_right;

	CStack<wchar_t,50>  chStack;						// ����һ������ջ
	CStack<double,50>  numStack;						// ����һ������ջ

	afx_msg void OnClickedButtonClean();
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnClickedButtonEqual();
	afx_msg void OnClickedButtonMul();
	afx_msg void OnClickedButtonDiv();
	afx_msg void OnClickedButtonPlus();
	afx_msg void OnClickedButtonMinus();
	afx_msg void OnClickedButtonLeft();
	afx_msg void OnClickedButtonRight();
	afx_msg void OnClickedButtonPoint();
	afx_msg void OnClickedButton0();
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
	afx_msg void OnClickedButton3();
	afx_msg void OnClickedButton4();
	afx_msg void OnClickedButton5();
	afx_msg void OnClickedButton6();
	afx_msg void OnClickedButton7();
	afx_msg void OnClickedButton8();
	afx_msg void OnClickedButton9();

	void firstzero();
	double Calculate(CString expression);
	bool calc();
	CString Display(CString expression);

};
