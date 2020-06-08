///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////


#include <iomanip>

#include "Currency.h"



namespace CppBook
{



// "w" for wide-character streams
std::wostream & operator << ( std::wostream & o, const TCurrency & c )
{
	const int kOutWidth { 10 };		// total width of numeric output
	const int kOutPrec { 4 };		// precision for the rates

	o << c.GetCurrKey() << "\t";
	o << c.GetCurrName() << "\t";

	o	<<	std::fixed 
		<<	std::setw( kOutWidth ) 
		<<	std::setprecision( kOutPrec ) 
		<<	c.GetSellRate() << "\t";

	o	<<	std::fixed 
		<<	std::setw( kOutWidth ) 
		<<	std::setprecision( kOutPrec ) 
		<< c.GetBuyRate()  << "\t";

	return o;
}

std::wistream & operator >> ( std::wistream & i, TCurrency & c )
{
	wstring s {};	// empty temporary string
	i >> s; c.SetCurrCode( s );
	i >> s; c.SetCurrName( s );

	double tmp {};	// temporary double
	i >> tmp; c.SetSellRate( tmp );
	i >> tmp; c.SetBuyRate( tmp );

	return i;
}



}	// CppBook

