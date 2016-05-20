// MyChess.h : main header file for the MYCHESS application
//

#if !defined(AFX_MYCHESS_H__BFFACCC8_F0F9_419A_8476_4CBA4E7E5209__INCLUDED_)
#define AFX_MYCHESS_H__BFFACCC8_F0F9_419A_8476_4CBA4E7E5209__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyChessApp:
// See MyChess.cpp for the implementation of this class
//

class CMyChessApp : public CWinApp
{
public:
	CMyChessApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyChessApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyChessApp)
	afx_msg void OnAppAbout();
	//afx_msg void OnFileReset();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCHESS_H__BFFACCC8_F0F9_419A_8476_4CBA4E7E5209__INCLUDED_)
