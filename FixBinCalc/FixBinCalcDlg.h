// FixBinCalcDlg.h : header file
//

#if !defined(AFX_FIXBINCALCDLG_H__0365BA86_53E9_481D_8734_E9392DA1E78A__INCLUDED_)
#define AFX_FIXBINCALCDLG_H__0365BA86_53E9_481D_8734_E9392DA1E78A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFixBinCalcDlg dialog

class CFixBinCalcDlg : public CDialog
{
public:

	typedef __int64				LongWord;
	typedef unsigned __int64	UnsignedLongWord;

private:

	CString DoStringFromBinary( UnsignedLongWord value, int num_of_bits, unsigned int radix );
	UnsignedLongWord DoBinaryFromString( CString & str, int num_of_bits, unsigned int radix );
	bool Float2Fix( double inFloatVal, int fixIntLen, int fixFracLen, LongWord & outFixInteger, LongWord & outFixFractional );
	bool Fix2Float( LongWord inFixInteger, LongWord inFixFractional, int fixFracLen, double & outFloatVal );


	double ComputeError( double firstFloatValue, LongWord inFixInteger, LongWord inFixFractional, int fixFracLen );
	void RecomputeRepresentation( void );

	bool CheckStringValidity_Int( const CString & theString, int maxLen, int radix );
	bool CheckStringValidity_Frac( const CString & theString, int maxLen, int radix );

	CString ConvertRadices( const CString & theString, int inRadix, int outRadix );


	CString ComputeDecimalRepresentation( void );



	bool CheckChars( const CString & str, int r );
	bool CheckChars( const CString & str, const CString & allowableChars );


// Construction
public:
	CFixBinCalcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFixBinCalcDlg)
	enum { IDD = IDD_FIXBINCALC_DIALOG };
	int		fFixFractionalLength;
	int		fRadix;
	CString	fFixValueRepresentation;
	CString	fFixedValue_IntegerPart;
	CString	fFixedValue_FractionalPart;
	int		fFixIntegerLength;
	int		fTotalLength;
	CString	fTotalError;
	double	fFloatValue;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFixBinCalcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFixBinCalcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonFix2Float();
	afx_msg void OnButtonFloat2Fix();
	afx_msg void OnRadioBin();
	afx_msg void OnRadioHex();
	afx_msg void OnRadioOct();
	afx_msg void OnChangeEditIntLength();
	afx_msg void OnChangeEditFixFractionalLength();
	afx_msg void OnButtonForceValue();
	afx_msg void OnRadioDec();
	afx_msg void OnButtonClearAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIXBINCALCDLG_H__0365BA86_53E9_481D_8734_E9392DA1E78A__INCLUDED_)
