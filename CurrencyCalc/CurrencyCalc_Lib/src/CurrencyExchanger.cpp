


#include "CurrencyExchanger.h"
#include <algorithm>




namespace CppBook
{

using std::wostream, std::wistream;	// Introduce these std objects to the scope


wostream & operator << ( wostream & o, const TCurrencyExchanger & c )
{
	for( const auto & currency : c.fCurrencyMap )
		o << currency.second << L"\n";
	return o;
}

wistream & operator >> ( wistream & i, TCurrencyExchanger & c )
{
	TCurrency	currency;		// temporary currency (one line from file)

	// Read record-by-record and insert to the map;
	// The fCurrKey becomes the map key.
	while( i >> currency )
		c.AddCurrency( currency );

	return i;
}

bool TCurrencyExchanger::Convert( const wstring & from_key, const double from_val, const wstring & to_key, double & to_val ) const
{
	try
	{
		// Get the exchange ratios 
		double fromCurr_ExchRatio	= fCurrencyMap.at( from_key ).GetSellRate();
		double toCurr_ExchRatio		= fCurrencyMap.at( to_key ).GetBuyRate();

		// First we buy to the reference
		double val = from_val * fromCurr_ExchRatio;
	
		// The we sell
		assert( toCurr_ExchRatio > 1e-6 );	// check that we don't divide by 0
		to_val = val / toCurr_ExchRatio;
	}
	catch( ... )
	{
		return false;		// problems, sorry

	}
		
	return true;			// operation ok
}

// Find and return currency by its code;
// Returns true if ok, false if cannot find.
bool TCurrencyExchanger::FindCurrency( const wstring & currency_code, TCurrency & outCurrency ) const
{
	if( auto pos = fCurrencyMap.find( currency_code ); pos != fCurrencyMap.end() )
	{
		outCurrency = ( * pos ).second;
		return true;
	}
		
	return false;
}


void TCurrencyExchanger::AddCurrency( const TCurrency & new_currency )
{
	fCurrencyMap[ new_currency.GetCurrKey() ] = new_currency;	
}




}	// CppBook



