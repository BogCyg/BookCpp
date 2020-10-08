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


#include <fstream>
#include "LongNumberFor.h"

using std::cout, std::endl;
using std::ofstream, std::ifstream;



// A function that checks main functionality 
// of the TLongNumberFor class
void LongNumbers_Test( void )
{
	try
	{
		TLongNumberFor< 11 > pesel;

		pesel.SetNumberAt( 7, 7 );
		pesel.SetNumberAt( 8, 8 );

		assert( pesel.GetNumberAt( 7 ) == 7 );
		assert( pesel.GetNumberAt( 8 ) == 8 );


		// Try conversions
		TLongNumberFor< 5 > number_1(  "1234" );

		std::string str { "--" };	// Create std::string from number_1
		str += number_1;		// Convert number_1 to std::string and concatenate with str
		std::cout << str << endl;	// Let's see it

		{

			ofstream testFile( "TLongNumberFor.txt" );
			testFile << number_1;
			testFile.close();
		}


		TLongNumberFor< 5 > number_2;
		{
			ifstream testFile( "TLongNumberFor.txt" );
			testFile >> number_2;
			testFile.close();
		}

		assert( number_1 == number_2 );

		// Now let's try to access at the wrong position
		//cout << number_1[ 33 ];
	}
	catch( const std::exception & e )
	{
		std::cerr << "Out of Range error: " << e.what() << '\n';
	}
	catch( ... )
	{
		std::cerr << "Unknown exception\n";
	}
}








// A function that checks main functionality 
// of the TLongNumberFor class that has the proxy pattern
void LongNumbersWithProxy_Test( void )
{
#ifdef TURN_ON_PROXY

	TLongNumberFor< 11 > id;

	int x = id[ 7 ];	// operator = to read only

	id[ 7 ] = 7;		// use proxy here

	id[ 6 ] = id[ 8 ] = id[ 7 ] = 3;	// use proxy as well		

	assert( id[ 6 ] == 3 );
	assert( id[ 7 ] == 3 );
	assert( id[ 8 ] == 3 );

	assert( id[ 10 ] == id[ 0 ] );

#endif

	// The concordant indexing:      9   ...  0
	const TLongNumberFor< 11 > cid( "9876543210" );	// cid contains "09876543210"
	assert( cid[ 10 ] == cid[ 0 ] );	// the leading 11th digit was set to 0

	//cid[ 0 ] = 5;		cannot do that since cid is const
	int z = cid[ 7 ];	// calls const int TLongNumberFor< 11 >::operator [] ( int position ) const

#ifdef TURN_ON_PROXY

	id[ 7 ] = cid[ 1 ];
	assert( id[ 7 ] == 1 );

#endif
}