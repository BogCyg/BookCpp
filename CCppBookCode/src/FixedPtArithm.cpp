// ==========================================================================
//
// Software written by Boguslaw Cyganek to be used with the book:
// INTRODUCTION TO PROGRAMMING WITH C++ FOR ENGINEERS
// Published by Wiley, 2020
//
// The software is supplied as is and for educational purposes
// without any guarantees nor responsibility of its use in any application. 
//
// ==========================================================================



#include <iostream>
#include <string>
#include "FxFor.h"




// -----------------------------

// New way of defining constants
// with variable templates
template< typename T >
constexpr T gkPi = T( 3.1415926535897932385 );


// A helper multiple end-of-line
template < auto REP, auto CHAR = '\n' >
std::ostream & endl( std::ostream & o )
{
	// Avoid sending endl - it flushes the stream
	return o << std::string( REP, CHAR );
}

// -----------------------------


using std::cout, std::endl;



void FxPt_Test_1( void )
{
	constexpr auto & kPi { gkPi< double > };


	constexpr FX_8_8	kPi_8_8( gkPi< FX_8_8 > );

	// This checks if kPi_8_8 is created during compilation
	static_assert( kPi_8_8.GetInternalValue() >= 0 );

	// double
	constexpr double	radius( 2.0 );
	constexpr auto area_d ( kPi * radius * radius );

	// FX_8_8
	constexpr FX_8_8	radius_8_8( radius );
	constexpr FX_8_8	area_8_8( gkPi< FX_8_8 > * radius_8_8 * radius_8_8 );

	static_assert( area_8_8.GetInternalValue() >= 0 );



	static_assert( ComputeRoundingError( area_8_8, area_d ) < 0.005 );

	// area_d and area_8_8 have been already precomputed in compilation
	cout << "sizeof(double) = " << sizeof( double );
	cout << ", area< double > = " << area_d << endl;
	cout << "sizeof(FX_8_8) = " << sizeof( FX_8_8 );
	cout << ", area< FX_8_8 > = " << static_cast< double >( area_8_8 ) << endl;
	cout << "Diff = " << ComputeRoundingError( area_8_8, area_d ) << endl << endl< 7 >;



	// ------------------------------------------
	// Compute at run-time

	auto cyl_len { 1000.0 };

	// There will be an overflow
	cout << "volume< FX_8_8 > = " << static_cast< double >( area_8_8 * FX_8_8( cyl_len ) ) << endl;


	FX_16_16	area_16_16( area_8_8 );		// init wider from shorter



	// Compute a volume of a cylinder
	area_16_16 *= cyl_len;

	cout << "volume< FX_16_16 > = " << static_cast< double >( area_16_16 ) << endl;

}



void FxPt_Test_2( void )
{
	// ------------------------------------------
	// const vs. constexpr

	const FX_8_8		d1 {};	// d1 will be const
	constexpr FX_8_8	d2 {};	// d2 will be const and computed durinng compilation

	// Will not compile -  is not sufficient, must be constexpr
	// static_assert( d1.GetInternalValue() >= 0 );

	// This is ok 
	static_assert( d2.GetInternalValue() >= 0 );	
	// Will not compile -  d2 is const FX_8_8
	// d2 *= 2.0;
}






