// MyChessView.h : interface of the CMyChessView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCHESSVIEW_H__DA1670CB_84F3_4AF5_9C3D_6BFF6A729261__INCLUDED_)
#define AFX_MYCHESSVIEW_H__DA1670CB_84F3_4AF5_9C3D_6BFF6A729261__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyChessView : public CView
{
protected: // create from serialization only
	CMyChessView();
	DECLARE_DYNCREATE(CMyChessView)

// Attributes
public:
	CMyChessDoc* GetDocument();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyChessView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	void xxx();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyChessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyChessView)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnFileReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	//virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void Reset_Board();
};

#ifndef _DEBUG  // debug version in MyChessView.cpp
inline CMyChessDoc* CMyChessView::GetDocument()
   { return (CMyChessDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCHESSVIEW_H__DA1670CB_84F3_4AF5_9C3D_6BFF6A729261__INCLUDED_)
