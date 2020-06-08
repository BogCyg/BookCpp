///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////



#include "XML_CurrencyExchanger.h"
#include <fstream>

using namespace std;

namespace CppBook
{


bool	XML_CurrencyExchanger::FillCurrencyTableFrom( const wstring & currencyFile )
{

	wifstream	inFile( currencyFile );

	if( ! inFile.is_open() )
		return false;				// cannot open the input file


	// Read line by line and look for patterns


	ESearchStates	state = ESearchStates::kIdle;

	// Stores currently processed line of the XML 
	wstring line;

	// Stores current match and sub-matches of the regex
	wsmatch	match_res;

	// These will gather partial matches of the currency record
	wstring curr_code, curr_name, buy_rate_str, sell_rate_str;

	// Read params one-by-one
	while( getline( inFile, line ) )
	{

		switch( state )
		{
			case ESearchStates::kIdle:

				if( regex_search( line, match_res, f_curr_name_pat ) && match_res.size() > 1 )
				{
					// Ok, a currency code was found, let's store it
					// require at least one subexpression
					curr_name = match_res[ 1 ];		// take the first sub-match
					
					// For easier processing replace white characters
					replace( curr_name.begin(), curr_name.end(), L' ', L'-');

					state = ESearchStates::k_Name_Processed;	// change the state 
				}				
				
				break;

			case ESearchStates::k_Name_Processed:

				if( regex_search( line, match_res, f_curr_code_pat ) && match_res.size() > 1 )
				{
					// Ok, a currency code found, let's store it
					// require at least one subexpression
					curr_code = match_res[ 1 ];		// take the first sub-match

					state = ESearchStates::k_Code_Processed;	// change the state 
				}				
				
				break;

			case ESearchStates::k_Code_Processed:

				// Try to match the buying option
				if( regex_search( line, match_res, f_buy_rate_pat ) && match_res.size() > 2 )
				{
					// Ok, a currency code found, let's store it
					// require at least one subexpression
					buy_rate_str = wstring( match_res[ 1 ] ) + wstring( L"." ) + wstring( match_res[ 2 ] );		// assembly the sub-match'es

					state = ESearchStates::k_BuyingRate_Processed;	// change the state 
				}		

				break;

			case ESearchStates::k_BuyingRate_Processed:

				// Try to match the selling option
				if( regex_search( line, match_res, f_sell_rate_pat ) && match_res.size() > 2 )
				{
					// Ok, a currency code found, let's store it
					// require at least one subexpression
					sell_rate_str = wstring( match_res[ 1 ] ) + wstring( L"." ) + wstring( match_res[ 2 ] );		// assembly the sub-match'es

					state = ESearchStates::k_SellingRate_Processed;	// change the state 
				}	

				break;

			case ESearchStates::k_SellingRate_Processed:

				// Ok, we are ready to insert the new currency record
				try
				{	
					// can throw an exception e.g. on empty string, wrong format, etc.
					AddCurrency( { curr_code, curr_name, stod( buy_rate_str ), stod( sell_rate_str ) } );
				}
				catch( ... )
				{
					;
				}

				state = ESearchStates::kIdle;		// enter the basic state

				break;

			default:
				assert( false );	// shouldn't be here
				break;
		}


	}



	return true;
}


}	// CppBook



