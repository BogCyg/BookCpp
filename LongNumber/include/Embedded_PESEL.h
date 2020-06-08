///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////


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

