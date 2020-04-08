
// CalculatorDlg.h : 头文件
//

#pragma once

#include "Stack.h"
#include <Cmath>

// CCalculatorDlg 对话框
class CCalculatorDlg : public CDialogEx
{
// 构造
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_equation;									//式子
	CString m_expression;
	CString m_result;									//结果

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

	CStack<wchar_t,50>  chStack;						// 创建一个符号栈
	CStack<double,50>  numStack;						// 创建一个数字栈

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
