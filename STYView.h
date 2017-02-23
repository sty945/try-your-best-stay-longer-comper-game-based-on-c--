// STYView.h : interface of the CSTYView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STYVIEW_H__8A8B70B8_3767_4B94_81DB_6668CBD8C8DE__INCLUDED_)
#define AFX_STYVIEW_H__8A8B70B8_3767_4B94_81DB_6668CBD8C8DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define  N 300

struct Bullet
{
	float pos[2];
	float dir[2];
	bool alive;
	COLORREF m_color;
};

class CSTYView : public CView
{
protected: // create from serialization only
	CSTYView();
	DECLARE_DYNCREATE(CSTYView)

// Attributes
public:
	CSTYDoc* GetDocument();

	//定义变量
	Bullet bullet[N];
	CRect wrect;
	CPoint hero;
	int count;
	time_t time_1;
	time_t time_2;
	CBitmap bmpGround, bmpHero;
	
	CDC dcBack;  //为了去除闪动
	CBitmap bmpBack;





// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSTYView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSTYView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSTYView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGamerestart();
	afx_msg void OnFirst();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in STYView.cpp
inline CSTYDoc* CSTYView::GetDocument()
   { return (CSTYDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STYVIEW_H__8A8B70B8_3767_4B94_81DB_6668CBD8C8DE__INCLUDED_)
