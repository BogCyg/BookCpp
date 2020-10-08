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


#include "CurrencyExchanger.h"

#include <string>
#include <regex>

using std::wregex;


// (1) Using regex
// (2) Processing XML files
// (3) Working with wstrings
// (4) Using state machine


namespace CppBook
{



class XML_CurrencyExchanger : public TCurrencyExchanger
{

	private:


		// Simple state machine
		enum class ESearchStates { kIdle, k_Name_Processed, k_Code_Processed, k_BuyingRate_Processed, k_SellingRate_Processed };

	private:

		// Let's define some patterns
		// We use raw string formats here R"(   )"
		wregex f_curr_name_pat		{ LR"(<nazwa_waluty>(.+)</nazwa_waluty>)" };
		wregex f_curr_code_pat		{ LR"(<kod_waluty>([[:upper:]][[:upper:]][[:upper:]])</kod_waluty>)" };
		wregex f_buy_rate_pat		{ LR"(<kurs_kupna>([[:d:]]+),([[:d:]]+)</kurs_kupna>)" };		// instead of 1.27, in Poland 1,27 is used (with comma)
		wregex f_sell_rate_pat		{ LR"(<kurs_sprzedazy>([[:d:]]+),([[:d:]]+)</kurs_sprzedazy>)" };

	public:

		// Allow other patterns
		void set_curr_name_pat( const wregex & pat ) { f_curr_name_pat = pat; }
		// ...

	public:

		///////////////////////////////////////////////////////////
		// Fills currency table 
		///////////////////////////////////////////////////////////
		//
		// INPUT:
		//			currencyFile - full path to the XML file
		//				with currency entries
		// OUTPUT:
		//			true if ok, false otherwise
		//
		// REMARKS:
		//
		//
		virtual bool	FillCurrencyTableFrom( const wstring & currencyFile );

};




}	// CppBook




