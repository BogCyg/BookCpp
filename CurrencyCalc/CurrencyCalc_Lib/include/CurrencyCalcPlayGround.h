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


#pragma once		// include this header to the translation unit only once

#include <optional>

#include "XML_CurrencyExchanger.h"


// --------------------
namespace CurrExchanger
{
	using std::wstring;


	extern wstring initDefaultFileName;



	using CppBook::TCurrencyExchanger;

	using CurrExch_Optional = std::optional< TCurrencyExchanger >;



	auto CreateCurExchanger( const wstring & initFileFullPath ) -> CurrExch_Optional;


	void DisplayAllCurrencies( const TCurrencyExchanger & currencyExchangerObj );


	void DisplayCurrentTime( void );


	// Perform currency exchange based on user's commands.
	void UserInterface( const TCurrencyExchanger & currencyExchangerObj );

	// Run if we already have the currency exchanger object
	void Run( const TCurrencyExchanger & currExchObj );


	// All actions
	void Run( void );



	// --------------------------------------------------------
	// A version that can load from a HTTP downloaded XML file.
	namespace OnLine_CurrExchanger
	{
		extern wstring nbp_addr;

		using CppBook::XML_CurrencyExchanger;

		using XML_CurrExch_Optional = std::optional< XML_CurrencyExchanger >;

		// There are two options for the return object:
		// - It is either TCurrencyExchanger if properly built
		// - or empty CurrExch_Optional if cannot create 
		auto CreateCurExchanger( const wstring & http_XML_FileName, const wstring & initFileFullPath ) -> XML_CurrExch_Optional;

		// All actions
		void Run( void );

		bool CurExchanger_DownloadCurrencies( const wstring & http_addr, const wstring & local_XML_FullPath );

		void CurExchanger_SaveInitFile( const XML_CurrencyExchanger & obj, const wstring & initFileFullPath );

	}



}





/////////////////////////////////////////////////////////








