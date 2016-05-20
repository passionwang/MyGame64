// MyChessDoc.h : interface of the CMyChessDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCHESSDOC_H__82CBDD7D_EBD3_4A13_9453_3A867A1DE48C__INCLUDED_)
#define AFX_MYCHESSDOC_H__82CBDD7D_EBD3_4A13_9453_3A867A1DE48C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyChessDoc : public CDocument
{
protected: // create from serialization only
	CMyChessDoc();
	DECLARE_DYNCREATE(CMyChessDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyChessDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyChessDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyChessDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCHESSDOC_H__82CBDD7D_EBD3_4A13_9453_3A867A1DE48C__INCLUDED_)
