
// CalculatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define L_NUM 25				//一行最大字符个数
#define T_NUM L_NUM*2			//最大字符个数

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg 对话框




CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalculatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_equation = _T("");
	m_result = _T("");
	chStack=CStack<wchar_t,50>();				
	numStack=CStack<double,50>();				
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_EQUATION, m_static_eq);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_static_re);
	DDX_Text(pDX, IDC_STATIC_EQUATION, m_equation);
	DDV_MaxChars(pDX, m_equation, 50);
	DDX_Text(pDX, IDC_STATIC_RESULT, m_result);
	DDV_MaxChars(pDX, m_result, 50);
	DDX_Control(pDX, IDC_BUTTON_0, m_bt_0);
	DDX_Control(pDX, IDC_BUTTON_1, m_bt_1);
	DDX_Control(pDX, IDC_BUTTON_2, m_bt_2);
	DDX_Control(pDX, IDC_BUTTON_3, m_bt_3);
	DDX_Control(pDX, IDC_BUTTON_4, m_bt_4);
	DDX_Control(pDX, IDC_BUTTON_5, m_bt_5);
	DDX_Control(pDX, IDC_BUTTON_6, m_bt_6);
	DDX_Control(pDX, IDC_BUTTON_7, m_bt_7);
	DDX_Control(pDX, IDC_BUTTON_8, m_bt_8);
	DDX_Control(pDX, IDC_BUTTON_9, m_bt_9);
	DDX_Control(pDX, IDC_BUTTON_CLEAN, m_bt_clean);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_bt_delete);
	DDX_Control(pDX, IDC_BUTTON_DIV, m_bt_div);
	DDX_Control(pDX, IDC_BUTTON_EQUAL, m_bt_equal);
	DDX_Control(pDX, IDC_BUTTON_LEFT, m_bt_left);
	DDX_Control(pDX, IDC_BUTTON_MINUS, m_bt_minus);
	DDX_Control(pDX, IDC_BUTTON_MUL, m_bt_mul);
	DDX_Control(pDX, IDC_BUTTON_PLUS, m_bt_plus);
	DDX_Control(pDX, IDC_BUTTON_POINT, m_bt_point);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, m_bt_right);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CCalculatorDlg::OnClickedButtonClean)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CCalculatorDlg::OnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CCalculatorDlg::OnClickedButtonEqual)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CCalculatorDlg::OnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalculatorDlg::OnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorDlg::OnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CCalculatorDlg::OnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CCalculatorDlg::OnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CCalculatorDlg::OnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_POINT, &CCalculatorDlg::OnClickedButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_0, &CCalculatorDlg::OnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_1, &CCalculatorDlg::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCalculatorDlg::OnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCalculatorDlg::OnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCalculatorDlg::OnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCalculatorDlg::OnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCalculatorDlg::OnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCalculatorDlg::OnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCalculatorDlg::OnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCalculatorDlg::OnClickedButton9)
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CFont font;
	font.CreatePointFont(10,_T("楷体"));
	m_static_eq.SetFont(&font);
	m_static_re.SetFont(&font);

	/**********************************加载图片***************************************/
	CBitmap MemBitmap_0;
	CBitmap MemBitmap_1;
	CBitmap MemBitmap_2;
	CBitmap MemBitmap_3;
	CBitmap MemBitmap_4;
	CBitmap MemBitmap_5;
	CBitmap MemBitmap_6;
	CBitmap MemBitmap_7;
	CBitmap MemBitmap_8;
	CBitmap MemBitmap_9;
	CBitmap MemBitmap_clean;
	CBitmap MemBitmap_delete;
	CBitmap MemBitmap_div;
	CBitmap MemBitmap_equal;
	CBitmap MemBitmap_left;
	CBitmap MemBitmap_minus;
	CBitmap MemBitmap_mul;
	CBitmap MemBitmap_plus;
	CBitmap MemBitmap_point;
	CBitmap MemBitmap_right;

	MemBitmap_0.LoadBitmap(IDB_BITMAP_0);
	MemBitmap_1.LoadBitmap(IDB_BITMAP_1);
	MemBitmap_2.LoadBitmap(IDB_BITMAP_2);
	MemBitmap_3.LoadBitmap(IDB_BITMAP_3);
	MemBitmap_4.LoadBitmap(IDB_BITMAP_4);
	MemBitmap_5.LoadBitmap(IDB_BITMAP_5);
	MemBitmap_6.LoadBitmap(IDB_BITMAP_6);
	MemBitmap_7.LoadBitmap(IDB_BITMAP_7);
	MemBitmap_8.LoadBitmap(IDB_BITMAP_8);
	MemBitmap_9.LoadBitmap(IDB_BITMAP_9);
	MemBitmap_clean.LoadBitmap(IDB_BITMAP_CLEAN);
	MemBitmap_delete.LoadBitmap(IDB_BITMAP_DELETE);
	MemBitmap_div.LoadBitmap(IDB_BITMAP_CHU);
	MemBitmap_equal.LoadBitmap(IDB_BITMAP_DENG);
	MemBitmap_left.LoadBitmap(IDB_BITMAP_LEFT);
	MemBitmap_minus.LoadBitmap(IDB_BITMAP_JIAN);
	MemBitmap_mul.LoadBitmap(IDB_BITMAP_CHENG);
	MemBitmap_plus.LoadBitmap(IDB_BITMAP_JIA);
	MemBitmap_point.LoadBitmap(IDB_BITMAP_DIAN);
	MemBitmap_right.LoadBitmap(IDB_BITMAP_RIGHT);

	m_bt_0.SetBitmap(MemBitmap_0);
	m_bt_1.SetBitmap(MemBitmap_1);
	m_bt_2.SetBitmap(MemBitmap_2);
	m_bt_3.SetBitmap(MemBitmap_3);
	m_bt_4.SetBitmap(MemBitmap_4);
	m_bt_5.SetBitmap(MemBitmap_5);
	m_bt_6.SetBitmap(MemBitmap_6);
	m_bt_7.SetBitmap(MemBitmap_7);
	m_bt_8.SetBitmap(MemBitmap_8);
	m_bt_9.SetBitmap(MemBitmap_9);
	m_bt_clean.SetBitmap(MemBitmap_clean);
	m_bt_delete.SetBitmap(MemBitmap_delete);
	m_bt_div.SetBitmap(MemBitmap_div);
	m_bt_equal.SetBitmap(MemBitmap_equal);
	m_bt_left.SetBitmap(MemBitmap_left);
	m_bt_minus.SetBitmap(MemBitmap_minus);
	m_bt_mul.SetBitmap(MemBitmap_mul);
	m_bt_plus.SetBitmap(MemBitmap_plus);
	m_bt_point.SetBitmap(MemBitmap_point);
	m_bt_right.SetBitmap(MemBitmap_right);

	MemBitmap_0.DeleteObject();
	MemBitmap_1.DeleteObject();
	MemBitmap_2.DeleteObject();
	MemBitmap_3.DeleteObject();
	MemBitmap_4.DeleteObject();
	MemBitmap_5.DeleteObject();
	MemBitmap_6.DeleteObject();
	MemBitmap_7.DeleteObject();
	MemBitmap_8.DeleteObject();
	MemBitmap_9.DeleteObject();
	MemBitmap_clean.DeleteObject();
	MemBitmap_delete.DeleteObject();
	MemBitmap_div.DeleteObject();
	MemBitmap_equal.DeleteObject();
	MemBitmap_left.DeleteObject();
	MemBitmap_minus.DeleteObject();
	MemBitmap_mul.DeleteObject();
	MemBitmap_plus.DeleteObject();
	MemBitmap_point.DeleteObject();
	MemBitmap_right.DeleteObject();

	/*******************************************************************************/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}











void CCalculatorDlg::OnClickedButtonClean()			//清空
{
	// TODO: 在此添加控件通知处理程序代码
	m_expression=_T("");
	m_result=_T("");
	m_equation=Display(m_expression);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>0)
	{
		m_expression.Delete(length-1);
		m_equation=Display(m_expression);
		UpdateData(false);
	}
}


void CCalculatorDlg::OnClickedButtonEqual()		//最多17位有效数字
{
	// TODO: 在此添加控件通知处理程序代码
	double result;
	result=Calculate(m_expression);
	if(result==NULL)
	{
		m_result=_T("error");
	}
	else
	{
		m_result.Format(_T("%lf"),result);		//最后一位会四舍五入
		if(m_result.GetLength()>T_NUM)
			m_result=_T("error");
	}
	m_result=Display(m_result);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButtonMul()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	if(length>0)
	{
		wchar_t ch1=m_expression.GetAt(length-1);
		if(ch1>='0'&&ch1<='9'||ch1==')')
		{
			m_expression.AppendChar('*');
			m_equation=Display(m_expression);
			UpdateData(false);
		}
	}
}


void CCalculatorDlg::OnClickedButtonDiv()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	if(length>0)
	{
		wchar_t ch1=m_expression.GetAt(length-1);
		if(ch1>='0'&&ch1<='9'||ch1==')')
		{
			m_expression.AppendChar('/');
			m_equation=Display(m_expression);
			UpdateData(false);
		}
	}
}


void CCalculatorDlg::OnClickedButtonPlus()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	if(length>0)
	{
		wchar_t ch1=m_expression.GetAt(length-1);
		if(ch1>='0'&&ch1<='9'||ch1==')')
		{
			m_expression.AppendChar('+');
			m_equation=Display(m_expression);
			UpdateData(false);
		}
	}
}


void CCalculatorDlg::OnClickedButtonMinus()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	if(length>0)
	{
		wchar_t ch1=m_expression.GetAt(length-1);
		if(ch1>='0'&&ch1<='9'||ch1==')')
		{
			m_expression.AppendChar('-');
			m_equation=Display(m_expression);
			UpdateData(false);
		}
	}
}


void CCalculatorDlg::OnClickedButtonLeft()		//左括号
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	if(length==0)
	{
		m_expression.AppendChar('(');
		m_equation=Display(m_expression);
		UpdateData(false);
	}
	else
	{
		wchar_t ch1=m_expression.GetAt(length-1);
		if(ch1=='+'||ch1=='-'||ch1=='*'||ch1=='/'||ch1=='(')
		{
			m_expression.AppendChar('(');
			m_equation=Display(m_expression);
			UpdateData(false);
		}
	}
}


void CCalculatorDlg::OnClickedButtonRight()		//右括号
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	int a=0,b=0,le=0,ri=0;
	if(length>0)
	{
		for(a=0;a<length;a++)					//获得左括号数量
		{
			if(m_expression.GetAt(a)=='(')
			{
				le++;
			}
		}
		for(b=0;b<length;b++)					//获得右括号数量
		{
			if(m_expression.GetAt(b)==')')
			{
				ri++;
			}
		}
		wchar_t ch1=m_expression.GetAt(length-1);
		if(ch1>='0'&&ch1<='9'&&le>ri)			//数字后面才可以是右括号
		{
			m_expression.AppendChar(')');
			m_equation=Display(m_expression);
			UpdateData(false);
		}
	}
}


void CCalculatorDlg::OnClickedButtonPoint()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	int a;
	if(length==0)								//第一个输入的是“.”的情况
	{
		m_expression.AppendChar('0');
		m_expression.AppendChar('.');
		m_equation=Display(m_expression);
		UpdateData(false);
	}
	else
	{
		wchar_t ch1=m_expression.GetAt(length-1);
		if(ch1=='('||ch1=='+'||ch1=='-'||ch1=='*'||ch1=='/')	//前面是+,-,*,/,(的情况
		{
			m_expression.AppendChar('0');
			m_expression.AppendChar('.');
			m_equation=Display(m_expression);
			UpdateData(false);
		}
		else if(ch1>='0'&&ch1<='9')				//前面是数字的情况
		{
			a=length-1;
			while(a>0&&ch1>='0'&&ch1<='9')
			{
				ch1=m_expression.GetAt(--a);
			}
			if(ch1!='.')						//前面的数字中没有小数点
			{
				m_expression.AppendChar('.');
				m_equation=Display(m_expression);
				UpdateData(false);
			}
		}
	}
}

void CCalculatorDlg::firstzero()
{
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	if(length==1&&m_expression.GetAt(0)=='0')
	{
		m_expression=_T("");
	}
	else if(length>1)
	{
		wchar_t ch1=m_expression.GetAt(length-2);
		wchar_t ch2=m_expression.GetAt(length-1);
		if((ch1=='+'||ch1=='-'||ch1=='*'||ch1=='/'||ch1=='('||ch1==')')&&ch2=='0')
		{
			m_expression.Delete(length-1);
		}
	}
}

void CCalculatorDlg::OnClickedButton0()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	firstzero();
	m_expression.AppendChar('0');
	m_equation=Display(m_expression);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	firstzero();
	m_expression.AppendChar('1');
	m_equation=Display(m_expression);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	firstzero();
	m_expression.AppendChar('2');
	m_equation=Display(m_expression);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	firstzero();
	m_expression.AppendChar('3');
	m_equation=Display(m_expression);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	firstzero();
	m_expression.AppendChar('4');
	m_equation=Display(m_expression);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	firstzero();
	m_expression.AppendChar('5');
	m_equation=Display(m_expression);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	firstzero();
	m_expression.AppendChar('6');
	m_equation=Display(m_expression);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	firstzero();
	m_expression.AppendChar('7');
	m_equation=Display(m_expression);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	firstzero();
	m_expression.AppendChar('8');
	m_equation=Display(m_expression);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	firstzero();
	m_expression.AppendChar('9');
	m_equation=Display(m_expression);
	UpdateData(false);
}
/*chStack=CStack();				
	numStack*/
double CCalculatorDlg::Calculate(CString expression)
{
	while(expression.GetLength() > 0)			//若表达式还没有解析完
	{
		wchar_t ch = expression.GetAt(0);		//获取当前表达式头部的第一个字符
		expression.Delete(0);					//删除第一个字符(拿一个，删除一个）
		double num = 0;
		bool existNum = false;
		while (ch >= '0' && ch <= '9')			//若当前读取到的是数字
		{
			num = num * 10 + ch-'0';			//减零是为了使ch表示实际的数值，而不是ASCII码值
			existNum = true;
			if (expression.GetLength() > 0)		//继续取数
			{
				ch = expression.GetAt(0);
				expression.Delete(0);
			} 
			else 	
			{
				break;
			}
		}
		if(ch=='.')								//若当前读取到的是小数点
		{
			ch = expression.GetAt(0);
			expression.Delete(0);
			int i=1;
			while (ch >= '0' && ch <= '9')
			{
				double mi=pow(0.1,i);
				i++;
				num=num+(ch-'0')*mi;
				existNum = true;
				if (expression.GetLength() > 0)	//继续取数
				{
					ch = expression.GetAt(0);
					expression.Delete(0);
				} 
				else 	
				{
					break;
				}
			}
		}
		if (existNum)							// 若刚刚解析完一个数字，则将数字压栈
		{
			numStack.push(num);
			//若整个表达式的解析已经结束了。这种情况为以数字结束
			if(expression.GetLength() == 0 && ch >= '0' && ch <= '9')
			{
				break;//结束while循环
			}
		}
		/*// 若符号栈为空 或 栈顶元素为左括号 或 ch本身就是左括号,则直接将符号压入栈
		if (this.chStack.isEmpty() || this.chStack.peek() == '(' || ch == '(') 
		{
			this.chStack.push(ch);
			continue;
		}*/
		switch (ch) 
		{
			case '(':
				chStack.push(ch);
				continue;
			case ')': 
			{
				// 若当前符号是右括号,则不断的弹出一个运算符和两个操作数，直到遇到左括号为止
				while (numStack.size() >= 2 && !chStack.isEmpty() && chStack.peek() != '(') 
				{
					if(!calc())
						return NULL;
				}
				if (!chStack.isEmpty() && chStack.peek() == '(') 
				{
					chStack.pop();				// 弹出这个左括号
					continue;
				} 	
				else 
				{
					return NULL;
				}
			}
			case '*':
			case '/':
			{
				// 若符号栈栈顶元素为+、-、( 或者符号栈为空，则意味着符号栈栈顶符号比ch优先级底，所以，将ch压栈。否则，将符号栈栈顶元素弹出来，然后开始计算
				while (numStack.size() >= 2 && !(chStack.isEmpty() ||chStack.peek() == '(' 
						|| chStack.peek() == '+' || chStack.peek() == '-')) 
				{
					if(!calc())
						return NULL;
							
				}
				// 若符号栈栈顶元素优先级比ch的低
				if (chStack.isEmpty() || chStack.peek() == '(' || chStack.peek() == '+' || chStack.peek() == '-')
				{
					chStack.push(ch);	
					continue;
				}
			}
			case '+':
			case '-':
			{
				// 若当前符号栈栈顶元素不是(，符号栈也不为空，则将符号栈栈顶元素弹出来，然后开始计算。因为+、-号的优先级最低。
				while (numStack.size() >= 2 && !chStack.isEmpty() && chStack.peek() !='(')
				{
					if(!calc())
						return NULL;
				}
				if (chStack.isEmpty() || chStack.peek() == '(') 
				{
					// 若符号栈栈顶元素为(、或符号栈为空，则将ch压栈。
					chStack.push(ch);
					continue;
				} 
				else 
				{
					return NULL;						//表达式格式不合法!
				}
			}
			default : return NULL;						//运算符非法!
		}// switch 结束
	}// while 结束
	// 若符号栈不为空，则不断的从符号栈和数字栈中弹出元素，进行计算
	while(!chStack.isEmpty())
	{
		if(!calc())
			return NULL;
	}
	// 若最终数字栈中仅存一个元素，则证明表达式正确，栈顶元素就是表达式的值
	return numStack.size() == 1 ? numStack.pop() : NULL;
}
bool CCalculatorDlg::calc()
{
	double b = numStack.pop();	//取出第一个数
	double a = numStack.pop();	//取数第二个数
	wchar_t op = chStack.pop();	//取数运算符
	double result = 0;
	switch (op) 
	{
		case '+': result = a + b; break;
		case '-': result = a - b; break;
		case '*': result = a * b; break;
		case '/': 
		{
			if (b == 0)					//error
			{
				return false;
			}
			result = a / b;
			break;
		}
	}
	numStack.push(result);		 //将运算的结果压栈
	return true;
}

CString CCalculatorDlg::Display(CString expression)
{
	int length=expression.GetLength();
	CString str=expression;
	if(length>L_NUM)
	{
		str.Insert(L_NUM,'\n');
	}
	//if(length>2*L_NUM)
	//{
	//	str.Insert(2*L_NUM+1,'\n');
	//}
	return str;
}
