
// colorbuttonDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "colorbutton.h"
#include "colorbuttonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CcolorbuttonDlg �Ի���




CcolorbuttonDlg::CcolorbuttonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcolorbuttonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_color = 0;
}

void CcolorbuttonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIOCOLOR, m_color);
	DDX_Check(pDX, IDC_CHECKRED, m_RED);
	DDX_Check(pDX, IDC_CHECKGREEN, m_GREEN);
	DDX_Check(pDX, IDC_CHECKBLUE, m_BLUE);
}

BEGIN_MESSAGE_MAP(CcolorbuttonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_RADIOCOLOR, &CcolorbuttonDlg::OnClickedRadiocolor)
	ON_COMMAND(IDC_RADIOBLACK, &CcolorbuttonDlg::OnRadioblack)
	ON_BN_CLICKED(IDC_BUTTONAPPLY, &CcolorbuttonDlg::OnClickedButtonapply)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CcolorbuttonDlg ��Ϣ�������

BOOL CcolorbuttonDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CcolorbuttonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcolorbuttonDlg::OnPaint()
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
HCURSOR CcolorbuttonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CcolorbuttonDlg::OnClickedRadiocolor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_color=1;
	CWnd *p;
	p=GetDlgItem(IDC_CHECKRED);
	p->EnableWindow(true);
	p=GetDlgItem(IDC_CHECKGREEN);
	p->EnableWindow(true);
	p=GetDlgItem(IDC_CHECKBLUE);
	p->EnableWindow(true);
}


void CcolorbuttonDlg::OnRadioblack()
{
	// TODO: �ڴ���������������
	//m_color=0;
	CWnd *p;
	p=GetDlgItem(IDC_CHECKRED);
	p->EnableWindow(false);
	p=GetDlgItem(IDC_CHECKGREEN);
	p->EnableWindow(false);
	p=GetDlgItem(IDC_CHECKBLUE);
	p->EnableWindow(false);
}


void CcolorbuttonDlg::OnClickedButtonapply()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWnd *p=GetDlgItem(IDC_BUTTONDRAW);
	p->Invalidate();
	p->UpdateWindow();
}


void CcolorbuttonDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData();
	COLORREF m_c;
	if(m_color==0)
		m_c=RGB(m_RED?255:0,m_GREEN?255:0,m_BLUE?255:0);
	else
		m_c=RGB(0,0,0);
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);				//���Ӿ��
	if(nIDCtl==IDC_BUTTONDRAW)
	{
		CWnd *p=GetDlgItem(IDC_BUTTONDRAW);
		CRect r;
		p->GetClientRect(&r);						//��ȡ������ռ����
		dc.FillSolidRect(&r,m_c);					//���ư���
	}
	dc.Detach();									//������
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
