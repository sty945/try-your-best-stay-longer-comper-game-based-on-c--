// STYDoc.cpp : implementation of the CSTYDoc class
//

#include "stdafx.h"
#include "STY.h"

#include "STYDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSTYDoc

IMPLEMENT_DYNCREATE(CSTYDoc, CDocument)

BEGIN_MESSAGE_MAP(CSTYDoc, CDocument)
	//{{AFX_MSG_MAP(CSTYDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTYDoc construction/destruction

CSTYDoc::CSTYDoc()
{
	// TODO: add one-time construction code here

}

CSTYDoc::~CSTYDoc()
{
}

BOOL CSTYDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSTYDoc serialization

void CSTYDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSTYDoc diagnostics

#ifdef _DEBUG
void CSTYDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSTYDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSTYDoc commands
