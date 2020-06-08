// FixBinCalcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FixBinCalc.h"
#include "FixBinCalcDlg.h"
#include "math.h"
#include "EnterNewValueDialog.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////





CString CFixBinCalcDlg::DoStringFromBinary( UnsignedLongWord value, int num_of_bits, unsigned int radix )
{
	CString retStr( "" );

	while( num_of_bits -- > 0 )
	{
		UnsignedLongWord reminder = value % radix;
		value = value / radix;

		CString reminderStr;
		reminderStr.Format( "%X", reminder );
		
		retStr += reminderStr;	
	}

	retStr.MakeReverse();

	return retStr;
}

CFixBinCalcDlg::UnsignedLongWord CFixBinCalcDlg::DoBinaryFromString( CString & str, int num_of_bits, unsigned int radix )
{
	UnsignedLongWord retVal = 0;

	int string_index = 0;
	while( num_of_bits -- > 0 )
	{
		retVal *= radix;

		int digit;
		
		if( string_index < str.GetLength() )
		{
			char digit_letter = str.GetAt( string_index ++ );
			//                   '0'                     '9'
			if( digit_letter >= 0x30 && digit_letter <= 0x39 )
				digit = digit_letter - 0x30;
			else
				// Upper case, please...
			    //                   'A'                     'F'
				if( digit_letter >= 0x41 && digit_letter <= 0x46 )
					digit = digit_letter - 0x37;
				else
					digit = 0;
		}
		else
		{
			digit = 0;			// fill up trailing zeros in the string
		}

		retVal += digit;
	}

	return retVal;
}


bool CFixBinCalcDlg::Float2Fix( double inFloatVal, int fixIntLen, int fixFracLen, LongWord & outFixInteger, LongWord & outFixFractional )
{
	bool isNegative = false;
	if( inFloatVal < 0.0 )
	{
		isNegative = true;
		inFloatVal = - inFloatVal;
	}

	// Now, the float value is positive
	ASSERT( inFloatVal >= 0.0 );

	outFixInteger = (LongWord)( inFloatVal );
	long double floatFraction = inFloatVal - outFixInteger;


	long double frac_scale_factor = pow( 2, fixFracLen );
	long double fractional_scaled = floatFraction * frac_scale_factor;


	outFixFractional = (LongWord)fractional_scaled;

	if( isNegative == true )
	{
		outFixInteger = ~ outFixInteger;

		if( outFixFractional == 0 )
			++ outFixInteger;

		outFixFractional = ~ outFixFractional;
		++ outFixFractional;
	}

	return true;
}


bool CFixBinCalcDlg::Fix2Float( LongWord inFixInteger, LongWord inFixFractional, int fixFracLen, double & outFloatVal )
{
	outFloatVal = inFixInteger;

	double outFloatVal_Fractional = inFixFractional;
	double frac_scale_factor = pow( 2, fixFracLen );
	outFloatVal_Fractional /= frac_scale_factor;

	outFloatVal += outFloatVal_Fractional;

	return true;
}



/////////////////////////////////////////////////////////////////////////////
// CFixBinCalcDlg dialog

CFixBinCalcDlg::CFixBinCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFixBinCalcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFixBinCalcDlg)
	fFixFractionalLength = 16;
	fRadix = 0;
	fFixValueRepresentation = _T("");
	fFixedValue_IntegerPart = _T("");
	fFixedValue_FractionalPart = _T("");
	fFixIntegerLength = 16;
	fTotalLength = fFixFractionalLength + fFixIntegerLength;
	fTotalError = _T("");
	fFloatValue = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFixBinCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFixBinCalcDlg)
	DDX_Text(pDX, IDC_EDIT_FIX_FRACTIONAL_LENGTH, fFixFractionalLength);
	DDV_MinMaxInt(pDX, fFixFractionalLength, 0, 64);
	DDX_Radio(pDX, IDC_RADIO_BIN, fRadix);
	DDX_Text(pDX, IDC_EDIT_FIXED_VAL_REPRESENTATION, fFixValueRepresentation);
	DDX_Text(pDX, IDC_EDIT_FIXED_VAL_INTEGER, fFixedValue_IntegerPart);
	DDX_Text(pDX, IDC_EDIT_FIXED_VAL_FRACTIONAL, fFixedValue_FractionalPart);
	DDX_Text(pDX, IDC_EDIT_FIX_INTEGER_LENGTH, fFixIntegerLength);
	DDV_MinMaxInt(pDX, fFixIntegerLength, 0, 64);
	DDX_Text(pDX, IDC_EDIT_TOTAL_LENGTH, fTotalLength);
	DDX_Text(pDX, IDC_EDIT_ERROR, fTotalError);
	DDX_Text(pDX, IDC_EDIT_FLOAT_VALUE, fFloatValue);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFixBinCalcDlg, CDialog)
	//{{AFX_MSG_MAP(CFixBinCalcDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FIX_2_FLOAT, OnButtonFix2Float)
	ON_BN_CLICKED(IDC_BUTTON_FLOAT_2_FIX, OnButtonFloat2Fix)
	ON_BN_CLICKED(IDC_RADIO_BIN, OnRadioBin)
	ON_BN_CLICKED(IDC_RADIO_HEX, OnRadioHex)
	ON_BN_CLICKED(IDC_RADIO_OCT, OnRadioOct)
	ON_EN_CHANGE(IDC_EDIT_FIX_INTEGER_LENGTH, OnChangeEditIntLength)
	ON_EN_CHANGE(IDC_EDIT_FIX_FRACTIONAL_LENGTH, OnChangeEditFixFractionalLength)
	ON_BN_CLICKED(IDC_BUTTON_FORCE_VALUE, OnButtonForceValue)
	ON_BN_CLICKED(IDC_RADIO_DEC, OnRadioDec)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_ALL, OnButtonClearAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFixBinCalcDlg message handlers

BOOL CFixBinCalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	OnButtonFloat2Fix();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFixBinCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFixBinCalcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFixBinCalcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFixBinCalcDlg::OnButtonFix2Float() 
{
	UpdateData( TRUE );

	UnsignedLongWord inFixInteger;
	UnsignedLongWord inFixFractional;

	unsigned int radix = 2;

	// At first check whether the strings contain valid data
	if( CheckStringValidity_Int( fFixedValue_IntegerPart, fFixIntegerLength, radix ) == false )
		return;
	if( CheckStringValidity_Frac( fFixedValue_FractionalPart, fFixFractionalLength, radix ) == false )
		return;


	int missingLeadingZeros = fFixIntegerLength - fFixedValue_IntegerPart.GetLength();
	while( missingLeadingZeros -- > 0 )
		fFixedValue_IntegerPart.Insert( 0, TCHAR( '0' ) );

	
	inFixInteger = DoBinaryFromString( fFixedValue_IntegerPart, fFixIntegerLength, radix );
	LongWord theIntValue;
	if( fFixedValue_IntegerPart.GetLength() == fFixIntegerLength && fFixedValue_IntegerPart[ 0 ] == '1' )
	{
		LongWord max_val = pow( 2.0, fFixIntegerLength );
		LongWord new_val = max_val - (LongWord)inFixInteger;
		theIntValue = - (int)new_val;
	}
	else
	{
		theIntValue = inFixInteger;
	}

	inFixFractional = DoBinaryFromString( fFixedValue_FractionalPart, fFixFractionalLength, radix );
	
	double localFloatValue;
	Fix2Float( theIntValue, inFixFractional, fFixFractionalLength, fFloatValue );

	UpdateData( FALSE );

	RecomputeRepresentation();

	double totalError = ComputeError( fFloatValue, theIntValue, inFixFractional, fFixFractionalLength );
	fTotalError.Format( _T("%e"), totalError );
	UpdateData( FALSE );
}

void CFixBinCalcDlg::OnButtonFloat2Fix() 
{
	UpdateData( TRUE );

	LongWord outFixInteger;
	LongWord outFixFractional;

	Float2Fix( fFloatValue, fFixIntegerLength, fFixFractionalLength, outFixInteger, outFixFractional );

	unsigned int radix = 2;

	fFixedValue_IntegerPart		= DoStringFromBinary( outFixInteger, fFixIntegerLength, radix );
	fFixedValue_FractionalPart	= DoStringFromBinary( outFixFractional, fFixFractionalLength, radix );


	UpdateData( FALSE );


	RecomputeRepresentation();

	// We have to recompute from the string since only the fFixFractionalLength of bits
	// is valid
	UnsignedLongWord integerPart = DoBinaryFromString( fFixedValue_IntegerPart, fFixIntegerLength, radix );
	UnsignedLongWord fractionalPart = DoBinaryFromString( fFixedValue_FractionalPart, fFixFractionalLength, radix );
	LongWord theIntValue;
	if( fFixedValue_IntegerPart.GetLength() == fFixIntegerLength && fFixedValue_IntegerPart[ 0 ] == '1' )
	{
		LongWord max_val = pow( 2.0, fFixIntegerLength );
		LongWord new_val = max_val - (LongWord)integerPart;
		theIntValue = - (int)new_val;
	}
	else
	{
		theIntValue = integerPart;
	}
	double totalError = ComputeError( fFloatValue, theIntValue, fractionalPart, fFixFractionalLength );
	fTotalError.Format( _T("%e"), totalError );
	UpdateData( FALSE );
}

void CFixBinCalcDlg::RecomputeRepresentation( void )
{
	UpdateData( TRUE );

	CString totalVal( fFixedValue_IntegerPart );
	totalVal += fFixedValue_FractionalPart;


	static int radix[] = { 2, 8, 10, 16 };
	ASSERT( fRadix < sizeof( radix )/ sizeof( radix[0] ) );
	int theRadix = radix[ fRadix ];
	
	fFixValueRepresentation = theRadix == 10 ? ComputeDecimalRepresentation() : ConvertRadices( totalVal, 2, theRadix );

	UpdateData( FALSE );
}


void CFixBinCalcDlg::OnRadioBin() 
{
	RecomputeRepresentation();
}

void CFixBinCalcDlg::OnRadioOct() 
{
	RecomputeRepresentation();
}

void CFixBinCalcDlg::OnRadioDec() 
{
	RecomputeRepresentation();
}

void CFixBinCalcDlg::OnRadioHex() 
{
	RecomputeRepresentation();
}

void CFixBinCalcDlg::OnChangeEditIntLength() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData( TRUE );
	fTotalLength = fFixFractionalLength + fFixIntegerLength;
	UpdateData( FALSE );

	OnButtonFloat2Fix();
}

void CFixBinCalcDlg::OnChangeEditFixFractionalLength() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData( TRUE );
	fTotalLength = fFixFractionalLength + fFixIntegerLength;
	UpdateData( FALSE );

	OnButtonFloat2Fix();
}

double CFixBinCalcDlg::ComputeError( double firstFloatValue, LongWord inFixInteger, LongWord inFixFractional, int fixFracLen )
{
	double secondFloatValue;
	Fix2Float( inFixInteger, inFixFractional, fixFracLen, secondFloatValue );
	return fabs( firstFloatValue - secondFloatValue );
}

bool CFixBinCalcDlg::CheckStringValidity_Int( const CString & theString, int maxLen, int radix )
{
	if( theString.GetLength() > maxLen )
	{
		AfxMessageBox( _T("Length of the integer part is longer than number of declared bits.\n Please correct."), MB_OK | MB_ICONSTOP );
		return false;
	}

	const CString kForbiddenForTwo( "23456789" );

	if( theString.FindOneOf( kForbiddenForTwo ) >= 0 )
	{
		AfxMessageBox( _T("Found not allowable digits for this radix in the integer part.\n Please correct."), MB_OK | MB_ICONSTOP );
		return false;
	}

	return true;
}

bool CFixBinCalcDlg::CheckStringValidity_Frac( const CString & theString, int maxLen, int radix )
{
	if( theString.GetLength() > maxLen )
	{
		AfxMessageBox( _T("Length of the fractional part is longer than number of declared bits.\n Please correct."), MB_OK | MB_ICONSTOP );
		return false;
	}

	const CString kForbiddenForTwo( "23456789" );

	if( theString.FindOneOf( kForbiddenForTwo ) >= 0 )
	{
		AfxMessageBox( _T("Found not allowable digits for this radix in the fractional part.\n Please correct."), MB_OK | MB_ICONSTOP );
		return false;
	}

	return true;
}


CString CFixBinCalcDlg::ConvertRadices( const CString & inString, int inRadix, int outRadix )
{
	CString theString( inString );
	CString retStr;

	int chunkLen;
	int tmp = inRadix;
	for( chunkLen = 1; chunkLen <= max( inRadix, outRadix ); ++ chunkLen )
	{
		if( tmp >= outRadix )
			break;

		tmp *= inRadix;
	}

	int out_digit_len = log10( inRadix ) / log10( outRadix );
	if( out_digit_len == 0 )
		out_digit_len = 1;
	while( theString.GetLength() > 0 )
	{
		int charsToGetFromRight = min( chunkLen, theString.GetLength() );
		CString newDigit( theString.Right( charsToGetFromRight ) );

		theString.Delete( theString.GetLength() - charsToGetFromRight, charsToGetFromRight );

		UnsignedLongWord  inVal = DoBinaryFromString( newDigit, charsToGetFromRight, inRadix );

		CString digit_str = DoStringFromBinary( inVal, out_digit_len, outRadix );
		digit_str += retStr;
		retStr = digit_str;

	}



	return retStr;
}



CString CFixBinCalcDlg::ComputeDecimalRepresentation( void ) 
{
	UnsignedLongWord integerPart = DoBinaryFromString( fFixedValue_IntegerPart + fFixedValue_FractionalPart, fFixIntegerLength + fFixFractionalLength, 2 );

	int dec_len = ( fFixIntegerLength + fFixFractionalLength ) * log10( 2 );
	return DoStringFromBinary( integerPart, dec_len + 1, 10 );
}




void CFixBinCalcDlg::OnButtonForceValue() 
{
	CEnterNewValueDialog theDialog;
	if( theDialog.DoModal() != IDOK )
		return;

	// Convert to uppercase
	theDialog.fNewValue.MakeUpper();

	static int radix[] = { 2, 8, 10, 16 };
	ASSERT( fRadix < sizeof( radix )/ sizeof( radix[0] ) );
	int inRadix = radix[ fRadix ];

	if( CheckChars( theDialog.fNewValue, inRadix ) == false )
	{
		AfxMessageBox( _T("The entered string contains letters that do not fit the current base.\n Please correct."), MB_OK | MB_ICONSTOP );
		return;
	}
	
	if( inRadix == 10 )
	{
		UnsignedLongWord val = DoBinaryFromString( theDialog.fNewValue, theDialog.fNewValue.GetLength(), 10 );

		inRadix = 16;
		theDialog.fNewValue = DoStringFromBinary( val, theDialog.fNewValue.GetLength(), inRadix );
		
		// Added by BC on June 22nd '07 to remove leading zeros
		theDialog.fNewValue.TrimLeft( _T('0') );
	}
	
	CString str = ConvertRadices( theDialog.fNewValue, inRadix, 2 );
	// Added by BC on June 22nd '07 to remove leading zeros
	str.TrimLeft( _T('0') );

	int str_len = str.GetLength();

	int start_fractional_index = str_len - fFixFractionalLength;
	if( start_fractional_index < 0 )
		start_fractional_index = 0;
	fFixedValue_FractionalPart	= str.Mid( start_fractional_index );
	int i;
	int fill_number = fFixFractionalLength - fFixedValue_FractionalPart.GetLength();
	for( i = 0; i < fill_number; ++ i )
		fFixedValue_FractionalPart.Insert( 0, '0' );
	
	if( start_fractional_index < 1 )
		fFixedValue_IntegerPart = "";
	else
		fFixedValue_IntegerPart	= str.Left( start_fractional_index );

	fill_number = fFixIntegerLength - fFixedValue_IntegerPart.GetLength();
	if( fill_number < 0 )
	{
		AfxMessageBox( _T("Length of the integer part is longer than number of declared bits.\n Please correct."), MB_OK | MB_ICONSTOP );
		return;
	}

	for( i = 0; i < fill_number; ++ i )
		fFixedValue_IntegerPart.Insert( 0, '0' );

	UpdateData( FALSE );

	RecomputeRepresentation();

	OnButtonFix2Float();
}


bool CFixBinCalcDlg::CheckChars( const CString & str, int r )
{
	switch( r )
	{
		case 2:
			return CheckChars( str, "01" );
		case 8:
			return CheckChars( str, "01234567" );
		case 10:
			return CheckChars( str, "0123456789" );
		case 16:
			return CheckChars( str, "0123456789ABCDEFabcdef" );
		default:
			return false;
	}

	return true;
}

bool CFixBinCalcDlg::CheckChars( const CString & str, const CString & allowableChars )
{
	for( int i = 0; i < str.GetLength(); ++ i )
		if( allowableChars.Find( str[ i ] ) == -1 )
			return false;

	return true;
}


void CFixBinCalcDlg::OnButtonClearAll() 
{
	fFloatValue = 0.0;
	UpdateData( FALSE );
	OnButtonFloat2Fix();
}
