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




#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <fstream>

#include "range.h"




using std::cout, std::endl;
using std::vector;


using CppBook::range;

///////////////////////////////////////////////////////////////////////////////////////////////


void RangeTest( void )
{
	std::ofstream ostr( "RangeTest.txt" );
	if( ostr.is_open() == false )
		return;

	// 1:
	ostr << "1st test:" << endl;

	vector< float > v = range( 256.0f );
	std::copy( v.begin(), v.end(), std::ostream_iterator< float >( ostr, ", " ) );

	// 2:
	ostr << endl << "2nd test:" << endl;

	const unsigned int rr { 5 };
	vector< size_t >	v_size_t( range<>( 0, 100, 13 ) );
	for( auto a : v_size_t )
		ostr << a << ", ";

	// 3:
	ostr << endl << "3rd test:" << endl;

	auto vvv = range( 123 );	// 0..122 inclusive, with step 1
	for( auto a : vvv )
		ostr << a << ", ";

	// 4:
	ostr << endl << "4th test:" << endl;

	// Can be used in the nested loops as well
	for( auto i : range( 0.0, 256.0, 16.5 ) ) // Must be the same type, 0.0 not 0
	{
		for( auto j : range( -2, +16, 3 ) ) 
		{
			ostr << j << ", ";
		}
		ostr << endl << i << endl;
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////


