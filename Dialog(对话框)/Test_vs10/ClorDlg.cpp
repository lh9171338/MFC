// ClorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test_vs10.h"
#include "ClorDlg.h"
#include "afxdialogex.h"
//#include "Test_vs10View.h"


// CClorDlg dialog

IMPLEMENT_DYNAMIC(CClorDlg, CDialogEx)

CClorDlg::CClorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClorDlg::IDD, pParent)
{

	m_iColor = 0;
	m_bCorlorDlgUsed = FALSE;


}

CClorDlg::~CClorDlg()
{
}

void CClorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIOCLR, m_iColor);
	DDX_Check(pDX, IDC_CHECKBLU, m_bBlue);
	DDX_Check(pDX, IDC_CHECKRED, m_bRed);
	DDX_Check(pDX, IDC_CHECKGRE, m_bGreen);
}


BEGIN_MESSAGE_MAP(CClorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIOCLR, &CClorDlg::OnBnClickedRadioclr)
	ON_BN_CLICKED(IDC_RADIOBLK, &CClorDlg::OnRadioblk)
	ON_BN_CLICKED(IDC_BUTTONDRAW, &CClorDlg::OnBnClickedButtondraw)
	ON_BN_CLICKED(IDC_BUTTONBITMAP, &CClorDlg::OnBnClickedButtonbitmap)
	ON_BN_CLICKED(IDC_BUTTONAPPLY, &CClorDlg::OnBnClickedButtonapply)
	ON_BN_CLICKED(IDC_BUTTONCOL, &CClorDlg::OnBnClickedButtoncol)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_CHECKRED, &CClorDlg::OnBnClickedCheckred)
	ON_BN_CLICKED(IDC_CHECKGRE, &CClorDlg::OnBnClickedCheckgre)
	ON_BN_CLICKED(IDC_CHECKBLU, &CClorDlg::OnBnClickedCheckblu)
END_MESSAGE_MAP()


// CClorDlg message handlers


void CClorDlg::OnBnClickedRadioclr()
{
	// TODO: Add your control notification handler code here
		CWnd* pwnd = NULL;
	
	pwnd = GetDlgItem(IDC_CHECKRED);
	pwnd->EnableWindow(true);
	
	pwnd = GetDlgItem(IDC_CHECKBLU);
	pwnd->EnableWindow(true);
	
	pwnd = GetDlgItem(IDC_CHECKGRE);
	pwnd->EnableWindow(true);

	pwnd = GetDlgItem(IDC_BUTTONCOL);
	pwnd->EnableWindow(true);
}


void CClorDlg::OnRadioblk()
{
	// TODO: Add your control notification handler code here
	CWnd* pwnd = NULL;

	pwnd = GetDlgItem(IDC_CHECKRED);
	pwnd->EnableWindow(false);

	pwnd = GetDlgItem(IDC_CHECKBLU);
	pwnd->EnableWindow(false);

	pwnd = GetDlgItem(IDC_CHECKGRE);
	pwnd->EnableWindow(false);

	pwnd = GetDlgItem(IDC_BUTTONCOL);
	pwnd->EnableWindow(false);
}


void CClorDlg::OnBnClickedButtondraw()
{
	// TODO: Add your control notification handler code here
}


void CClorDlg::OnBnClickedButtonbitmap()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T("sss"));
	
}


void CClorDlg::OnBnClickedButtonapply()
{
	// TODO: Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_BUTTONDRAW);
	pwnd->Invalidate();

	pwnd->UpdateWindow();
}


void CClorDlg::OnBnClickedButtoncol()
{
	// TODO: Add your control notification handler code here
	CColorDialog  coldlg;
	
	
	if(coldlg.DoModal() == IDOK)
	{

		CButton* pbun = (CButton*)GetDlgItem(IDC_RADIOCLR);
		pbun->SetCheck(true);

	
		m_iColor = 0;
		m_bCorlorDlgUsed = TRUE;
		
		UpdateData(false);
		OnBnClickedRadioclr();
		

		m_clrButn = coldlg.GetColor();

		CWnd* pwnd = GetDlgItem(IDC_BUTTONDRAW);
		pwnd->Invalidate();
		
		pwnd->UpdateWindow();
		
	}


}


void CClorDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	UpdateData();
	COLORREF clrButn;

	if(m_iColor == 0)
	{
		if(m_bCorlorDlgUsed == false)
			clrButn = RGB(m_bRed ? 255 : 0, m_bGreen ? 255 : 0, m_bBlue ? 255 : 0);
		else
			clrButn = m_clrButn;

	}
	else
	{
		clrButn = RGB(0,0,0);
	}

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	if(nIDCtl == IDC_BUTTONDRAW)
	{
		CWnd* pwnd = GetDlgItem(IDC_BUTTONDRAW);
		CRect rectButn;
		pwnd->GetClientRect(&rectButn);

	/*
		CPen pen(PS_SOLID, 2, clrButn);
			CPen* poldpen = dc.SelectObject(&pen);
	
			dc.Ellipse(rectButn.right / 2 - (rectButn.right / 2 - 4),
				rectButn.bottom / 2 - (rectButn.bottom / 2 - 4),
				rectButn.right / 2 + (rectButn.right / 2 - 4),
				rectButn.bottom / 2 + (rectButn.bottom / 2 - 4));
	
			dc.SelectObject(poldpen);*/
	
		
		
		
		dc.FillSolidRect(&rectButn, clrButn);
	}

	dc.Detach();


	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


BOOL CClorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CButton *pBtn = (CButton*)GetDlgItem(IDC_BUTTONBITMAP);//IDC_BUTTON1是需要使用位图按钮的ID
	CBitmap Bitmap;
	Bitmap.LoadBitmap(IDB_BITMAP_BTN); //其中IDB_BITMAP1为使用的位图
	HBITMAP hBitmap = (HBITMAP)Bitmap.Detach();     
	pBtn->SetBitmap(hBitmap);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CClorDlg::OnBnClickedCheckred()
{
	// TODO: Add your control notification handler code here
	m_bCorlorDlgUsed = FALSE;
}


void CClorDlg::OnBnClickedCheckgre()
{
	// TODO: Add your control notification handler code here
	m_bCorlorDlgUsed = FALSE;
}


void CClorDlg::OnBnClickedCheckblu()
{
	// TODO: Add your control notification handler code here
	m_bCorlorDlgUsed = FALSE;
}
