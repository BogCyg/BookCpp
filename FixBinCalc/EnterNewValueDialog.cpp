// EnterNewValueDialog.cpp : implementation file
//

#include "stdafx.h"
#include "FixBinCalc.h"
#include "EnterNewValueDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnterNewValueDialog dialog


CEnterNewValueDialog::CEnterNewValueDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEnterNewValueDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnterNewValueDialog)
	fNewValue = _T("");
	//}}AFX_DATA_INIT
}


void CEnterNewValueDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnterNewValueDialog)
	DDX_Text(pDX, IDC_EDIT_VALUE, fNewValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnterNewValueDialog, CDialog)
	//{{AFX_MSG_MAP(CEnterNewValueDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnterNewValueDialog message handlers
