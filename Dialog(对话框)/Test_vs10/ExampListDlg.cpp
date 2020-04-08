// ExampListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test_vs10.h"
#include "ExampListDlg.h"
#include "afxdialogex.h"


// CExampListDlg dialog

IMPLEMENT_DYNAMIC(CExampListDlg, CDialogEx)

CExampListDlg::CExampListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExampListDlg::IDD, pParent)
{

	m_nArea = 0;
	m_nPopulat = 0;
}

CExampListDlg::~CExampListDlg()
{
}

void CExampListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITAREA, m_nArea);
	DDX_Text(pDX, IDC_EDITPOPULAT, m_nPopulat);
	DDX_Text(pDX, IDC_EDITCAPITAL, m_strCapitao);
	DDX_Text(pDX, IDC_EDITNAME, m_strName);
	DDX_Control(pDX, IDC_LIST_CTRLCOUNTRY, m_listCountry);
	DDX_Control(pDX, IDC_LISTSTATE, m_ListBx);

}


BEGIN_MESSAGE_MAP(CExampListDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CExampListDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CExampListDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDOK, &CExampListDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CTRLCOUNTRY, &CExampListDlg::OnLvnItemchangedListCtrlcountry)
	ON_LBN_SELCHANGE(IDC_LISTSTATE, &CExampListDlg::OnLbnSelchangeListstate)
END_MESSAGE_MAP()


// CExampListDlg message handlers


BOOL CExampListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

		CRect rect;
	m_listCountry.GetWindowRect(&rect);
	int width = (rect.right - rect.left)/4;
	m_listCountry.InsertColumn(0,_T("国家"),LVCFMT_CENTER,width);
	m_listCountry.InsertColumn(1,_T("首都"),LVCFMT_LEFT,width);
	m_listCountry.InsertColumn(2,_T("人口"),LVCFMT_LEFT,width);
	m_listCountry.InsertColumn(3,_T("面积"),LVCFMT_LEFT,width);

	m_listCountry.SetItemCount( 10 );	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CExampListDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	 UpdateData(TRUE);

	if(m_strName.IsEmpty())
	{
		AfxMessageBox(_T("Name can not be empty"));
		return;

	}

	m_strName.TrimLeft();
	m_strName.TrimRight();

	if((m_ListBx.FindString(-1, m_strName)) != LB_ERR)
	{
		AfxMessageBox(_T("This item already exist, can not be added"));
		return;
		
	}

	int iIndex = m_ListBx.AddString(m_strName);
	
	SState stState;
	stState.strName = m_strName;
	stState.strCap = m_strCapitao;
	stState.nPopu = m_nPopulat;
	stState.nArea = m_nArea;

	m_ListBx.SetItemDataPtr(iIndex, new SState(stState));

////////////////add list ctrl data/////////////////////////////////////////////////
	CString strT ;
	int nTotal=m_listCountry.GetItemCount();
	CString str;
	if(nTotal>=10)
	{
		m_listCountry.DeleteItem(0);
		nTotal--;
	}

	m_listCountry. InsertItem ( nTotal, strT);
	
	m_listCountry.SetItemText(nTotal, 0, m_strName);
	
	m_listCountry.SetItemText(nTotal, 1, m_strCapitao);

	str.Format(_T("%d"),m_nPopulat);
	m_listCountry.SetItemText(nTotal, 2, str);
	
	str.Format(_T("%d"),m_nArea);
	m_listCountry.SetItemText (nTotal, 3, str);
}


void CExampListDlg::OnBnClickedButtonDel()
{
	// TODO: Add your control notification handler code here
	int iIndex = m_ListBx.GetCurSel();

	if(iIndex != LB_ERR)
	{
		delete (SState *)m_ListBx.GetItemDataPtr(iIndex);
		m_ListBx.DeleteString(iIndex);
		m_strName = m_strCapitao = "";
		m_nPopulat = m_nArea = 0;

		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("Delete fail"));
	}
}


void CExampListDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CExampListDlg::OnLvnItemchangedListCtrlcountry(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	int iChoice = m_listCountry.GetNextItem(-1, LVNI_SELECTED);

    if(iChoice != -1)
	{
		m_strName = m_listCountry.GetItemText(iChoice, 0);
		m_strCapitao = m_listCountry.GetItemText(iChoice, 1);
		CString strPopu = m_listCountry.GetItemText(iChoice, 2);
		//m_nPopulat =	atoi(strPopu);
		strPopu = m_listCountry.GetItemText(iChoice, 3);
		//m_nArea = atoi(strPopu);
		UpdateData(false);
	}



	*pResult = 0;
}


void CExampListDlg::OnLbnSelchangeListstate()
{
	// TODO: Add your control notification handler code here
		int iIndex = m_ListBx.GetCurSel();

	if(iIndex != LB_ERR)
	{
		SState *pSt = (SState *)m_ListBx.GetItemDataPtr(iIndex);
		m_strName = pSt->strName;
		m_strCapitao = pSt->strCap;
		m_nArea = pSt->nArea;
		m_nPopulat = pSt->nPopu;

		UpdateData(false);
	}
	
}
