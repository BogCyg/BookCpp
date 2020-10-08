/// ==========================================================================
//
// Software written by Boguslaw Cyganek (C) to be used with the book:
// INTRODUCTION TO PROGRAMMING WITH C++ FOR ENGINEERS
// Published by Wiley, 2020
//
// The software is supplied as is and for educational purposes
// without any guarantees nor responsibility of its use in any application. 
//
// ==========================================================================



#include <string>
#include <vector>
#include <algorithm>
#include <numeric> 
#include <iostream>
#include <iterator>
#include <random>

#include <cassert>

#include <array>
#include <time.h>

#include "range.h"

using namespace std;
using CppBook::range;


///////////////////////////////////////////////////////////////////////////////////


void Vector_Test_1( void )
{
	// ----------
	vector< int >		intVec;		// Create an empty vector

	cout << "intVec.size() == " << intVec.size() << endl;

	intVec.push_back( -13 );
	intVec.push_back( 0 );
	intVec.push_back( 1 );
	intVec.push_back( 13 );

	cout << "intVec.size() == " << intVec.size() << endl;

	// Find position of the element with value 0
	auto pos = find( intVec.cbegin(), intVec.cend(), 0 );
	if( pos != intVec.cend() )
		intVec.insert( pos, -1 );	// insert -1 before 0

	cout << "intVec.size() == " << intVec.size() << endl;

	for( auto elem : intVec )
		cout << elem << " ";	// Print all elements
	
	cout << endl;

	// Erase from beginning up to but excluding 0 element
	intVec.erase( intVec.begin(), find( intVec.cbegin(), intVec.cend(), 0 ) );	

	cout << "intVec.size() == " << intVec.size() << endl;

	for( auto elem : intVec )
		cout << elem << " ";	// Print them


	cout << endl << endl;

	// ----------
	vector< char >		monthDays { 31, 28, 31, 30, 31, 30, 
									31, 31, 30, 31, 30, 31 };

	// Print them out
	for( size_t i = 0; i < monthDays.size(); ++ i )
		cout	<< "Month " << i + 1 
				<< " has " << +monthDays[ i ] << " days" << endl;

	cout	<< "Total days = " 
			<< accumulate( monthDays.cbegin(), monthDays.cend(), 0 ) << endl;

	cout << endl;

	// ----------
	vector< double >	dobVec( 5, 0.0 );	// 5 elems with 0.0 value

	// Add 5 more and init ONLY the NEW ONES to 1.0
	dobVec.resize( 10, 1.0 );	

	// Another way to copy (print) all to the screen
	copy(	dobVec.cbegin(), dobVec.cend(), 
			ostream_iterator< double >( cout, " " ) );

	dobVec.clear();		// Remove all

	cout << endl << endl;
}

void Vector_Test_2( void )
{

	vector< int >	vec;
	for( int i = -5; i <= 5; ++ i )
		vec.push_back( i );


	vector< int >	neg_vec;

	// Copy all values up to 0
	copy(	vec.begin(), 
			find( vec.begin(), vec.end(), 0 ), 
			back_inserter( neg_vec ) );


	// Copy vec to cout
	cout << "vec : ";
	copy( vec.begin(), vec.end(), 
			ostream_iterator<int>( cout, " " ) );

	cout << endl << "Sum( vec ) = " 
		<< accumulate( vec.begin(), vec.end(), 0 ) << endl;

	// Copy neg_vec to cout
	cout << "neg_vec : ";
	copy( neg_vec.begin(), neg_vec.end(), 
			ostream_iterator<int>( cout, " " ) );


	cout << endl;
}



void Vector_Test_3( void )
{
	vector< unsigned int >	randVec( 10 );

	// Put some random values with Mersenne twister
	generate( randVec.begin(), randVec.end(), std::mt19937( std::random_device{}() ) );

	// Sort the values
	sort( randVec.begin(), randVec.end() );

	// Copy to the screen
	copy( randVec.begin(), randVec.end(), ostream_iterator< unsigned int >( cout, " " ) );
}






// ---------------------------------------------------


int String_Test_0( void )
{
	string str( "The quick" );
	str += " brown fox.";
	cout	<< str << "\nContains " 
			<< str.size() << " characters." << endl;
	return 0;
}


void String_Test_1( void )
{
	// ----------

	string str( "The quick" );
	str += " brown fox.";
	cout	<< str << "\nContains " 
			<< str.size() << " characters." << endl;


	// Count a number of lowercase letters
	int cnt_lowercase {};		// Set counter to 0
	for( auto c : str )
		if( islower( c ) )
			++ cnt_lowercase;

	cout << str << "\nLowercase = " << str.size() << endl;

	// ----------

	// Strings can be compared
//	cout << std::min( "Fox", "Dog" );	// oops, comparing addressess...
	cout << std::min( string( "Fox" ), string( "Dog" ) );	// ok, compare texts

	cout << endl << endl;

	// ----------

	// We create a vector of strings and enter the first one
	// To enter one \ we need to put \\  
	vector< string > paths { "C:\\Projects\\data.csv" };

	// Split full_path into path core and file name 
	string path_core, file_name;
	if( auto pos = paths[ 0 ].rfind( '\\' ); pos != string::npos )
	{
		paths.push_back( paths[ 0 ].substr( 0, pos ) );		// core path
		paths.push_back( paths[ 0 ].substr( pos + 1 ) );	// file name
	}

	for( auto & str : paths )	// Print all strings
		cout << str << endl;



	// ----------
	const vector< string >	textVec { "The ", "quick ", "brown ", "fox " };	
	

	string outMsg;	// empty text

	// Add i.e. concatenate all the elements together
	outMsg = accumulate( textVec.begin(), textVec.end(), outMsg );

	cout << outMsg << endl;


}



void String_Test_2( void )
{

	// ----------
	int file_cnt { 3 };	// Create a counter

	string base_file( "Data_no_" );
	base_file += to_string( file_cnt );
	base_file += ".txt";

	cout << "base_file : " << base_file << endl;

	// ----------




}



// -----------------------------------------------------




void ConstSizeArrayTest_1( void )
{
	// Create a fixed-size array - its first two
	// elements will get 1, 2,
	// the rest will be set to 0.
	array< int, 10 > arr = { 1, 2 };

	assert( sizeof( arr ) == arr.size() * sizeof( arr[ 0 ] ) );

	// Traverse and print all elements of array
	for( size_t i = 0; i < arr.size(); ++ i )
		cout << arr[ i ] << " ";

	cout << endl;
}

void ConstSizeArrayTest_2( void )
{
	const int kArrSize { 13 };
	array< unsigned int, kArrSize > theArray {};


	// Put some random values 
	generate( theArray.begin(), theArray.end(),  std::mt19937( std::random_device{}() ) );

	sort( theArray.begin(), theArray.end() );

	for( const auto e : theArray )
		cout << e << " ";

	cout << endl;


	// Make the same size as theArray
	array< double, theArray.size() > theDbArray;

	// Copy and convert int to double
	copy( theArray.begin(), theArray.end(), theDbArray.begin() );

	copy(  theDbArray.begin(), theDbArray.end(), ostream_iterator< double >( cout, " " ) );

	cout << endl;
}



void ConstSizeArrayTest_3( void )
{


	const int MyArrayDim { 10 };

	using MyArrayElem = int;

	using MyArray = std::array< MyArrayElem, MyArrayDim >;


	using UP_MA = std::unique_ptr< MyArray >;

	// Let's make a std::array on the heap
	UP_MA	up_ma( std::make_unique< MyArray >() );


	// Let's make a const pointer to non-const in, so we can write to it
	MyArrayElem * const ma_begin	= & (*up_ma)[0];
	MyArrayElem * const ma_end		= ma_begin + up_ma->size();

	for( auto & a : * up_ma )
		a = 0;

	copy( ma_begin, ma_end, ostream_iterator< MyArrayElem >( cout, " " ) );

	cout << endl;

	fill( ma_begin, ma_end, 3 );

	copy( ma_begin, ma_end, ostream_iterator< MyArrayElem >( cout, " " ) );

	cout << endl;

}



void ConstSizeArrayTest_4( void )
{


	enum ArrayDims { kCols = 3, kRows = 2 };

	using ArrayElem = double;

	// Declare a single array of kCols elems
	using _1D_Array = std::array< ArrayElem, ArrayDims::kCols >;

	// Declare a matrix with kRows
	using _2D_Array = std::array< _1D_Array, ArrayDims::kRows >;


	_2D_Array	matrix { 0.0 };		// Create a matrix and init with zeros

	double val { 0.0 };		// Initial value

	// Initialize matrix with increasing values
	for( auto & r : matrix )
		for( auto & c : r )
			c = val ++;		// Each element gets 1 higher value

	val = 0.0;				// Reset

	// Make the same initialization with subscripts
	for( _2D_Array::size_type r = 0; r < matrix.size(); ++ r )
		for( _2D_Array::size_type c = 0; c < matrix[ 0 ].size(); ++ c )
			matrix[ r ][ c ] = val ++;


	// Display the matrix
	for( const auto & r : matrix )
	{
		for( const auto & c : r )
			cout << c << " ";

		cout << endl;
	}



}





// -----------------------------------------------------

/* A size of an array can be found with the sizeof as follows */
#define ARR_SIZE(tab)	( sizeof( tab ) / sizeof( tab[0] ) )


void BuiltIn_ArrayTest_1( void )
{
	//const int kArrSize = 12;
	enum Dim { kArrSize = 4 };		/* Works in C and C++ */
	int arr[ kArrSize ] = { 0 };	/* Init all elems to 0 */

	/* Set new values to arr */
	for( int i = 0; i < kArrSize; ++ i )
		arr[ i ] = i;

	/* arr is a const pointer to its first element, */
	/* so we can write also this */
	for( int i = 0; i < kArrSize; ++ i )
		* ( arr + i ) = i;

	int sum = 0;
	for( int i = 0; i < ARR_SIZE( arr ); ++ i )
		sum += arr[ i ];

	cout << endl << endl;
}




void BuiltIn_ArrayTest_2( void )
{
	/* Multi-dimensional arrays */
	enum Dims { kRows = 2, kCols = 2 };

	/* kRows is external, kCols internal index */ 
	double affineMatrix[ kRows ][ kCols ] { 0.0 };

	/* Set all off-diagonal elements to -1 */
	for( int r = 0; r < kRows; ++ r )
		for( int c = 0; c < kCols; ++ c )
			if( r != c )
				affineMatrix[ r ][ c ] = -1.0;

	/* The same with pointers */
	for( int r = 0; r < kRows; ++ r )
		for( int c = 0; c < kCols; ++ c )
			if( r != c )
				* ( * ( affineMatrix + r ) + c ) = -1.0;


}


void BuiltIn_ArrayTest_3( void )
{
	/* Arrays with char - texts */

	char text[] = "Dog";

	const char * textArr[] = { "The", "quick", "fox" };



}



// -----------------------------------------------------












