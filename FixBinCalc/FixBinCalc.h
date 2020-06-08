// FixBinCalc.h : main header file for the FIXBINCALC application
//

#if !defined(AFX_FIXBINCALC_H__A4644F60_3461_43BE_B8B2_B802DDEF125A__INCLUDED_)
#define AFX_FIXBINCALC_H__A4644F60_3461_43BE_B8B2_B802DDEF125A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFixBinCalcApp:
// See FixBinCalc.cpp for the implementation of this class
//

class CFixBinCalcApp : public CWinApp
{
public:
	CFixBinCalcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFixBinCalcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFixBinCalcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIXBINCALC_H__A4644F60_3461_43BE_B8B2_B802DDEF125A__INCLUDED_)
