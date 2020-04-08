
// HuaRongDaoView.cpp : CHuaRongDaoView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "HuaRongDao.h"
#endif

#include "HuaRongDaoDoc.h"
#include "HuaRongDaoView.h"
#include <mmsystem.h>
#include <Digitalv.h>
#pragma comment( lib, "Winmm.lib" ) 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHuaRongDaoView

IMPLEMENT_DYNCREATE(CHuaRongDaoView, CView)

BEGIN_MESSAGE_MAP(CHuaRongDaoView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHuaRongDaoView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_CREATE()

	ON_BN_CLICKED(IDB_RESTART,ONRESTART)
	ON_BN_CLICKED(IDB_SAVE,ONSAVE)
	ON_BN_CLICKED(IDB_LOAD,ONLOAD)
	ON_BN_CLICKED(IDB_NEXT,ONNEXT)
	ON_BN_CLICKED(IDB_HELP,ONHELP)
	ON_BN_CLICKED(IDB_LEVEL,ONLEVEL)
	ON_BN_CLICKED(IDB_VIDEO,ONVIDEO)
	ON_LBN_SELCHANGE(IDC_LISTLEVEL,OnSelchangeListlevel)
	ON_LBN_SELCHANGE(IDC_LISTVIDEO,OnSelchangeListvideo)
	ON_LBN_DBLCLK(IDC_LISTLEVEL,OnDblclkListlevel)
	ON_LBN_DBLCLK(IDC_LISTVIDEO,OnDblclkListvideo)

	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CHuaRongDaoView ����/����
Person person[15]={{0,_T("01.�ܲ�")},{1,_T("02.�ŷ�-��")},{1,_T("03.�ŷ�-��")},{2,_T("04.����-��")},{2,_T("05.����-��")},
				{3,_T("06.��-��")},{3,_T("07.��-��")},{4,_T("08.����-��")},{4,_T("09.����-��")},{5,_T("10.����-��")},
				{5,_T("11.����-��")},{6,_T("12.��1")},{7,_T("13.��2")},{8,_T("14.��3")},{9,_T("15.��4")}};
CHuaRongDaoView::CHuaRongDaoView()
{
	// TODO: �ڴ˴���ӹ������
	playflag=false;
	successflag=false;				
	makeflag=false;	
	dragflag=false;
	timeflag=false;
	pwndstatic=NULL;
	pwndedit=NULL;
	pwndlevel_list=NULL;				
	pwndvideo_list=NULL;
	m_date1=m_date2=_T("");
}
CHuaRongDaoView::~CHuaRongDaoView()
{
}

BOOL CHuaRongDaoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CHuaRongDaoView ����

void CHuaRongDaoView::OnDraw(CDC* pDC)
{
	CHuaRongDaoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC MemDC;
	CBitmap MemBitmap;
	CRect r;
	GetClientRect(r);
	MemDC.CreateCompatibleDC(NULL); 
	MemBitmap.CreateCompatibleBitmap(pDC,r.right,r.bottom); 
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap); 
	MemDC.FillSolidRect(0,0,r.right,r.bottom,RGB(255,255,255)); 

	draw(&MemDC);

	pDC->BitBlt(0,0,r.right,r.bottom,&MemDC,0,0,SRCCOPY); 
	MemBitmap.DeleteObject(); 
	MemDC.DeleteDC(); 
	
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CHuaRongDaoView ��ӡ


void CHuaRongDaoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHuaRongDaoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CHuaRongDaoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CHuaRongDaoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CHuaRongDaoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CHuaRongDaoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHuaRongDaoView ���

#ifdef _DEBUG
void CHuaRongDaoView::AssertValid() const
{
	CView::AssertValid();
}

void CHuaRongDaoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHuaRongDaoDoc* CHuaRongDaoView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHuaRongDaoDoc)));
	return (CHuaRongDaoDoc*)m_pDocument;
}
#endif //_DEBUG


// CHuaRongDaoView ��Ϣ�������


void CHuaRongDaoView::OnLButtonDown(UINT nFlags, CPoint point)			//�ƶ�
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(makeflag)
	{
		int x=point.x/100-2;
		int y=(point.y+50)/100-1;
		if(x>=0&&x<4&&y>=0&&y<5)											//����������							
		{
			if(!m_chessboard[x][y].empty)									//�㵽����
			{
				m_chessman[m_chessmannumber].m_clickflag=false;
				m_chessmannumber=getchessmannumber(x,y);
				m_chessman[m_chessmannumber].m_clickflag=true;
				b3.EnableWindow();
				dragflag=false;
			}
			else if(m_chessmannumber!=10)										//���ڿ�λ������
			{
				setchess(x,y);	
			}
			reflesh();
		}
	}
	else if(!playflag)				//���ڲ���״̬
	{
		if(pwndstatic!=NULL)
		{
			delete pwndstatic;							//ɾ���ϴ����ɵĿؼ�����
			pwndstatic=NULL;
			b5.EnableWindow();
		}
		if(pwndlevel_list!=NULL)
		{
			delete pwndlevel_list;							//ɾ���ϴ����ɵĿؼ�����
			pwndlevel_list=NULL;
			b6.EnableWindow();
			b1.SetWindowTextW(_T("��ʼ��Ϸ"));
		}
		if(timeflag)
		{
			int x=point.x/100-2;
			int y=(point.y+50)/100-1;
			if(x>=0&&x<4&&y>=0&&y<5)											//����������							
			{
				if(!m_chessboard[x][y].empty)									//�㵽����
				{
					m_chessman[m_chessmannumber].m_clickflag=false;
					m_chessmannumber=getchessmannumber(x,y);
					m_chessman[m_chessmannumber].m_clickflag=true;
				}
				else if(m_chessmannumber!=10)										//���ڿ�λ���ƶ�
				{
					m_d=getderection(x,y);
					if(m_d!='\0')												//��Ч����
					{
						move(m_d);
						m_chessman[m_chessmannumber].move(m_d);

						/***************************************������**********************************/
						m_stepnumber++;
						GetDocument()->addmovement(m_chessmannumber,m_d,m_stepnumber);
						succeed();
					}
				}
				reflesh();
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}
void CHuaRongDaoView::OnRButtonDown(UINT nFlags, CPoint point)			//��
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!playflag&&timeflag)
	{
		if(m_stepnumber)
		{
			m_stepnumber--;
			m_chessman[m_chessmannumber].m_clickflag=false;
			m_chessmannumber=GetDocument()->m_movementarray.GetAt(m_stepnumber)->m_chessmannumber;
			m_chessman[m_chessmannumber].m_clickflag=true;
			m_d=GetDocument()->m_movementarray.GetAt(m_stepnumber)->m_d+32;//תСд
			move(m_d);								
			m_chessman[m_chessmannumber].move(m_d);
	
			/***************************************������**********************************/
			GetDocument()->m_movementarray.RemoveAt(m_stepnumber);
			Invalidate();
		}
	}
	CView::OnRButtonDown(nFlags, point);
}
void CHuaRongDaoView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(makeflag&&m_chessmannumber!=10)						
	{
		if(!m_chessman[m_chessmannumber].m_finishset)
		{
			int w=m_chessman[m_chessmannumber].m_width/200;
			int h=m_chessman[m_chessmannumber].m_height/200;
			int x=point.x/100-2;
			int y=(point.y+50)/100-1;
			if(x>=0&&y>=0&&x+w<4&&y+h<5)								//���ھ�����
			{
				dragflag=true;
				if((m_chessman[m_chessmannumber].m_x!=x)||(m_chessman[m_chessmannumber].m_y!=y))
				{
					m_chessman[m_chessmannumber].m_x=x;
					m_chessman[m_chessmannumber].m_y=y;
					reflesh();
				}
			}
		}
	}
	CView::OnMouseMove(nFlags, point);
}
void CHuaRongDaoView::initselect(int level)
{
	if(level>0)
	{
		load_level(level);
		m_chessmannumber=10;
		m_d='\0';
		m_stepnumber=0;
		m_time=0;
		clearmovement();
	}
	else
	{
		for(int i=0;i<10;i++)
			m_chessman[i].m_finishset=false;
	}
}
void CHuaRongDaoView::draw(CDC *pDC)
{
	/**************************����**************************/
	CPen pen1(PS_SOLID,3,RGB(0,0,0));
	pDC->SelectObject(&pen1);
	CBrush brush1(RGB(255,153,0));
	pDC->SelectObject(&brush1);
	pDC->Rectangle(0,0,800,600);

	CBrush brush2(RGB(0,255,0));
	pDC->SelectObject(&brush2);				
	pDC->Rectangle(200,50,600,550);

	/**************************��ͼ**************************/
	for(int i=0;i<10;i++)
		m_chessman[i].draw(pDC);
	if(dragflag)
		m_chessman[m_chessmannumber].draw(pDC,true);
	/***************************�߿�****************************/
	CPen pen4(PS_SOLID,3,RGB(0,0,255));
	pDC->SelectObject(&pen4);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(200,50,600,550);

	/****************************����*****************************/
	CPen pen3(PS_SOLID,4,RGB(0,255,0));
	pDC->SelectObject(&pen3);
	CBrush brush3(RGB(0,255,0));
	pDC->SelectObject(&brush3);
	pDC->Rectangle(300,550,500,600);


	/****************************����******************************/
	CString str;
	CFont font1;
	font1.CreatePointFont(150,_T("�����п�"));
	pDC->SelectObject(&font1);
	pDC->SetTextColor(RGB(0,0,255));
	pDC->TextOutW(360,10,_T("���ݵ�"));

	/****************************************�ı���1***************************************/
	if(m_levelnumber>0)
	{
		ASSERT((&m_static)&&m_static.GetSafeHwnd());
		CDC *pdc1=m_static.GetDC();          //��ÿؼ�DC
		CFont font2;
		font2.CreatePointFont(120,_T("�����п�"));
		pdc1->SelectObject(&font2);
		pdc1->SetTextColor(RGB(0,255,255));
		pdc1->TextOutW(5,5,_T("�ؿ�:"));
		pdc1->TextOutW(5,80,_T("����:"));
		pdc1->TextOutW(5,130,_T("ʱ��:"));

		CFont font3;
		font3.CreatePointFont(80,_T("����"));
		pdc1->SelectObject(&font3);
		pdc1->SetTextColor(RGB(255,0,255));
		str.Format(_T("%d"),m_level);
		pdc1->TextOutW(5,30,str);
		pdc1->TextOutW(5,55,m_levelname);
		str.Format(_T("%d"),m_stepnumber);
		pdc1->TextOutW(5,105,str);
		if(m_time<60)
			str.Format(_T("%ds"),m_time);
		else
			str.Format(_T("%dmin%ds"),m_time/60,m_time%60);
		pdc1->TextOutW(5,155,str);
		ReleaseDC(pdc1);
	}
	/****************************************�ı���2***************************************/
	if(makeflag)
	{
		if(pwndstatic!=NULL)
		{
			ASSERT(pwndstatic&&pwndstatic->GetSafeHwnd());
			CDC *pdc=pwndstatic->GetDC();          //��ÿؼ�DC
			CFont font2;
			font2.CreatePointFont(120,_T("�����п�"));
			pdc->SelectObject(&font2);
			pdc->SetTextColor(RGB(0,255,255));
			pdc->SetBkColor(pdc->GetBkColor());	//����ɫ
			//pdc->SetBkColor(RGB(255,153,0));
			pdc->TextOutW(5,5,_T("�ؿ�:"));
			pdc->TextOutW(5,55,_T("����:"));
			CFont font3;
			font3.CreatePointFont(80,_T("����"));
			pdc->SelectObject(&font3);
			pdc->SetTextColor(RGB(255,0,255));
			str.Format(_T("%d"),m_levelnumber+1);
			pdc->TextOutW(50,30,str);
			ReleaseDC(pdc);
		}
	}
	else
	{
		if(pwndstatic!=NULL)
		{
			ASSERT(pwndstatic&&pwndstatic->GetSafeHwnd());
			CDC *pdc=pwndstatic->GetDC();          //��ÿؼ�DC
			CFont font2;
			font2.CreatePointFont(120,_T("�����п�"));
			pdc->SelectObject(&font2);
			pdc->SetTextColor(RGB(0,255,255));
			pdc->SetBkColor(pdc->GetBkColor());	//����ɫ
			//pdc->SetBkColor(RGB(255,153,0));
			pdc->TextOutW(5,5,_T("�������:"));
			pdc->TextOutW(5,55,_T("�����Ҽ�:"));
			pdc->TextOutW(5,105,_T("���½���:"));
			CFont font3;
			font3.CreatePointFont(80,_T("����"));
			pdc->SelectObject(&font3);
			pdc->SetTextColor(RGB(255,0,255));
			pdc->TextOutW(50,30,_T("ѡ�ж���"));
			pdc->TextOutW(50,80,_T("��һ��"));
			if(m_date1==_T(""))								//�ޱ������
				pdc->TextOutW(50,130,_T("�ޱ������"));
			else
			{
				pdc->TextOutW(50,130,m_date1);
				pdc->TextOutW(50,155,m_date2);
			}
			ReleaseDC(pdc);
		}
	}
}
void CHuaRongDaoView::reflesh()
{
	Invalidate();						//ʹ�ͻ�����Ч
	CWnd *pWnd=(CWnd*)GetDlgItem(1);
	pWnd->Invalidate();
	pWnd->UpdateWindow();				//ʹ�ı���1����Ч
	if(pwndstatic!=NULL)
	{
		pWnd=(CWnd*)GetDlgItem(2);
		pWnd->Invalidate();
		pWnd->UpdateWindow();				//ʹ�ı���2����Ч
	}
}
int CHuaRongDaoView::getchessmannumber(int x,int y)			//����������
{
	int k;
	for(k=0;k<10;k++)
	{
		if(m_chessman[k].m_finishset)
		{
			int i=m_chessman[k].m_x;
			int j=m_chessman[k].m_y;
			int w=m_chessman[k].m_width/200;
			int h=m_chessman[k].m_height/200;
			if(i==x&&j==y)
				break;
			else if(i+w==x&&j==y)
				break;
			else if(i==x&&j+h==y)
				break;
			else if(i+w==x&&j+h==y)
				break;
		}
	}
	return k;
}
void CHuaRongDaoView::move(char d)
{
	int i=m_chessman[m_chessmannumber].m_x;
	int j=m_chessman[m_chessmannumber].m_y;
	int w=m_chessman[m_chessmannumber].m_width/200;
	int h=m_chessman[m_chessmannumber].m_height/200;
	switch(d)
	{
	case 'L':
	case 'r':	//��
		m_chessboard[i+w][j].empty=m_chessboard[i+w][j+h].empty=true;
		m_chessboard[i-1][j].empty=m_chessboard[i-1][j+h].empty=false;
		break;
	case 'R':
	case 'l':	//��
		m_chessboard[i][j].empty=m_chessboard[i][j+h].empty=true;
		m_chessboard[i+w+1][j].empty=m_chessboard[i+w+1][j+h].empty=false;
		break;
	case 'U':
	case 'd':	//��
		m_chessboard[i][j+h].empty=m_chessboard[i+w][j+h].empty=true;
		m_chessboard[i][j-1].empty=m_chessboard[i+w][j-1].empty=false;
		break;
	case 'D':
	case 'u':	//��
		m_chessboard[i][j].empty=m_chessboard[i+w][j].empty=true;
		m_chessboard[i][j+h+1].empty=m_chessboard[i+w][j+h+1].empty=false;
		break;
	default:break;
	}
}
char CHuaRongDaoView::getderection(int x,int y)				//��÷���
{
	int i=m_chessman[m_chessmannumber].m_x;
	int j=m_chessman[m_chessmannumber].m_y;
	int w=m_chessman[m_chessmannumber].m_width/200;
	int h=m_chessman[m_chessmannumber].m_height/200;
	if(x<i)					//��
	{
		/***************************�ж��Ƿ���ƶ�************************************/
		if(m_chessboard[i-1][j].empty&&m_chessboard[i-1][j+h].empty)
		{
			return 'L';
		}
	}
	else if(x>i&&i+w+1<4)					//��,���ܳ���
	{
		if(m_chessboard[i+w+1][j].empty&&m_chessboard[i+w+1][j+h].empty)
		{
			return 'R';
		}
	}
	if(y<j)					//��
	{
		if(m_chessboard[i][j-1].empty&&m_chessboard[i+w][j-1].empty)
		{
			return 'U';
		}
	}
	else if(y>j&&j+h+1<5)			//��
	{
		if(m_chessboard[i][j+h+1].empty&&m_chessboard[i+w][j+h+1].empty)
		{
			return 'D';
		}
	}
	return '\0';
}
void CHuaRongDaoView::setchess(int x,int y)							//�ڷ�����
{
	int w=m_chessman[m_chessmannumber].m_width/200;
	int h=m_chessman[m_chessmannumber].m_height/200;
	if(m_chessboard[x][y].empty&&m_chessboard[x+w][y].empty&&m_chessboard[x][y+h].empty&&m_chessboard[x+w][y+h].empty)		//�ɷ�
	{
		dragflag=false;
		if(m_chessman[m_chessmannumber].m_finishset)
		{
			int i=m_chessman[m_chessmannumber].m_x;
			int j=m_chessman[m_chessmannumber].m_y;
			m_chessboard[i][j].empty=m_chessboard[i+w][j].empty=m_chessboard[i][j+h].empty=m_chessboard[i+w][j+h].empty=true;
		}
		else
		{
			int n=pwndlevel_list->GetCount();
			for(int i=0;i<15;i++)
			{
				if(person[i].m_chessmannumber==m_chessmannumber)
				{
					CString str;
					int j;
					for(j=0;j<n;j++)
					{
						pwndlevel_list->GetText(j,str);
						if(person[i].m_name==str)
							break;
					}
					if(j<n)
						pwndlevel_list->DeleteString(j);
				}
			}
		}
		m_chessman[m_chessmannumber].m_x=x;
		m_chessman[m_chessmannumber].m_y=y;
		m_chessman[m_chessmannumber].m_finishset=true;
		m_chessman[m_chessmannumber].m_clickflag=true;
		b3.EnableWindow();
		m_chessboard[x][y].empty=m_chessboard[x+w][y].empty=m_chessboard[x][y+h].empty=m_chessboard[x+w][y+h].empty=false;
		Ismakefinish();
	}
}
void CHuaRongDaoView::succeed()								//�ж��Ƿ����
{
	if(m_chessman[0].m_x==1&&m_chessman[0].m_y==3)
	{
		KillTimer(1);
		timeflag=false;
		//PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(),SND_RESOURCE|SND_ASYNC); 
		successflag=true;
		b2.SetWindowTextW(_T("�ⷨ�ղ�"));
		b4.SetWindowTextW(_T("��һ��"));
		if(m_level<14)
			b4.EnableWindow();
	}
}
BOOL CHuaRongDaoView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return true;
	//return CView::OnEraseBkgnd(pDC);
}
void CHuaRongDaoView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(playflag)
	{
		int n=GetDocument()->m_movementarray.GetSize();
		m_time++;
		m_stepnumber++;
		m_chessmannumber=GetDocument()->m_movementarray.GetAt(m_time-1)->m_chessmannumber;
		m_d=GetDocument()->m_movementarray.GetAt(m_time-1)->m_d;
		move(m_d);
		m_chessman[m_chessmannumber].move(m_d);
		for(int i=0;i<10;i++)
			m_chessman[i].m_clickflag=false;
		m_chessman[m_chessmannumber].m_clickflag=true;
		if(m_stepnumber==n)
		{
			Timer(3);
			b2.EnableWindow(false);
			b3.EnableWindow(false);
		}
		reflesh();
	}
	else
	{
		m_time++;
		reflesh();
	}
	CView::OnTimer(nIDEvent);
}
int CHuaRongDaoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	/**************************************����*************************************/
	CRect rect_button1(700,50,780,80);
	b1.Create(_T("��ʼ��Ϸ"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button1,this,IDB_RESTART);
	b1.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button2(700,110,780,140);
	b2.Create(_T("�������"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button2,this,IDB_SAVE);
	b2.ShowWindow(SW_SHOWNORMAL);
	

	CRect rect_button3(700,170,780,200);
	b3.Create(_T("�������"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button3,this,IDB_LOAD);
	b3.ShowWindow(SW_SHOWNORMAL);
	Iscanload();
	
	CRect rect_button4(700,230,780,260);
	b4.Create(_T("���ƹؿ�"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button4,this,IDB_NEXT);
	b4.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button5(20,50,100,80);
	b5.Create(_T("����"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button5,this,IDB_HELP);
	b5.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button6(700,300,780,330);
	b6.Create(_T("ѡ��ؿ�"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button6,this,IDB_LEVEL);
	b6.ShowWindow(SW_SHOWNORMAL);

	CRect rect_button7(20,300,100,330);
	b7.Create(_T("�ⷨ"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button7,this,IDB_VIDEO);
	b7.ShowWindow(SW_SHOWNORMAL);

	m_static.Create(_T(""),WS_CHILD|SS_WHITERECT|WS_VISIBLE|WS_BORDER,CRect(610,90,690,290),this,1);

	load_level_solution();
	if(m_levelnumber>0)
	{
		m_static.ShowWindow(SW_SHOWNORMAL);
		initselect(1);
	}
	else
	{
		m_static.ShowWindow(SW_HIDE);
		initselect(0);
	}
	// TODO:  �ڴ������ר�õĴ�������
	return 0;
}
void CHuaRongDaoView::ONRESTART() 
{
	if(playflag)
	{
		Timer(3);
		b2.EnableWindow(false);
		b3.EnableWindow();
		initselect(m_level);
		load_solution(m_level);
		Timer(1);
		reflesh();
	}
	else if(makeflag)
	{
		m_levelnumber++;
		m_level=m_levelnumber;
		pwndedit->GetWindowText(m_levelname);
		save_level(m_level);
		makeflag=false;
		b1.SetWindowTextW(_T("��ʼ��Ϸ"));
		b2.SetWindowTextW(_T("�������"));
		b3.SetWindowTextW(_T("�������"));
		b6.SetWindowTextW(_T("ѡ��ؿ�"));
		b1.EnableWindow();
		b2.EnableWindow();
		Iscanload();
		b4.EnableWindow();
		b5.ShowWindow(SW_SHOWNORMAL);
		b7.ShowWindow(SW_SHOWNORMAL);
		m_static.ShowWindow(SW_SHOWNORMAL);
		if(pwndlevel_list!=NULL)
		{
			delete pwndlevel_list;							//ɾ���ϴ����ɵĿؼ�����
			pwndlevel_list=NULL;
			b6.EnableWindow();
		}
		if(pwndedit!=NULL)
		{
			delete pwndedit;							//ɾ���ϴ����ɵĿؼ�����
			pwndedit=NULL;
		}
		if(pwndstatic!=NULL)
		{
			delete pwndstatic;							//ɾ���ϴ����ɵĿؼ�����
			pwndstatic=NULL;
		}
		initselect(m_level);
		reflesh();
	}
	else if(successflag)
	{
		b2.SetWindowTextW(_T("�������"));
		b2.EnableWindow();
		b4.SetWindowTextW(_T("���ƹؿ�"));
		successflag=false;
		initselect(m_level);
		clearmovement();
		Timer(1);
		reflesh();
	}
	else
	{
		if(!timeflag)
		{
			b1.SetWindowTextW(_T("���¿�ʼ"));
			Timer(1);
		}
		else
		{
			Timer(3);
			b2.SetWindowTextW(_T("�������"));
			b2.EnableWindow();
			initselect(m_level);
			clearmovement();
			Timer(1);
		}
		reflesh();
	}
}
void CHuaRongDaoView::ONSAVE()
{
	if(playflag)					//����		
	{
		if(pwndvideo_list!=NULL)
		{
			delete pwndvideo_list;
			pwndvideo_list=NULL;
			b7.EnableWindow();

			load_solution(m_level);
			Iscannext();
		}
		b1.EnableWindow();
		b2.EnableWindow(false);
		b3.EnableWindow();
		Timer(1);
	}		
	else if(makeflag)				//�˳�
	{
		makeflag=false;
		dragflag=false;
		b1.SetWindowTextW(_T("��ʼ��Ϸ"));
		b2.SetWindowTextW(_T("�������"));
		b3.SetWindowTextW(_T("�������"));
		b6.SetWindowTextW(_T("ѡ��ؿ�"));
		b1.EnableWindow();
		b2.EnableWindow();
		Iscanload();
		b4.EnableWindow();
		b5.ShowWindow(SW_SHOWNORMAL);
		b7.ShowWindow(SW_SHOWNORMAL);
		m_static.ShowWindow(SW_SHOWNORMAL);
		if(pwndlevel_list!=NULL)
		{
			delete pwndlevel_list;							//ɾ���ϴ����ɵĿؼ�����
			pwndlevel_list=NULL;
			b6.EnableWindow();
		}
		if(pwndedit!=NULL)
		{
			delete pwndedit;								//ɾ���ϴ����ɵĿؼ�����
			pwndedit=NULL;
		}
		if(pwndstatic!=NULL)
		{
			delete pwndstatic;								//ɾ���ϴ����ɵĿؼ�����
			pwndstatic=NULL;
		}
		initselect(m_level);
		reflesh();
	}
	else if(successflag)									//�ⷨ�ղ�
	{
		int j;
		for(j=0;j<m_solutionnumber;j++)
			if(psolution[j]==m_level)
				break;
		if(j==m_solutionnumber)
		{
			m_solutionnumber++;
			int *p=new int[m_solutionnumber];
			int i;
			for(i=0;i<m_solutionnumber-1;i++)
				p[i]=psolution[i];
			p[i]=m_level;
			delete [] psolution;
			psolution=NULL;
			psolution=new int[m_solutionnumber];
			for(i=0;i<m_solutionnumber;i++)
				psolution[i]=p[i];
			delete [] p;
		}
		save_solution(m_level);
		b2.EnableWindow(false);
	}
	else
	{
		save();
		b3.EnableWindow();
	}
}
void CHuaRongDaoView::ONLOAD()
{
	if(playflag)
	{
		Timer(2);
		b2.EnableWindow();
		b3.EnableWindow(false);
		reflesh();
	}
	else if(makeflag)
	{
		int x=m_chessman[m_chessmannumber].m_x;
		int y=m_chessman[m_chessmannumber].m_y;
		int w=m_chessman[m_chessmannumber].m_width/200;
		int h=m_chessman[m_chessmannumber].m_height/200;
		m_chessman[m_chessmannumber].m_finishset=false;
		m_chessman[m_chessmannumber].m_clickflag=false;
		b3.EnableWindow(false);
		m_chessboard[x][y].empty=m_chessboard[x+w][y].empty=m_chessboard[x][y+h].empty=m_chessboard[x+w][y+h].empty=true;
		for(int i=0;i<15;i++)
			if(person[i].m_chessmannumber==m_chessmannumber)
				pwndlevel_list->AddString(person[i].m_name);
		m_chessmannumber=10;
		Ismakefinish();
		reflesh();
	}
	else
	{
		Timer(3);
		load();
		b1.SetWindowTextW(_T("���¿�ʼ"));
		Timer(1);
		reflesh();
	}
}
void CHuaRongDaoView::ONNEXT()
{
	if(playflag)
	{
		m_level=Iscannext();
		Timer(3);
		b1.EnableWindow(false);
		b2.EnableWindow();
		b3.EnableWindow(false);
		Iscannext();
		initselect(m_level);
		load_solution(m_level);
		reflesh();
	}
	else if(successflag)
	{
		successflag=false;
		b1.SetWindowTextW(_T("��ʼ��Ϸ"));
		b2.SetWindowTextW(_T("�������"));
		b2.EnableWindow();
		b4.SetWindowTextW(_T("���ƹؿ�"));
		m_level++;
		initselect(m_level);
		reflesh();
	}
	else
	{
		Timer(3);
		makeflag=true;
		m_chessmannumber=10;
		b1.SetWindowTextW(_T("ȷ��"));
		b2.SetWindowTextW(_T("�˳�"));
		b3.SetWindowTextW(_T("ɾ������"));
		b6.SetWindowTextW(_T("ѡ������"));
		b1.EnableWindow(false);
		b3.EnableWindow(false);
		b4.EnableWindow(false);
		b5.ShowWindow(SW_HIDE);
		b7.ShowWindow(SW_HIDE);
		for(int i=0;i<10;i++)
			m_chessman[i].m_finishset=false;	
		for(int i=0;i<4;i++)
			for(int j=0;j<5;j++)
				m_chessboard[i][j].empty=true;
		if(pwndlevel_list!=NULL)
		{
			delete pwndlevel_list;							//ɾ���ϴ����ɵĿؼ�����
			pwndlevel_list=NULL;
			b6.EnableWindow();
		}
		if(pwndstatic!=NULL)
		{
			delete pwndstatic;								//ɾ���ϴ����ɵĿؼ�����
			pwndstatic=NULL;
			b5.EnableWindow();
		}
		pwndstatic=new CStatic;
		pwndstatic->Create(_T(""),WS_CHILD|SS_WHITERECT|WS_VISIBLE|WS_BORDER,CRect(20,90,180,170),this,2);
		pwndedit=new CEdit;
		pwndedit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER,CRect(20,170,180,200),this,IDC_EDIT);
		m_static.ShowWindow(SW_HIDE);
		reflesh();
	}
}
void CHuaRongDaoView::ONHELP()
{
	pwndstatic=new CStatic;
	((CStatic*)pwndstatic)->Create(_T(""),WS_CHILD|SS_WHITERECT|WS_VISIBLE|WS_BORDER,CRect(20,90,180,290),this,2);
	b5.EnableWindow(false);
	reflesh();
}
void CHuaRongDaoView::ONLEVEL()
{
	if(playflag)			//�˳�
	{
		Timer(3);
		b1.SetWindowTextW(_T("��ʼ��Ϸ"));
		b2.SetWindowTextW(_T("�������"));
		b3.SetWindowTextW(_T("�������"));
		b4.SetWindowTextW(_T("���ƹؿ�"));
		b6.SetWindowTextW(_T("ѡ��ؿ�"));
		b1.EnableWindow();
		b2.EnableWindow();
		Iscanload();
		b4.EnableWindow();
		b5.ShowWindow(SW_SHOWNORMAL);
		if(pwndvideo_list!=NULL)
		{
			delete pwndvideo_list;							//ɾ���ϴ����ɵĿؼ�����
			pwndvideo_list=NULL;
			b7.EnableWindow();
		}
		playflag=false;
		initselect(m_level);
		reflesh();
	}
	else if(makeflag)
	{
		pwndlevel_list=new CListBox;
		pwndlevel_list->Create(WS_CHILD|WS_VISIBLE|LBS_STANDARD,CRect(610,340,780,550),this,IDC_LISTLEVEL);
		for(int i=0;i<15;i++)
			pwndlevel_list->AddString(person[i].m_name);
		b6.EnableWindow(false);
		reflesh();
	}
	else
	{
		Timer(3);
		pwndlevel_list=new CListBox;
		pwndlevel_list->Create(WS_CHILD|WS_VISIBLE|LBS_STANDARD,CRect(610,340,780,550),this,IDC_LISTLEVEL);
		CString str;
		for(int i=1;i<=m_levelnumber;i++)
		{
			str.Format(_T("%d%d"),i/10,i%10);
			pwndlevel_list->AddString(str);
		}
		b6.EnableWindow(false);
		reflesh();
	}
}
void CHuaRongDaoView::ONVIDEO()
{
	Timer(3);
	pwndvideo_list=new CListBox;
	((CListBox*)pwndvideo_list)->Create(WS_CHILD|WS_VISIBLE|LBS_STANDARD,CRect(20,340,180,550),this,IDC_LISTVIDEO);
	CString str;
	for(int i=0;i<m_solutionnumber;i++)
	{
		str.Format(_T("%d%d"),psolution[i]/10,psolution[i]%10);
		pwndvideo_list->AddString(str);
	}
	if(!playflag)
	{
		b1.SetWindowTextW(_T("���²���"));
		b2.SetWindowTextW(_T("����"));
		b3.SetWindowTextW(_T("��ͣ"));
		b4.SetWindowTextW(_T("��һ��"));
		b6.SetWindowTextW(_T("�˳�"));
		playflag=true;
		b5.ShowWindow(SW_HIDE);
		if(pwndlevel_list!=NULL)
		{
			delete pwndlevel_list;							//ɾ���ϴ����ɵĿؼ�����
			pwndlevel_list=NULL;
			b6.EnableWindow();
		}
		if(pwndstatic!=NULL)
		{
			delete pwndstatic;							//ɾ���ϴ����ɵĿؼ�����
			pwndstatic=NULL;
			b5.EnableWindow();
		}
	}
	b1.EnableWindow(false);
	b2.EnableWindow();
	b3.EnableWindow(false);
	b4.EnableWindow(false);
	b7.EnableWindow(false);
	initselect(m_level);
	reflesh();
}
void CHuaRongDaoView::OnSelchangeListlevel()
{
	if(makeflag)
	{
		int n=pwndlevel_list->GetCurSel();
		if(n!=-1)
		{
			CString str;
			pwndlevel_list->GetText(n,str);
			int pos=str.Find('.');
			CString temp=str.Left(pos);
			int m=_ttoi(temp);
			if(m_chessmannumber!=10)
			{
				m_chessman[m_chessmannumber].m_clickflag=false;
				b3.EnableWindow(false);
			}
			switch(m)
			{
			case 1:m_chessmannumber=0;m_chessman[m_chessmannumber].set(200,200,Caocao);break;
			case 2:m_chessmannumber=1;m_chessman[m_chessmannumber].set(100,200,Zhangfei);break;
			case 3:m_chessmannumber=1;m_chessman[m_chessmannumber].set(200,100,Zhangfei1);break;
			case 4:m_chessmannumber=2;m_chessman[m_chessmannumber].set(100,200,Zhaoyun);break;
			case 5:m_chessmannumber=2;m_chessman[m_chessmannumber].set(200,100,Zhaoyun1);break;
			case 6:m_chessmannumber=3;m_chessman[m_chessmannumber].set(100,200,Machao);break;
			case 7:m_chessmannumber=3;m_chessman[m_chessmannumber].set(200,100,Machao1);break;
			case 8:m_chessmannumber=4;m_chessman[m_chessmannumber].set(100,200,Huangzhong);break;
			case 9:m_chessmannumber=4;m_chessman[m_chessmannumber].set(200,100,Huangzhong1);break;
			case 10:m_chessmannumber=5;m_chessman[m_chessmannumber].set(200,100,Guanyu);break;
			case 11:m_chessmannumber=5;m_chessman[m_chessmannumber].set(100,200,Guanyu1);break;
			case 12:m_chessmannumber=6;m_chessman[m_chessmannumber].set(100,100,Zu);break;
			case 13:m_chessmannumber=7;m_chessman[m_chessmannumber].set(100,100,Zu);break;
			case 14:m_chessmannumber=8;m_chessman[m_chessmannumber].set(100,100,Zu);break;
			case 15:m_chessmannumber=9;m_chessman[m_chessmannumber].set(100,100,Zu);break;
			default:break;
			}
			dragflag=false;
			m_chessman[m_chessmannumber].m_finishset=false;
			reflesh();
		}
		else
			MessageBox(_T("û��ѡ���б�����б�����ʧ��"));
	}
	else
	{
		int n=pwndlevel_list->GetCurSel();
		if(n!=-1)
		{
			m_level=n+1;
			initselect(m_level);
			reflesh();
		}
		else
			MessageBox(_T("û��ѡ���б�����б�����ʧ��"));
	}
}
void CHuaRongDaoView::OnSelchangeListvideo()
{
	int n=pwndvideo_list->GetCurSel();
	if(n!=-1)
	{
		m_level=psolution[n];
		initselect(m_level);
		reflesh();
	}
	else
		MessageBox(_T("û��ѡ���б�����б�����ʧ��"));
}
void CHuaRongDaoView::OnDblclkListlevel()
{
	if((!playflag)&&(!makeflag))
	{
		delete pwndlevel_list;							//ɾ���ϴ����ɵĿؼ�����
		pwndlevel_list=NULL;
		b6.EnableWindow();
		b1.SetWindowTextW(_T("��ʼ��Ϸ"));
		reflesh();
	}
}
void CHuaRongDaoView::OnDblclkListvideo()
{
	delete pwndvideo_list;							//ɾ���ϴ����ɵĿؼ�����
	pwndvideo_list=NULL;
	b7.EnableWindow();
	
	b1.EnableWindow();
	b2.EnableWindow(false);
	b3.EnableWindow();
	Iscannext();
	load_solution(m_level);
	Timer(1);
	reflesh();
}
void CHuaRongDaoView::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		/******************************************************��ȡʱ��****************************************************************/
		SYSTEMTIME st;
		GetLocalTime(&st);
		m_date1.Format(_T("%4d-%2d-%2d"),st.wYear,st.wMonth,st.wDay);
		m_date2.Format(_T("%2d:%2d:%2d"),st.wHour,st.wMinute,st.wSecond);
		ar<<m_date1<<m_date2;
		/***************************************CMovement***************************************/
		int n=GetDocument()->m_movementarray.GetSize();
		ar<<n;
		CMovement *pmovement=NULL;
		for(int i=0;i<n;i++)
		{
			pmovement=GetDocument()->m_movementarray.GetAt(i);	
			ar<<pmovement->m_chessmannumber<<pmovement->m_d<<pmovement->m_stepnumber;								//���ļ�
		}
		
		/***************************************CChessman***************************************/
		for(int i=0;i<10;i++)
			ar<<m_chessman[i].m_x<<m_chessman[i].m_y<<m_chessman[i].m_width<<m_chessman[i].m_height<<m_chessman[i].m_name<<m_chessman[i].m_clickflag<<m_chessman[i].m_finishset;
		/***************************************CChessboard***************************************/
		for(int i=0;i<4;i++)
			for(int j=0;j<5;j++)
				ar<<m_chessboard[i][j].empty;

		/***************************************����***************************************/
		ar<<m_chessmannumber<<m_d<<m_stepnumber<<m_level<<m_time;
	}
	else
	{
		ar>>m_date1>>m_date2;
		int n=clearmovement();
		ar>>n;
		for(int i=0;i<n;i++)
		{
			CMovement *pmovement=new CMovement;
			ar>>pmovement->m_chessmannumber>>pmovement->m_d>>pmovement->m_stepnumber;							//���ļ�
			GetDocument()->m_movementarray.Add(pmovement);
		}
		for(int i=0;i<10;i++)
			ar>>m_chessman[i].m_x>>m_chessman[i].m_y>>m_chessman[i].m_width>>m_chessman[i].m_height>>m_chessman[i].m_name>>m_chessman[i].m_clickflag>>m_chessman[i].m_finishset;
		for(int i=0;i<4;i++)
			for(int j=0;j<5;j++)
				ar>>m_chessboard[i][j].empty;
		ar>>m_chessmannumber>>m_d>>m_stepnumber>>m_level>>m_time;
	}
}
void CHuaRongDaoView::load()
{
	CFile file;
	if(file.Open(_T(".\\file1.txt"),CFile::modeRead))
	{
		CArchive ar(&file,CArchive::load);
		Serialize(ar);
		ar.Close();
		file.Close();
	}
}
void CHuaRongDaoView::save()
{
	CFile file;
	if(file.Open(_T(".\\file1.txt"),CFile::modeCreate|CFile::modeWrite))
	{
		CArchive ar(&file,CArchive::store);
		Serialize(ar);
		ar.Close();
		file.Close();
	}
}
void CHuaRongDaoView::save_solution(int level)
{
	CFile file;
	solutionfilename.Format(_T("solution%d.txt"),level);
	if(file.Open(solutionfilename,CFile::modeCreate|CFile::modeWrite))
	{
		CArchive ar(&file,CArchive::store);
		int n=GetDocument()->m_movementarray.GetSize();
		ar<<n;
		CMovement *pmovement=NULL;
		for(int i=0;i<n;i++)
		{
			pmovement=GetDocument()->m_movementarray.GetAt(i);	
			ar<<pmovement->m_chessmannumber<<pmovement->m_d<<pmovement->m_stepnumber;								//���ļ�
		}
		ar.Close();
		file.Close();
	}
}
void CHuaRongDaoView::load_solution(int level)
{
	CFile file;
	solutionfilename.Format(_T("solution%d.txt"),level);
	if(file.Open(solutionfilename,CFile::modeRead))
	{
		CArchive ar(&file,CArchive::load);
		int n=clearmovement();
		ar>>n;
		for(int i=0;i<n;i++)
		{
			CMovement *pmovement=new CMovement;
			ar>>pmovement->m_chessmannumber>>pmovement->m_d>>pmovement->m_stepnumber;							//���ļ�
			GetDocument()->m_movementarray.Add(pmovement);
		}
		ar.Close();
		file.Close();
	}
}
void  CHuaRongDaoView::save_level(int level)
{
	CFile file;
	levelfilename.Format(_T("level%d.txt"),level);
	if(file.Open(levelfilename,CFile::modeCreate|CFile::modeWrite))
	{
		CArchive ar(&file,CArchive::store);
		ar<<m_level<<m_levelname;
		for(int i=0;i<10;i++)
			ar<<m_chessman[i].m_x<<m_chessman[i].m_y<<m_chessman[i].m_width<<m_chessman[i].m_height<<m_chessman[i].m_name;
		for(int i=0;i<4;i++)
			for(int j=0;j<5;j++)
				ar<<m_chessboard[i][j].empty;
		ar.Close();
		file.Close();
	}
}
void  CHuaRongDaoView::load_level(int level)	
{
	CFile file;
	levelfilename.Format(_T("level%d.txt"),level);
	if(file.Open(levelfilename,CFile::modeRead))
	{
		CArchive ar(&file,CArchive::load);
		ar>>m_level>>m_levelname;
		for(int i=0;i<10;i++)
		{
			ar>>m_chessman[i].m_x>>m_chessman[i].m_y>>m_chessman[i].m_width>>m_chessman[i].m_height>>m_chessman[i].m_name;
			m_chessman[i].m_clickflag=false;
			m_chessman[i].m_finishset=true;
		}
		for(int i=0;i<4;i++)
			for(int j=0;j<5;j++)
				ar>>m_chessboard[i][j].empty;
		ar.Close();
		file.Close();
	}
}
void CHuaRongDaoView::save_level_solution()
{
	CFile file;
	if(file.Open(_T(".\\level_solution.txt"),CFile::modeCreate|CFile::modeWrite))
	{
		CArchive ar(&file,CArchive::store);
		ar<<m_levelnumber<<m_solutionnumber;
		for(int i=0;i<m_solutionnumber;i++)
			ar<<psolution[i];
		delete [] psolution;
		ar.Close();
		file.Close();
	}
}
void CHuaRongDaoView::load_level_solution()
{
	CFile file;
	if(file.Open(_T(".\\level_solution.txt"),CFile::modeRead|CFile::modeCreate|CFile::modeNoTruncate))
	{
		CFileStatus status;  
		file.GetStatus(_T(".\\level_solution.txt"),status);
		long lSizeOfFile;  
		lSizeOfFile=status.m_size; 
		if(lSizeOfFile)						//�ǿ��ļ�
		{
			CArchive ar(&file,CArchive::load);
			ar>>m_levelnumber>>m_solutionnumber;
			psolution=new int[m_solutionnumber];
			for(int i=0;i<m_solutionnumber;i++)
				ar>>psolution[i];
			ar.Close();
		}
		else
		{
			m_levelnumber=0;
			m_solutionnumber=0;
			psolution=NULL;
		}
		file.Close();
	}
}
void CHuaRongDaoView::Iscanload()
{
	CFile file;
	if(file.Open(_T("file1.txt"),CFile::modeRead|CFile::modeCreate|CFile::modeNoTruncate))
	{
		CFileStatus status;  
		file.GetStatus(_T("file1.txt"),status);
		long lSizeOfFile;  
		lSizeOfFile=status.m_size; 
		if(lSizeOfFile)						//�ǿ��ļ�
		{
			CArchive ar(&file,CArchive::load);
			ar>>m_date1>>m_date2;
			ar.Close();
			file.Close();
			b3.EnableWindow();
		}
		else
		{
			file.Close();
			b3.EnableWindow(false);
		}
	}
}
int CHuaRongDaoView::Iscannext()
{
	int i;
	for(i=0;i<m_solutionnumber;i++)
		if(psolution[i]==m_level)
			break;
	if(i<m_solutionnumber-1)
		b4.EnableWindow();
	else
		b4.EnableWindow(false);
	return psolution[i+1];
}
void CHuaRongDaoView::Ismakefinish()
{
	int i;
	for(i=0;i<10;i++)
	{
		if(!m_chessman[i].m_finishset)
			break;
	}
	if(i==10)				//�������
		b1.EnableWindow();
	else
		b1.EnableWindow(false);
}
void CHuaRongDaoView::OnDestroy()
{
	CView::OnDestroy();
	clearmovement();
	save_level_solution();
	// TODO: �ڴ˴������Ϣ����������
}
int CHuaRongDaoView::clearmovement()
{
	int n=GetDocument()->m_movementarray.GetSize();
	for(int i=0;i<n;i++)
		delete GetDocument()->m_movementarray.GetAt(i);
	GetDocument()->m_movementarray.RemoveAll();
	return n;
}
void CHuaRongDaoView::Timer(int n)
{
	switch(n)
	{
	case 1:
		if(!timeflag)//����
		{
			SetTimer(1,1000,NULL);
			timeflag=true;
		}
		break;
	case 2:
		if(timeflag)//��ͣ
		{
			KillTimer(1);
			timeflag=false;
		}
		break;
	case 3:
		if(timeflag)//�˳�
		{
			KillTimer(1);
			timeflag=false;
		}
		break;
	default:break;
	}
}