// STY.h : main header file for the STY application
//

#if !defined(AFX_STY_H__0CD48BAA_02AE_4D45_94CA_E86DA611AE3D__INCLUDED_)
#define AFX_STY_H__0CD48BAA_02AE_4D45_94CA_E86DA611AE3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSTYApp:
// See STY.cpp for the implementation of this class
//

class CSTYApp : public CWinApp
{
public:
	CSTYApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSTYApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSTYApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STY_H__0CD48BAA_02AE_4D45_94CA_E86DA611AE3D__INCLUDED_)
