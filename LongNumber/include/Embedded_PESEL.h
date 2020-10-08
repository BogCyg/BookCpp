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


#define ALLOW_INHERITANCE 0

#include "LongNumberFor.h"






/////////////////////////////////////////////////////////////////////////////////
// The "has-a" version
class PESEL
{
	private:

		// Some constants specific to the Polish PESEL number
		enum { kBirthYear_Dec = 10, kBirthYear_Sngl = 9, kSex = 1 };

	public:

		enum class ESex { kMan, kWoman };

	private:

		using LongNumberObject = TLongNumberFor< 11 >;
		LongNumberObject				fData;

	public:

		PESEL( void ) {}
		PESEL( const string & s ) : fData( s ) {}

	public:

		auto GetYearOfBirth( void ) 
		{ 
			return fData.GetNumberAt( kBirthYear_Dec ) * 10 + fData.GetNumberAt( kBirthYear_Sngl );
		}

		ESex GetSex( void )
		{
			return ( fData.GetNumberAt( kSex ) & 0x01 ) == 0x01 ? ESex::kMan : ESex::kWoman;
		}

};

