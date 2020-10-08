// ==========================================================================
//
// Software written by Boguslaw Cyganek (C) to be used with the book:
// INTRODUCTION TO PROGRAMMING WITH C++ FOR ENGINEERS
// Published by Wiley, 2020
//
// The software is supplied as is and for educational purposes
// without any guarantees nor responsibility of its use in any application. 
//
// ==========================================================================



#pragma once


#include "Currency.h"

#include <map>





namespace CppBook
{


class TCurrencyExchanger
{
	public:

		// a kye-value data structure
		using CurrencyMap = std::map< wstring, TCurrency >;		

	private:

		CurrencyMap							fCurrencyMap;	// a map will store TCurrency objects

	public:

		// Let the compiler generate these.
		TCurrencyExchanger( void ) = default;
		virtual ~TCurrencyExchanger() = default;

	public:

		///////////////////////////////////////////////////////////
		// This function converts a value of one currency into
		// the other currency
		///////////////////////////////////////////////////////////
		//
		// INPUT:
		//			from_key - a 3-letter code of a currency (USD, PLN, etc.)
		//			from_val - value to convert
		//			to_key - a code of a destination currency
		//			to_val - output value
		//
		// OUTPUT:
		//			true if ok, false otherwise
		//
		// REMARKS:
		//			If from_key or to_key is not included in the map
		//			the function will throw an exception; a given currency
		//			code can be checked by calling FindCurrency member
		//
		bool Convert( const wstring & from_key, const double from_val, const wstring & to_key, double & to_val ) const;


		///////////////////////////////////////////////////////////
		// A helper to access fCurrencyMap for read only
		///////////////////////////////////////////////////////////
		//
		// INPUT:
		//			none
		// OUTPUT:
		//			the internal map data structure (for read only)
		//
		// REMARKS:
		//
		//
		const CurrencyMap & GetCurrencyMap( void ) const { return fCurrencyMap;	}


		///////////////////////////////////////////////////////////
		// Find and return currency by its code;
		// Returns true if ok, false if cannot find.
		///////////////////////////////////////////////////////////
		//
		// INPUT:
		//			currency_code - the 3-letters currency code, such
		//				as "USD", "EUR", etc. 
		//			outCurrency - contains found currency if returned true
		// OUTPUT:
		//			true if ok, false if cannot find
		//
		// REMARKS:
		//
		//
		bool FindCurrency( const wstring & currency_code, TCurrency & outCurrency ) const;


		///////////////////////////////////////////////////////////
		// Adds new currency record to the data-base
		///////////////////////////////////////////////////////////
		//
		// INPUT:
		//			new_currency - new currency record; If such 
		//				already exist it is obliterated by this one
		// OUTPUT:
		//			none
		//
		// REMARKS:
		//
		//
		void AddCurrency( const TCurrency & new_currency );

	private:

		// Friends to read and write to fCurrencyMap
		friend std::wostream & operator << ( std::wostream & o, const TCurrencyExchanger & c );
		friend std::wistream & operator >> ( std::wistream & i, TCurrencyExchanger & c );
};


}		// End of the CppBook namespace

