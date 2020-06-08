#if !defined(AFX_ENTERNEWVALUEDIALOG_H__90AB8C8D_DD33_4562_B5A1_933263A17737__INCLUDED_)
#define AFX_ENTERNEWVALUEDIALOG_H__90AB8C8D_DD33_4562_B5A1_933263A17737__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnterNewValueDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEnterNewValueDialog dialog

class CEnterNewValueDialog : public CDialog
{
// Construction
public:
	CEnterNewValueDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnterNewValueDialog)
	enum { IDD = IDD_DIALOG_ENTER_NEW_VALUE };
	CString	fNewValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnterNewValueDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnterNewValueDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTERNEWVALUEDIALOG_H__90AB8C8D_DD33_4562_B5A1_933263A17737__INCLUDED_)
