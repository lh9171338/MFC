
// moveView.cpp : CmoveView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "move.h"
#endif

#include "moveDoc.h"
#include "moveView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmoveView

IMPLEMENT_DYNCREATE(CmoveView, CView)

BEGIN_MESSAGE_MAP(CmoveView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CmoveView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDB_L,ONLDOWN)
	ON_BN_CLICKED(IDB_R,ONRDOWN)
	ON_BN_CLICKED(IDB_U,ONUDOWN)
	ON_BN_CLICKED(IDB_D,ONDDOWN)
	ON_BN_CLICKED(IDB_START,ONSTARTDOWN)
	ON_BN_CLICKED(IDB_STOP,ONSTOPDOWN)
	ON_WM_TIMER()
	ON_COMMAND(ID_HARD, &CmoveView::OnHard)
	ON_UPDATE_COMMAND_UI(ID_HARD, &CmoveView::OnUpdateHard)
	ON_COMMAND(ID_EASY, &CmoveView::OnEasy)
	ON_UPDATE_COMMAND_UI(ID_EASY, &CmoveView::OnUpdateEasy)
	ON_COMMAND(ID_NORMAL, &CmoveView::OnNormal)
	ON_UPDATE_COMMAND_UI(ID_NORMAL, &CmoveView::OnUpdateNormal)
	ON_COMMAND(ID_VERYHARD, &CmoveView::OnVeryhard)
	ON_UPDATE_COMMAND_UI(ID_VERYHARD, &CmoveView::OnUpdateVeryhard)
END_MESSAGE_MAP()

// CmoveView ����/����

CmoveView::CmoveView()
{
	// TODO: �ڴ˴���ӹ������
	m_head.SetPoint(1,1);
	m_tail.SetPoint(1,1);
	d='R';
	sign=bagin=faster=lastfaster=false;
	life=true;
	hard=1000;
	score=0;
}

CmoveView::~CmoveView()
{
}

BOOL CmoveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CmoveView ����

void CmoveView::OnDraw(CDC* pDC)
{
	CmoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CClientDC dc(this);
	CPen pen1(PS_SOLID,1,RGB(0,0,255));
	dc.SelectObject(&pen1);
	dc.Rectangle(0,0,402,402);							//�߿�0��0������402��402����20*20
	dc.Rectangle(450,100,950,350);
	dc.Rectangle(490,290,600,320);
	dc.Rectangle(630,290,740,320);
	dc.Rectangle(790,130,900,290);
	if(bagin)
		draw();
	if(!life)
	{
		CBrush brush2(RGB(255,0,0));
		dc.SelectObject(&brush2);
		dc.Rectangle(720,170,760,200);
		dc.Rectangle(720,230,760,260);
	}
	else if(sign)
	{
		CBrush brush2(RGB(0,255,0));
		dc.SelectObject(&brush2);
		dc.Rectangle(720,170,760,200);
		CBrush brush3(RGB(255,0,0));
		dc.SelectObject(&brush3);
		dc.Rectangle(720,230,760,260);
	}
	else
	{
		CBrush brush2(RGB(255,0,0));
		dc.SelectObject(&brush2);
		dc.Rectangle(720,170,760,200);
		CBrush brush3(RGB(0,255,0));
		dc.SelectObject(&brush3);
		dc.Rectangle(720,230,760,260);
	}
	if(life)
	{
		dc.SetTextColor(RGB(0,255,0));
		dc.TextOutW(800,170,_T("life:alive"));
		CString str;
		switch(hard)
		{
		case 1000:str=_T("hard:easy");break;
		case 500:str=_T("hard:normal");break;
		case 200:str=_T("hard:hard");break;
		case 100:str=_T("hard:very hard");break;
		default:break;
		}
		dc.TextOutW(800,200,str);
		str.Format(_T("score:%d"),score);
		dc.TextOutW(800,230,str);
		str.Format(_T("lengh:%d"),getnumpoint());
		dc.TextOutW(800,260,str);
		dc.SetTextColor(RGB(153,0,102));
		if(faster)
			dc.TextOutW(800,140,_T("speed:faster"));
		else
			dc.TextOutW(800,140,_T("speed:normal"));
	}
	else
	{
		dc.SetTextColor(RGB(255,0,0));
		dc.TextOutW(800,170,_T("life:dead"));
		CString str;
		switch(hard)
		{
		case 1000:str=_T("hard:easy");break;
		case 500:str=_T("hard:normal");break;
		case 200:str=_T("hard:hard");break;
		case 100:str=_T("hard:very hard");break;
		default:break;
		}
		dc.TextOutW(800,200,str);
		str.Format(_T("score:%d"),score);
		dc.TextOutW(800,230,str);
		str.Format(_T("lengh:%d"),getnumpoint());
		dc.TextOutW(800,260,str);
		if(faster)
			dc.TextOutW(800,140,_T("speed:faster"));
		else
			dc.TextOutW(800,140,_T("speed:normal"));
	}
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CmoveView ��ӡ


void CmoveView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CmoveView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CmoveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CmoveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CmoveView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CmoveView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	CMenu menupopup;
	if(menupopup.CreatePopupMenu())
	{
	menupopup.AppendMenuW(MF_STRING,ID_EASY,_T("����\tCtrl+E"));
	menupopup.AppendMenuW(MF_STRING,ID_NORMAL,_T("һ��\tCtrl+B"));
	menupopup.AppendMenuW(MF_STRING,ID_HARD,_T("��\tCtrl+H"));
	menupopup.AppendMenuW(MF_STRING,ID_VERYHARD,_T("����\tCtrl+A"));
	menupopup.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);			//��ʾ�˵�
	}
}


// CmoveView ���

#ifdef _DEBUG
void CmoveView::AssertValid() const
{
	CView::AssertValid();
}

void CmoveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmoveDoc* CmoveView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmoveDoc)));
	return (CmoveDoc*)m_pDocument;
}
#endif //_DEBUG


// CmoveView ��Ϣ�������


int CmoveView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rect_button1(500,200,540,230);
	b1.Create(_T("��"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button1,this,IDB_L);
	b1.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button2(580,200,620,230);
	b2.Create(_T("��"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button2,this,IDB_R);
	b2.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button3(540,170,580,200);
	b3.Create(_T("��"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button3,this,IDB_U);
	b3.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button4(540,230,580,260);
	b4.Create(_T("��"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button4,this,IDB_D);
	b4.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button5(640,170,700,200);
	b5.Create(_T("��ʼ"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button5,this,IDB_START);
	b5.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button6(640,230,700,260);
	b6.Create(_T("��ͣ"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button6,this,IDB_STOP);
	b6.ShowWindow(SW_SHOWNORMAL);
	return 0;
}


void CmoveView::OnDestroy()
{
	CView::OnDestroy();
	KillTimer(1);
	// TODO: �ڴ˴������Ϣ����������
}
void CmoveView::ONLDOWN()
{
	if(d=='R')
		faster=false;
	else if(d=='L')
		faster=true;
	else
		d='L';
}
void CmoveView::ONRDOWN()
{
	if(d=='L')
		faster=false;
	else if(d=='R')
		faster=true;
	else
		d='R';
}
void CmoveView::ONUDOWN()
{
	if(d=='D')
		faster=false;
	else if(d=='U')
		faster=true;
	else
		d='U';
}
void CmoveView::ONDDOWN()
{
	if(d=='U')
		faster=false;
	else if(d=='D')
		faster=true;
	else
		d='D';
}
void CmoveView::ONSTARTDOWN()
{
	if(!sign&&life)
	{
		SetTimer(1,hard ,NULL);
		if(!bagin)
		{
			addpoint(m_head);
			food();
		}
		sign=bagin=true;
	}
}
void CmoveView::ONSTOPDOWN()
{
	if(sign&&life)
	{
		KillTimer(1);
		sign=false;
	}
}

void CmoveView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(lastfaster==false&&faster==true)
	{
		KillTimer(1);
		SetTimer(1,hard*0.5,NULL);
		lastfaster=true;
	}
	else if(lastfaster==true&&faster==false)
	{
		KillTimer(1);
		SetTimer(1,hard,NULL);
		lastfaster=false;
	}
	run();
	eat();
	CmoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UpdateAllViews(NULL);
	CView::OnTimer(nIDEvent);
}


void CmoveView::OnHard()
{
	// TODO: �ڴ���������������
	hard=200;
	CmoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UpdateAllViews(NULL);
}


void CmoveView::OnUpdateHard(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(hard==200||bagin)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CmoveView::OnEasy()
{
	// TODO: �ڴ���������������
	hard=1000;
	CmoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UpdateAllViews(NULL);
}


void CmoveView::OnUpdateEasy(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(hard==1000||bagin)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CmoveView::OnNormal()
{
	// TODO: �ڴ���������������
	hard=500;
	CmoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UpdateAllViews(NULL);
}


void CmoveView::OnUpdateNormal(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(hard==500||bagin)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CmoveView::OnVeryhard()
{
	// TODO: �ڴ���������������
	hard=100;
	CmoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UpdateAllViews(NULL);
}


void CmoveView::OnUpdateVeryhard(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(hard==100||bagin)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}
Cpoint* CmoveView::getpoint(int n)								//��ȡָ������߶ζ����ָ��
{
	if(n<0||n>pointarray.GetUpperBound())
		return NULL;
	return pointarray.GetAt(n);
}
void CmoveView::addpoint(CPoint p)								//��̬������Ӷ���
{
	Cpoint *p1=new Cpoint(p);
	pointarray.Add(p1);
}
int CmoveView::getnumpoint()									//��ȡ�߶�����
{
	return pointarray.GetSize();
}
void CmoveView::food()
{
	srand((unsigned)time(NULL));
	m_food.x=rand()%20*20+1;
	m_food.y=rand()%20*20+1;
}
void CmoveView::eat()
{
	int n=getnumpoint()-1;
	while(n)
	{
		if(getpoint(n)->m_p.x==m_head.x&&getpoint(n)->m_p.y==m_head.y)
		{
			life=false;
			KillTimer(1);
			break;
		}
		n--;
	}
	if((m_head.x<1||m_head.x>381||m_head.y<1||m_head.y>381)||(m_head.x==m_tail.x&&m_head.y==m_tail.y))
	{
		life=false;
		KillTimer(1);
	}
	else if(m_head.x==m_food.x&&m_head.y==m_food.y)
	{
		score++;
		addpoint(m_tail);
		food();
	}
}
void CmoveView::run()
{
	int n=getnumpoint()-1;
	m_tail=getpoint(n)->m_p;
	while(n>0)
	{
		getpoint(n)->m_p=getpoint(n-1)->m_p;
		n--;
	}
	switch(d)
	{
	case 'L':getpoint(0)->m_p.x-=20;break;
	case 'R':getpoint(0)->m_p.x+=20;break;
	case 'U':getpoint(0)->m_p.y-=20;break;
	case 'D':getpoint(0)->m_p.y+=20;break;
	default:break;
	}
	m_head=getpoint(0)->m_p;
}
void CmoveView::draw()
{
	int n=getnumpoint()-1;
	CClientDC dc(this);
	CPen pen1(PS_SOLID,1,RGB(255,0,0));
	CBrush brush1(RGB(255,0,0));
	dc.SelectObject(&pen1);
	dc.SelectObject(&brush1);
	dc.Ellipse(m_food.x,m_food.y,m_food.x+20,m_food.y+20);
	CString str;
	dc.SetTextColor(RGB(127,255,212));
	str.Format(_T("snake:%d,%d"),m_head.x,m_head.y);
	dc.TextOutW(500,300,str);
	str.Format(_T("food:%d,%d"),m_food.x,m_food.y);
	dc.TextOutW(640,300,str);
	while(n>-1)
	{
		CPen pen2(PS_SOLID,1,RGB(0,0,0));
		CBrush brush2(RGB(0,0,0));
		dc.SelectObject(&pen2);
		dc.SelectObject(&brush2);
		dc.Rectangle(getpoint(n)->m_p.x,getpoint(n)->m_p.y,getpoint(n)->m_p.x+20,getpoint(n)->m_p.y+20);
		n--;
	}
}