// STYView.cpp : implementation of the CSTYView class
//

#include "stdafx.h"
#include "STY.h"

#include "STYDoc.h"
#include "STYView.h"
#include "math.h"
#include "time.h"
#include<mmsystem.h>
#include<stdlib.h>

#pragma comment(lib, "winmm.lib");
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define N 100
/////////////////////////////////////////////////////////////////////////////
// CSTYView

IMPLEMENT_DYNCREATE(CSTYView, CView)

BEGIN_MESSAGE_MAP(CSTYView, CView)
//{{AFX_MSG_MAP(CSTYView)
ON_WM_CREATE()
ON_WM_TIMER()
ON_WM_KEYDOWN()
ON_WM_SIZE()
ON_COMMAND(ID_GAMERESTART, OnGamerestart)
/*ON_COMMAND(ID_FIRST, OnFirst)
ON_COMMAND(ID_MIDDLE, OnMiddle)
ON_COMMAND(ID_TOP, OnTop)*/



//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTYView construction/destruction


//透明函数
void TransparentBlt2( HDC hdc0,	
					 int nX0,int nY0,
					 int nW0,int nH0,
					 HDC hdc1,
					 int nX1,int nY1,
					 int nW1,int nH1,
					 UINT Tcol
					 );


CSTYView::CSTYView()
{
	// TODO: add construction code here
	for (int i = 0; i < N; i++)
	{
		bullet[i].alive = false;		
	}
	count = 0;
	time_1 = time(NULL);
	
}

CSTYView::~CSTYView()
{
}

BOOL CSTYView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSTYView drawing

void CSTYView::OnDraw(CDC* pDC)
{
	CSTYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//添加背景
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	dcMem.SelectObject(&bmpGround);
	//pDC->StretchBlt(0, 0, wrect.right, wrect.bottom, &dcMem, 0, 0, 640, 480,SRCCOPY);
	dcBack.StretchBlt(0, 0, wrect.right, wrect.bottom, &dcMem, 0, 0, 640, 480,SRCCOPY);
	
	dcMem.SelectObject(&bmpHero);
	//TransparentBlt2(pDC->m_hDC, hero.x - 22, hero.y - 44, 44, 44, dcMem, 0, 0, 44, 44, RGB(255, 255, 255));
	TransparentBlt2(dcBack.m_hDC, hero.x - 22, hero.y - 44, 44, 44, dcMem, 0, 0, 44, 44, RGB(255, 255, 255));
	
	
	//画子弹
	for (int i = 0; i < N; i++)
	{
		if (bullet[i].alive)
		{
			//pDC->Ellipse(int(bullet[i].pos[0]) - 5, int(bullet[i].pos[1] - 5), int(bullet[i].pos[0]) + 5, int(bullet[i].pos[1]) + 5);
			
			dcBack.Ellipse(int(bullet[i].pos[0]) - 5, int(bullet[i].pos[1] - 5), int(bullet[i].pos[0]) + 5, int(bullet[i].pos[1]) + 5);
			/*int a = rand() + i;
			int b = rand() + i;
			int c = rand() + i;*/
			bullet[i].m_color = RGB(123, 32, 145);
			CBrush brush;
			brush.CreateSolidBrush(bullet[i].m_color);
			dcBack.SelectObject(&brush);
			
			
		}
	}
	
	pDC->BitBlt(0, 0, wrect.right, wrect.bottom, &dcBack, 0, 0, SRCCOPY);
	
}

/////////////////////////////////////////////////////////////////////////////
// CSTYView printing

BOOL CSTYView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSTYView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSTYView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSTYView diagnostics

#ifdef _DEBUG
void CSTYView::AssertValid() const
{
	CView::AssertValid();
}

void CSTYView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSTYDoc* CSTYView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSTYDoc)));
	return (CSTYDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSTYView message handlers


int CSTYView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	SetTimer(1, 30, NULL);
	bmpHero.LoadBitmap(IDB_HERO);
	HBITMAP hg = (HBITMAP)::LoadImage(NULL, "ground.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpGround.Attach(hg);
	//	return 0;
	mciSendString("OPEN background.mp3 ALIAS BACKGROUND", NULL, 0, NULL);
	mciSendString("PLAY BACKGROUND FROM 0 REPEAT", NULL, 0, NULL);
	mciSendString("OPEN shoot.mp3 ALIAS SHOOT", NULL, 0, NULL);
	mciSendString("PLAY SHOOT FROM 0 REPEAT", NULL, 0, NULL);
	mciSendString("OPEN win.mp3 ALIAS WIN", NULL, 0, NULL);
	return 0;
}



void CSTYView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	count++;
	//子弹向前飞
	for (int i = 0; i < N; i++)
	{
		if (bullet[i].alive)
		{
			bullet[i].pos[0] = bullet[i].pos[0] + 5 * bullet[i].dir[0];
			bullet[i].pos[1] = bullet[i].pos[1] + 5 * bullet[i].dir[1];
		}
	}
	
	for (i = 0; i < N; i++)
	{
		if (!bullet[i].alive)
		{
			bullet[i].alive = true;
			int rnd = rand();
			if (rnd % 6 == 0)
			{
				bullet[i].pos[0] = 0;
				bullet[i].pos[1] = 0;
			}
			else if (rnd % 6 == 1)
			{
				bullet[i].pos[0] = wrect.right / 2;
				bullet[i].pos[1] = 0;
			}
			else if (rnd % 6 == 2)
			{
				bullet[i].pos[0] = wrect.right;
				bullet[i].pos[1] = 0;
			}
			else if (rnd % 6 == 3)
			{
				bullet[i].pos[0] = 0;
				bullet[i].pos[1] = wrect.bottom / 2;
			}
			else if (rnd % 6 == 4)
			{
				bullet[i].pos[0] = wrect.right;
				bullet[i].pos[1] = wrect.bottom / 2;
			}
			else if (rnd % 6 == 5)
			{
				bullet[i].pos[0] = wrect.right / 3;
				bullet[i].pos[1] = 0;
			}
			float dx = (float)hero.x - bullet[i].pos[0];
			float dy = (float)hero.y - bullet[i].pos[1];
			float len = (float)sqrt(dx * dx + dy * dy);
			bullet[i].dir[0] = dx /len;
			bullet[i].dir[1] = dy / len;
			break;
			
		}
	}
	
	
	for (i = 0; i < N; i++)
	{
		int temp = 7;
		//判断打中
		if (bullet[i].pos[0] < hero.x + temp && bullet[i].pos[0] > hero.x - temp && bullet[i].pos[1] < hero.y + temp && bullet[i].pos[1] > hero.y - temp)
		{
			time_2 = time(NULL);
			time_t temp = time_2 - time_1;
			char s[10];
			KillTimer(1);
			sprintf(s, "坚持时间为%d秒", temp);
			mciSendString("STOP BACKGROUND", NULL, 0, NULL);
			mciSendString("STOP SHOOT", NULL, 0, NULL);
        	mciSendString("PLAY WIN FROM 0 REPEAT", NULL, 0, NULL);
			if(MessageBox(s)==MB_OK)
			{
				hero.x = wrect.right/2;
				hero.y = wrect.bottom;
				for(int i=0; i<N; i++)
					bullet[i].alive = false;
				SetTimer(1, 30, NULL);
				
				return ;
			}
			//for (int j = 0; j < 1000000000; j++);
			//exit(NULL);
			
		}
		if (bullet[i].alive && bullet[i].pos[1] > wrect.bottom)
		{
			bullet[i].alive = false;
		}
	}
	
	Invalidate(false);
	UpdateWindow();
	
	CView::OnTimer(nIDEvent);
}



void CSTYView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_UP)
	{
		hero.y -= 10;
	}
	if (nChar == VK_DOWN)
	{
		hero.y += 10;
	}
	if (nChar == VK_LEFT)
	{
		hero.x -= 10;
	}
	if (nChar == VK_RIGHT)
	{
		hero.x += 10;
	}
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}



void CSTYView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CView::OnSize(nType, cx, cy);
	wrect.left = 0;
	wrect.top = 0;
	wrect.right = cx;
	wrect.bottom = cy;
	
	hero.x = cx / 2;
	hero.y = cy;
	
	
	//内存DC与BMP初始化，为了清除闪动
	CDC *pDC = GetDC();
	dcBack.DeleteDC();
	dcBack.CreateCompatibleDC(pDC);
	bmpBack.DeleteObject();
	bmpBack.CreateCompatibleBitmap(pDC, cx, cy);
	dcBack.SelectObject(&bmpBack);
	ReleaseDC(pDC);
	
}



void CSTYView::OnGamerestart() 
{
	// TODO: Add your command handler code here
	for (int i = 0; i < N; i++)
	{
		if (i % 4 == 0)
		{
			bullet[i].pos[0] = 0;
			bullet[i].pos[1] = 0;
		}
		else
		{
			bullet[i].pos[0] = wrect.right;
			bullet[i].pos[1] = wrect.bottom / 3;
		}
		
	}
	hero.x = wrect.right / 2;
	hero.y = wrect.bottom;
	time_1 = time(NULL);
	time_2 = time(NULL);
	SetTimer(1, 30, NULL);
	mciSendString("OPEN background.mp3 ALIAS BACKGROUND", NULL, 0, NULL);
	mciSendString("PLAY BACKGROUND FROM 0 REPEAT", NULL, 0, NULL);
	mciSendString("OPEN shoot.mp3 ALIAS SHOOT", NULL, 0, NULL);
	mciSendString("PLAY SHOOT FROM 0 REPEAT", NULL, 0, NULL);
	mciSendString("STOP WIN", NULL, 0, NULL);
				
}




//透明函数
void TransparentBlt2( HDC hdc0,	
					 int nX0,int nY0,
					 int nW0,int nH0,
					 HDC hdc1,
					 int nX1,int nY1,
					 int nW1,int nH1,
					 UINT Tcol
					 )
{	HBITMAP hBMP   =CreateCompatibleBitmap(hdc0,nW0, nH0);
HBITMAP mBMP   =CreateBitmap(nW0,nH0,1,1,NULL);	
HDC		hDC    =CreateCompatibleDC(hdc0);
HDC		mDC    =CreateCompatibleDC(hdc0);
HBITMAP oldBMP =(HBITMAP)SelectObject(hDC, hBMP);
HBITMAP oldmBMP=(HBITMAP)SelectObject(mDC, mBMP);
if (nW0==nW1&&nH0==nH1)
BitBlt(hDC,0,0,nW0,nH0,hdc1,nX1,nY1,SRCCOPY);
else
StretchBlt(hDC,0,0,nW0,nH0,hdc1,nX1,nY1,nW1,nH1,SRCCOPY);

SetBkColor(hDC, Tcol);
BitBlt(mDC,0,0,nW0,nH0,hDC,0,0,SRCCOPY);
SetBkColor(hDC, RGB(0,0,0));
SetTextColor(hDC, RGB(255,255,255));
BitBlt(hDC,0,0,nW0,nH0,mDC,0,0,SRCAND);
SetBkColor(hdc0,RGB(255,255,255));
SetTextColor(hdc0,RGB(0,0,0));

BitBlt(hdc0,nX0,nY0,nW0,nH0,mDC,0,0,SRCAND);
BitBlt(hdc0,nX0,nY0,nW0,nH0,hDC,0,0,SRCPAINT);

SelectObject(hDC, oldBMP);				
DeleteDC(hDC);
SelectObject(mDC, oldmBMP);
DeleteDC(mDC);
DeleteObject(hBMP);
DeleteObject(mBMP);
}
/*
void CSTYView::OnFirst() 
{
// TODO: Add your command handler code here
//	N = 100;	
}

  
	
	  void CSTYView::OnMiddle() 
	  {
	  // TODO: Add your command handler code here
	  //	N = 250;
	  }
	  
		
		  
			void CSTYView::OnTop() 
			{
			// TODO: Add your command handler code here
			//	N = 400;
			
}*/
