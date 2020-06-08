///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////


#pragma once		// include this header in the translation unit only once

#include <iostream>
#include <string>
#include <cassert>




namespace CppBook
{
	

using std::wstring;


class TCurrency
{
	private:

		wstring		fCurrKey;		// a 3-letter code, such as USD, EUR, PLN
		wstring		fCurrName;		// a unique name of a currency to be displayed

		double		fSellRate {};		// selling rate – always add {} to stand. types
		double		fBuyRate {};		// buying rate

	public:

		// Two constructors in one
		TCurrency(	const wstring & currCode = L"", const wstring & currName = L"", 
					const double sellRate = 0.0, const double buyRate = 0.0 )
			: fCurrKey( currCode ), fCurrName( currName ), fSellRate( sellRate ), fBuyRate( buyRate )
		{}

	public:

		// Functions to read data
		wstring		GetCurrKey( void ) const { return fCurrKey; }
		wstring		GetCurrName( void ) const { return fCurrName; }	

		double		GetSellRate( void ) const { return fSellRate; }			
		double		GetBuyRate( void ) const { return fBuyRate; }			


		// Functions to write data
		void		SetCurrCode( const wstring & s ) { fCurrKey = s; }
		void		SetCurrName( const wstring & s ) { fCurrName = s; }	
					
		void		SetSellRate( double r ) { fSellRate = r; }			
		void		SetBuyRate( double r ) { fBuyRate = r; }			
};

// "w" for wide-character streams
std::wostream & operator << ( std::wostream & o, const TCurrency & c );

std::wistream & operator >> ( std::wistream & i, TCurrency & c );


}		// CppBook






