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
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <cassert>





//using namespace std;

using std::vector, std::string, std::tuple;
using std::cout, std::cin, std::endl;

// Converts decimal number in_dec_num into a Roman numeral string
auto ConvertDecimal_2_Roman( int in_dec_num )
{
	assert( in_dec_num <= 3999 );

	// The values need to be sorted from the largest one
	const vector< tuple< int, string > > RomanValueTranslator  
    {
        {	1000,	"M"	},		{	900,	"CM"	},
        {	500,	"D"	},		{	400,	"CD"	},
        {	100,	"C"	},		{	90,		"XC"	},
        {	50,		"L"	},		{	40,		"XL"	},
        {	10,		"X"	},		{	9,		"IX"	},
        {	5,		"V"	},		{	4,		"IV"	},
        {	1,		"I"	}
    };

	string outStr { "" };
	// Traverse all tuples [ val, str ], starting from the largest val
	for( const auto & [ val, str ] : RomanValueTranslator )	// structured binding
        while( in_dec_num >= val )					// iterate subtracting
            outStr += str, in_dec_num -= val;	// the largest possible value

    return outStr;
}




void Dec_2_Roman_Test( void )
{
	cout << "1593 <=> " << ConvertDecimal_2_Roman( 1593 ) << endl;

	cout << "1968 <=> " << ConvertDecimal_2_Roman( 1968 ) << endl;
	
	cout << "1999 <=> " << ConvertDecimal_2_Roman( 1999 ) << endl;
	
	cout << "2008 <=> " << ConvertDecimal_2_Roman( 2008 ) << endl;
}


/////////////////////////////////////////////////////////////////////////


// Unit test for ConvertDecimal_2_Roman
bool ConvertDecimal_2_Roman_UnitTest( void )
{
	assert( ConvertDecimal_2_Roman( 2000 ) == "MM" );
	assert( ConvertDecimal_2_Roman( 137 ) == "CXXXVII" );
	assert( ConvertDecimal_2_Roman( 1999 ) == "MCMXCIX" );
	//assert( ConvertDecimal_2_Roman( 2018 ) == "MMVIII" );	// a mistake to catch

	return true;
}




/////////////////////////////////////////////////////////////////////////



auto ConvertRoman_2_DecimalNumber( const string & Roman_str )
{
	int out_dec_num {};

	// Write the conversion algorithm ...


	return out_dec_num;
}




/////////////////////////////////////////////////////////////////////////




#include <random>

///////////////////////////////////////////////////////////
// Creates a vector with random integers
///////////////////////////////////////////////////////////
//
// INPUT:
//			kFrom, kTo - range of values
//			kNumOfTrials - the number of values
// OUTPUT:
//			vector< int > with random values in the range
//
auto	CreateRandomVector( const int kFrom, const int kTo, const int kNumOfTrials )					-> std::vector< int >
{
	// To generate random values we need:
	// (1) a random initialization object
    std::random_device rd;				
	// (2) a random engine 
	std::mt19937 mtRandomEngine( rd() );	// Mersenne twister MT19937? Why not?
	// (3) a distribution
	std::uniform_int_distribution uni_distr( kFrom, kTo );		// values between from_val and to_val

	std::vector< int >	random_decimals;	// will hold random integers

	// Generate kNumOfTrials random values through the lambda function joining 
	// uni_distr with mtRandomEngine. We use back_inserter since vector is empty.
	std::generate_n( back_inserter( random_decimals ), kNumOfTrials, [&](){ return uni_distr( mtRandomEngine ); } );
	
	return random_decimals;
}



///////////////////////////////////////////////////////////
// Unit test to randomly test both conversions
///////////////////////////////////////////////////////////
//
// INPUT:
//			kFrom, kTo - range of values to test
//			kNumOfTrials - a number of random test values
// OUTPUT:
//			true if all tests passed ok, false otherwise
//
// REMARKS:
//			Calls assert()
//
bool Decimal_2_Roman_Chain_UnitTest( const int kFrom = 1, const int kTo = 3999, const int kNumOfTrials = 1000 )
{
	// Check each random decimal if it converts ok
	for( const auto & val : CreateRandomVector( kFrom, kTo, kNumOfTrials ) )
		if(	ConvertRoman_2_DecimalNumber( ConvertDecimal_2_Roman( val ) ) != val )
			return false;

	return true;	// if here, then we passed all tests ;)
}




// Idea based on http://rosettacode.org/wiki/Roman_numerals/Encode#C.2B.2B



