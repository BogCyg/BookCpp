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



#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <array>
#include <random>
#include <fstream>
#include <tuple>
#include <thread>
#include <cstdint>
#include <utility>
#include <cassert>
#include <chrono>
#include <ctime>
#include <functional>
#include <regex>
#include <list>
#include <concepts>


#include "range.h"
#include "PointFor.h"

using namespace std;

using CppBook::range;


///////////////////////////////////////////////////////////////////////////////////


void my_simple_thread( uint64_t param )
{
	cout << "I'm thread no: " << param << endl;
}

void ThreadTest( void )
{

	const auto	num_of_threads = 10;

	vector< thread >	threadPool;

	for( auto i = 0; i < num_of_threads; ++ i )
	{
		threadPool.emplace_back( my_simple_thread, i );
	}

	// run them and join
	for( auto & th : threadPool )
		th.join();


}


////////////////////////////////////////////////////////////////



void regex_test_ext( void )
{
	// input stream

	//string str( "0001010102001100" );

	//string str( "12312312312345454545454545" );

	//string str( "<city>New York</city>" );

	//string str( "jan.koczwara_12@agh.edu.pl" );

	string str( "normalize_L1( matrix );" );



	cout << str << endl;

	// R"(   )"		for raw string
	regex	e_mail_pat( R"(([[:alnum:]._]+)@([[:alnum:]._]+)\.([[:alnum:]]+))" );
	
	regex	pat_0( R"(([[:alnum:]._]+)@([[:alnum:]._]+))" );

	regex	pat_1( R"(.+)" );

	regex	pat_2( R"(^.*$)" );

	regex	pat_3( R"((01)+)" );

	regex	pat_4( R"((01)+?)" );

	regex	pat_5( R"([01]+)" );

	regex	pat_6( R"([^01]+?)" );

	regex	pat_7( R"((123){2}(45){3})" );

	regex	pat_8( R"(<(.+)>(.+)</\1>)" );

	regex	pat_9( R"([[:alpha:]_][[:alnum:]_]*)" );

	regex	pat_10( R"([[:w:]]+([[:upper:]]+)[[:w:]]+)" );


	regex	pat = pat_10;


	//                                   where   result(s)   what
	if( smatch	match_res; regex_search( str,    match_res,  pat ) )
		for( auto m : match_res )
			cout << m << endl;


}




void regex_test( void )
{
	// input stream
	string str( "jan.koczwara_12@agh.edu.pl" );
	cout << str << endl;

	// R"(   )"		for a raw string
	regex	pat( R"(([[:alnum:]._]+)@([[:alnum:]._]+)\.([[:alnum:]]+))" );

	//                                   where   result(s)   what
	if( smatch	match_res; regex_search( str,    match_res,  pat ) )
		for( auto m : match_res )
			cout << m << endl;
}




/////////////////////////////////////////////////////////////////////



#include <iomanip>


// ios manipulator
void ios_manip_test( void )
{
	double e = exp( 1.0 );		// e value, default precision is 6

	cout << "[defaultfloat]        e = " << e << endl;

	cout << "[sc]                  e = " << std::scientific << e << endl;
	
	cout << "[fx]                  e = " << std::fixed << e << endl;

	cout << "[p=4]                 e = " << std::setprecision( 4 ) << e << endl;

	cout << "[w=10]                e = " << std::setw( 10 ) << e << endl;

	cout << "[fx][w=14][p=12]      e = " << std::fixed << std::setw( 14 ) << std::setprecision( 12 ) << e << endl;

	cout << "[fil_][fx][w=10][p=4] e = " << std::setfill( '_' ) << std::fixed << std::setw( 10 ) << std::setprecision( 4 ) << e << endl;


	// -----------------

	cout << "100d = " << 100 << " dec" << endl;
	cout << "100d = " << std::hex << 100 << " hex" << endl;
	cout << "100d = " << std::setbase( 8 ) << 100 << " oct" << endl;
	cout << "100d = " << std::dec << 100 << " dec" << endl;

}





/////////////////////////////////////////////////////////////////////



// Good and bad data types
void Fahrenheit2Celsius( void )
{

	double TF { 100.0 };
	double TC {};

	TC = ( TF - 32 ) * ( 5 / 9 );
	cout << TF << " Fahrenheit = " << TC << " Celsius" << endl;

	TC = ( TF - 32.0 ) * ( 5.0 / 9.0 );
	cout << TF << " Fahrenheit = " << TC << " Celsius" << endl;

}

/////////////////////////////////////////////////////////////////////

// Computes the square root in the integer domain.
// The computations are done by bisection, i.e.
// in consecutive steps the search region is split
// into halves and the closets assessment is selected.
unsigned int	IntSqrt( const unsigned int x )
{
	// Set the search range
	unsigned int low_bnd { 1 };
	unsigned int up_bnd { x >> 1 };	// x / 2

	//do
	while( up_bnd >= low_bnd )
	{
		// Compute the middle point
		unsigned int mid_val = ( low_bnd + up_bnd ) >> 1;
	
		// Check where is the middle point
		// and narrrow the search range
		if( mid_val * mid_val > x )
			up_bnd = mid_val - 1;
		else
			low_bnd = mid_val + 1;
	
	} //while( up_bnd >= low_bnd );

	//return low_bnd /*- 1*/;
	return ( low_bnd + up_bnd ) >> 1;
}



// Computes the square root in the integer domain.
// The computations are done by bisection, i.e.
// in consecutive steps the search region is split
// into halves and the closets assessment is selected.
double	FP_Sqrt_Approx( const double x )
{
	// Set the search range
	auto low_bnd { 1.0 };
	auto up_bnd { x / 2.0 };	// x / 2

	const double kStep = 0.001;

	do
	{
		// Compute the middle point
		auto mid_val = ( low_bnd + up_bnd ) / 2.0;

		// Check where is the middle point
		// and narrrow the search range
		if( mid_val * mid_val > x )
			up_bnd = mid_val - kStep;
		else
			low_bnd = mid_val + kStep;

	} while( up_bnd >= low_bnd );

	return ( low_bnd + up_bnd ) / 2.0;
}


/////////////////////////////////////////////////////////////////////




// Recursiver version of the integer sqrt
unsigned int IntSqrt_Rec_FunObj( unsigned int x )
{

	std::function< unsigned int ( unsigned int, unsigned int, unsigned int ) > Inner_IntSqrt_Rec = 
		
		[ & ] ( unsigned int x, unsigned int low_bnd, unsigned int up_bnd )
		{
			unsigned int mid_val = ( low_bnd + up_bnd ) >> 1;

			if( low_bnd > up_bnd )
				return mid_val;			// stop condition

			return x < mid_val * mid_val  ?	Inner_IntSqrt_Rec( x, low_bnd, mid_val - 1 ) : 
											Inner_IntSqrt_Rec( x, mid_val + 1, up_bnd );
		};

	return Inner_IntSqrt_Rec( x, 1, x >> 1 );

}

unsigned int IntSqrt_Rec_Lambda( unsigned int x )
{

	const auto Inner_IntSqrt_Rec = 

		[ & ] ( const auto & self, unsigned int x, unsigned int low_bnd, unsigned int up_bnd ) -> unsigned int
	{
		unsigned int mid_val = ( low_bnd + up_bnd ) >> 1;
		
		if( low_bnd >/*=*/ up_bnd )
			return mid_val;			// stop condition

		return x < mid_val * mid_val  ?	self( self, x, low_bnd, mid_val - 1 ) : 
			self( self, x, mid_val + 1, up_bnd );
	};



	return Inner_IntSqrt_Rec( Inner_IntSqrt_Rec, x, 1, x >> 1 );
}





// -----------------------------------------------------------




// A class with constexpr constructor and function 
class Rectangle 
{ 
	int _h, _w; 
public: 
	// A constexpr constructor 
	constexpr Rectangle (int h, int w) : _h(h), _w(w) {} 
	
	constexpr int getArea () const { return _h * _w; } 
}; 

// driver program to test function 
int xxmain() 
{ 
	// Below object is initialized at compile time 
	constexpr Rectangle obj(10, 20); 
	cout << obj.getArea(); 
	return 0; 
} 



// ------------------------------------------------


// Some hints on reflections


//#include <experimental/reflect>

class TBook
{
	string	fAuthor;
	string	fTitle;
	int		fPubYear {};

public:

	TBook( const string & author, const string & title, const int year)
		: fAuthor( author ), fTitle( title ), fPubYear( year )
	{
	}
	// ...

	//virtual auto reflect( void ) const -> std::tuple< const string &, const string &, const int & > 
	//{
	//	return std::tie( fAuthor, fTitle, fPubYear );
	//}
	auto reflect( void ) const
	{
		return std::tie( fAuthor, fTitle, fPubYear );
	}

};




bool operator == ( const TBook & a, const TBook & b )
{
	return a.reflect() == b.reflect();
}


bool operator < ( const TBook & a, const TBook & b )
{
	return a.reflect() < b.reflect();
}


void ReflectTest( void )
{
	TBook	technical( "How to fix a refrigerator", "Home", 2019 );
	TBook	Cpp( "Introduction to Programming with C++", "Wiley", 2020 );



	bool can_compare_books = technical == Cpp;

	bool lower_book = technical < Cpp;


}





void TransformTest( void )
{
	// Convert texts into absolute values and display
	vector< string >	str_vec { "10", "12", "-13.13" };
	vector< double >	dbl_vec;

	transform(	str_vec.begin(), str_vec.end(),		// src from-to
				back_inserter( dbl_vec ),			// dst from
				[] ( auto & s ) { return fabs( stod( s ) ); } );	// fun

	copy(	dbl_vec.begin(), dbl_vec.end(), 
			ostream_iterator< double >( cout, "\n" ) );
}


// -----------------------------------------------------------------



///////////////////////////////////////////////////////////
// Bubble sort (in situ)
///////////////////////////////////////////////////////////
//		
// INPUT:	vec - a reference to the vector of integers
//		
// OUTPUT:	none
//		
// REMARKS:	vec will be sorted in the ascending order
//		
void BubbleSort( std::vector< int >	& vec )
{
	auto swapped { true };

	for( auto i { 1 }; swapped && i < vec.size(); ++ i )
	{
		swapped = false;

		for( auto j = vec.size() - 1; j >= i; -- j )
		{
			if( vec[ j - 1 ] > vec[ j ] )
			{
				// swap them
				auto tmp = vec[ j - 1 ];
				vec[ j - 1 ] = vec[ j ];
				vec[ j ] = tmp;

				swapped = true;
			}
		}
	}
}

void BubbleSortTest( void )
{
	auto	CreateRandomVector( const int kFrom, const int kTo, const int kNumOfTrials ) -> vector< int >;

	auto	rand_int_vec { CreateRandomVector( 0, 255, 13 ) };

	std::cout << "\nThe random vector before sorting\n";
	copy( rand_int_vec.begin(), rand_int_vec.end(), ostream_iterator< int >( std::cout, ", " ) );

	BubbleSort( rand_int_vec );

	std::cout << "\nThe random vector after sorting\n";
	copy( rand_int_vec.begin(), rand_int_vec.end(), ostream_iterator< int >( std::cout, ", " ) );

}





// -----------------------------------------------------------------

#if 0

template< typename T >
concept has_bool_value_member = requires { { T::value } -> std::convertible_to< bool >; };

template< typename T >
concept exclusively_unsigned  = requires { std::unsigned_integral< T >; };

#endif

// -----------------------------------------------------------------


