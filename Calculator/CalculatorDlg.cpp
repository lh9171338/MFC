
// CalculatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define L_NUM 25				//һ������ַ�����
#define T_NUM L_NUM*2			//����ַ�����

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCalculatorDlg �Ի���




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


// CCalculatorDlg ��Ϣ�������

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CFont font;
	font.CreatePointFont(10,_T("����"));
	m_static_eq.SetFont(&font);
	m_static_re.SetFont(&font);

	/**********************************����ͼƬ***************************************/
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}











void CCalculatorDlg::OnClickedButtonClean()			//���
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_expression=_T("");
	m_result=_T("");
	m_equation=Display(m_expression);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButtonDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int length=m_expression.GetLength();
	if(length>0)
	{
		m_expression.Delete(length-1);
		m_equation=Display(m_expression);
		UpdateData(false);
	}
}


void CCalculatorDlg::OnClickedButtonEqual()		//���17λ��Ч����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	double result;
	result=Calculate(m_expression);
	if(result==NULL)
	{
		m_result=_T("error");
	}
	else
	{
		m_result.Format(_T("%lf"),result);		//���һλ����������
		if(m_result.GetLength()>T_NUM)
			m_result=_T("error");
	}
	m_result=Display(m_result);
	UpdateData(false);
}


void CCalculatorDlg::OnClickedButtonMul()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


void CCalculatorDlg::OnClickedButtonLeft()		//������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


void CCalculatorDlg::OnClickedButtonRight()		//������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	int a=0,b=0,le=0,ri=0;
	if(length>0)
	{
		for(a=0;a<length;a++)					//�������������
		{
			if(m_expression.GetAt(a)=='(')
			{
				le++;
			}
		}
		for(b=0;b<length;b++)					//�������������
		{
			if(m_expression.GetAt(b)==')')
			{
				ri++;
			}
		}
		wchar_t ch1=m_expression.GetAt(length-1);
		if(ch1>='0'&&ch1<='9'&&le>ri)			//���ֺ���ſ�����������
		{
			m_expression.AppendChar(')');
			m_equation=Display(m_expression);
			UpdateData(false);
		}
	}
}


void CCalculatorDlg::OnClickedButtonPoint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int length=m_expression.GetLength();
	if(length>=T_NUM)
		return;
	int a;
	if(length==0)								//��һ��������ǡ�.�������
	{
		m_expression.AppendChar('0');
		m_expression.AppendChar('.');
		m_equation=Display(m_expression);
		UpdateData(false);
	}
	else
	{
		wchar_t ch1=m_expression.GetAt(length-1);
		if(ch1=='('||ch1=='+'||ch1=='-'||ch1=='*'||ch1=='/')	//ǰ����+,-,*,/,(�����
		{
			m_expression.AppendChar('0');
			m_expression.AppendChar('.');
			m_equation=Display(m_expression);
			UpdateData(false);
		}
		else if(ch1>='0'&&ch1<='9')				//ǰ�������ֵ����
		{
			a=length-1;
			while(a>0&&ch1>='0'&&ch1<='9')
			{
				ch1=m_expression.GetAt(--a);
			}
			if(ch1!='.')						//ǰ���������û��С����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	while(expression.GetLength() > 0)			//�����ʽ��û�н�����
	{
		wchar_t ch = expression.GetAt(0);		//��ȡ��ǰ���ʽͷ���ĵ�һ���ַ�
		expression.Delete(0);					//ɾ����һ���ַ�(��һ����ɾ��һ����
		double num = 0;
		bool existNum = false;
		while (ch >= '0' && ch <= '9')			//����ǰ��ȡ����������
		{
			num = num * 10 + ch-'0';			//������Ϊ��ʹch��ʾʵ�ʵ���ֵ��������ASCII��ֵ
			existNum = true;
			if (expression.GetLength() > 0)		//����ȡ��
			{
				ch = expression.GetAt(0);
				expression.Delete(0);
			} 
			else 	
			{
				break;
			}
		}
		if(ch=='.')								//����ǰ��ȡ������С����
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
				if (expression.GetLength() > 0)	//����ȡ��
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
		if (existNum)							// ���ոս�����һ�����֣�������ѹջ
		{
			numStack.push(num);
			//���������ʽ�Ľ����Ѿ������ˡ��������Ϊ�����ֽ���
			if(expression.GetLength() == 0 && ch >= '0' && ch <= '9')
			{
				break;//����whileѭ��
			}
		}
		/*// ������ջΪ�� �� ջ��Ԫ��Ϊ������ �� ch�������������,��ֱ�ӽ�����ѹ��ջ
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
				// ����ǰ������������,�򲻶ϵĵ���һ���������������������ֱ������������Ϊֹ
				while (numStack.size() >= 2 && !chStack.isEmpty() && chStack.peek() != '(') 
				{
					if(!calc())
						return NULL;
				}
				if (!chStack.isEmpty() && chStack.peek() == '(') 
				{
					chStack.pop();				// �������������
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
				// ������ջջ��Ԫ��Ϊ+��-��( ���߷���ջΪ�գ�����ζ�ŷ���ջջ�����ű�ch���ȼ��ף����ԣ���chѹջ�����򣬽�����ջջ��Ԫ�ص�������Ȼ��ʼ����
				while (numStack.size() >= 2 && !(chStack.isEmpty() ||chStack.peek() == '(' 
						|| chStack.peek() == '+' || chStack.peek() == '-')) 
				{
					if(!calc())
						return NULL;
							
				}
				// ������ջջ��Ԫ�����ȼ���ch�ĵ�
				if (chStack.isEmpty() || chStack.peek() == '(' || chStack.peek() == '+' || chStack.peek() == '-')
				{
					chStack.push(ch);	
					continue;
				}
			}
			case '+':
			case '-':
			{
				// ����ǰ����ջջ��Ԫ�ز���(������ջҲ��Ϊ�գ��򽫷���ջջ��Ԫ�ص�������Ȼ��ʼ���㡣��Ϊ+��-�ŵ����ȼ���͡�
				while (numStack.size() >= 2 && !chStack.isEmpty() && chStack.peek() !='(')
				{
					if(!calc())
						return NULL;
				}
				if (chStack.isEmpty() || chStack.peek() == '(') 
				{
					// ������ջջ��Ԫ��Ϊ(�������ջΪ�գ���chѹջ��
					chStack.push(ch);
					continue;
				} 
				else 
				{
					return NULL;						//���ʽ��ʽ���Ϸ�!
				}
			}
			default : return NULL;						//������Ƿ�!
		}// switch ����
	}// while ����
	// ������ջ��Ϊ�գ��򲻶ϵĴӷ���ջ������ջ�е���Ԫ�أ����м���
	while(!chStack.isEmpty())
	{
		if(!calc())
			return NULL;
	}
	// ����������ջ�н���һ��Ԫ�أ���֤�����ʽ��ȷ��ջ��Ԫ�ؾ��Ǳ��ʽ��ֵ
	return numStack.size() == 1 ? numStack.pop() : NULL;
}
bool CCalculatorDlg::calc()
{
	double b = numStack.pop();	//ȡ����һ����
	double a = numStack.pop();	//ȡ���ڶ�����
	wchar_t op = chStack.pop();	//ȡ�������
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
	numStack.push(result);		 //������Ľ��ѹջ
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
