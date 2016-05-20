// MyChessDoc.cpp : implementation of the CMyChessDoc class
//

#include "stdafx.h"
#include "MyChess.h"

#include "MyChessDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyChessDoc

IMPLEMENT_DYNCREATE(CMyChessDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyChessDoc, CDocument)
	//{{AFX_MSG_MAP(CMyChessDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyChessDoc construction/destruction

CMyChessDoc::CMyChessDoc()
{
	// TODO: add one-time construction code here

}

CMyChessDoc::~CMyChessDoc()
{
}

BOOL CMyChessDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyChessDoc serialization

void CMyChessDoc::Serialize(CArchive& ar)
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
// CMyChessDoc diagnostics

#ifdef _DEBUG
void CMyChessDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyChessDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyChessDoc commands
