// STYDoc.h : interface of the CSTYDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STYDOC_H__6763ADF5_645C_4F2E_A911_B5E7A6222AE3__INCLUDED_)
#define AFX_STYDOC_H__6763ADF5_645C_4F2E_A911_B5E7A6222AE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSTYDoc : public CDocument
{
protected: // create from serialization only
	CSTYDoc();
	DECLARE_DYNCREATE(CSTYDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSTYDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSTYDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSTYDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STYDOC_H__6763ADF5_645C_4F2E_A911_B5E7A6222AE3__INCLUDED_)
