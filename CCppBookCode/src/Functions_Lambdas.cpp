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
#include <utility>
#include <algorithm>
#include <chrono>

#include <time.h>

#include "range.h"

using namespace std;	// Open the whole std since we use many objects in this source


using CppBook::range;


///////////////////////////////////////////////////////////////////////////////////


void SimpleLambda_TestFun( void )
{

	// This is lambda closure
	auto cm_2_in = 
		// This is lambda expression
		[] ( const double cm ) { return 2.54 * cm; };



	cout << "Enter cm: "; 

	double val {};
	cin >> val;

	// Call lambda expression
	cout << " = " << cm_2_in( val ) << " in" << endl;

}


void LambdaTestFun_0( void )
{
	vector< int >	vec;


	// Is it ok?
	//auto rand = [] ( const int from = 1, const int to = 1000 ) { return ( uniform_int_distribution<>( from, to ) )( default_random_engine( (random_device())() ) ); };

	//auto gen = bind(normal_distribution<double>{15,4.0},default_random_engine{});		// from Stroustrup



	// Insert 10 random values to vec
	generate_n( back_inserter( vec ), 10, rand );

	// Print only if element less than 100
	copy_if( vec.begin(), vec.end(), ostream_iterator< int >( cout, " " ), [] ( auto x ) { return x < 100; } );


	cout << endl;
}



void LambdaTestFun_1( void )
{
	// Fill array with odd values
	const int k_elems = 10;
	array< int, k_elems >	odd_vals {};	// fill all with 0 

	// Fill odd_vals with odd values
	char counter {};
	transform( odd_vals.begin(), odd_vals.end(), odd_vals.begin(), 
			// Caption [& counter] used to pass counter by reference
			// auto & is an empty placeholder for the argument passed by transform
			[& counter]( auto & ){ return 2 * counter ++ + 1; } 
	);

	// Print all chars
	copy( odd_vals.begin(), odd_vals.end(), ostream_iterator< int >( cout, " " ) );

	cout << endl;

}


void LambdaTestFun_2( void )
{
	// Generate random identifiers

	// Chars used to generate passwords
	const vector< string > rand_strings
		{	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
			"abcdefghijklmnopqrstuvwxyz",
			"0123456789_@&#"
		};


	std::srand( (unsigned int) time( 0 ) );		// seed random generator 

	// Generated value can be from 0 .. max_val-1
	// We could use default caption [=] to access RAND_MAX;
	// However, a better way is to create a local copy rm
	// via the "init capture" (generalized captures).
	// -> int to explicitly convert return value from double to int
	auto rand_index = [ rm = RAND_MAX ] ( const int max_val ) -> int 
	{ 
		return	static_cast< double >( std::rand() * max_val )	// static_cast to make
			/	static_cast< double >( rm + 1 );				// division on double
	};


	// 
	// Let's generate a few exemple passwords ...
	const int kPswdToGenerate { 10 };
	for( int cnt = kPswdToGenerate; cnt > 0; cnt -- )
	{

		string pwd;

		// Insert kPasswordLen random chars via lambda function
		const int kPasswordLen = 8;
		generate_n	(	back_inserter( pwd ), kPasswordLen, 

			// -------------------------------------------------------------
			// Use lambda which calls another lambda passed by reference 
			// However, avoid default [&]
			[ & rand_strings, & rand_index ] () 
			{ 
				const auto & s = rand_strings[ rand_index( rand_strings.size() ) ]; 
				return s[ rand_index( s.size() ) ];
			} 
			// -------------------------------------------------------------
		);

		cout << "Proposed password: " << pwd << endl;
	}

}



void LambdaTestFun_3( void )
{
	// Generate random identifiers
	class PswdGen
	{
		// Chars used to generate passwords
		const vector< string > rand_strings
			{	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
				"abcdefghijklmnopqrstuvwxyz",
				"0123456789_@&#"
			};

	public:

		PswdGen( void )
		{
			srand( (unsigned int) time( 0 ) );		// seed random generator 
		}

		// kPasswordLen defines 
		string	operator() ( const int kPasswordLen = 8 )
		{
			// Generated value can be from 0 .. max_val-1
			// Caption [=] to access RAND_MAX
			// -> int to explicitly convert return value from double to int
			auto rand_index = [=] ( const int max_val ) -> int 
			{ 
				return	static_cast< double >( rand() * max_val ) 
					/	static_cast< double >( RAND_MAX + 1 ); 
			};

			string pwd;

			// Insert kPasswordLen random chars via lambda function
			generate_n	(	back_inserter( pwd ), kPasswordLen, 

							// -------------------------------------------------------------
							// Use lambda which calls another lambda passed by reference [&]
							[this, & rand_index] () 
							{ 
								const auto & s = rand_strings[ rand_index( rand_strings.size() ) ]; 
								return s[ rand_index( s.size() ) ];
							} 
							// -------------------------------------------------------------
						);

			return pwd;
		}
	
	};


	//srand( time( 0 ) );

	// 
	// Let's generate a few exemple passwords ...
	for( int cnt = 10; cnt > 0; cnt -- )
	{
		cout << "Proposed password: " << PswdGen()() << endl;
	}

}





///////////////////////////////////////////////////////////////////////////////////

// SCUBA classes student information
struct StudentInfo
{
	wstring		fFirstName;	
	wstring		fFamilyName;

	int			fAge {};

	enum class SCUBA_Cert { kOpenWater, kAdvanced, kMaster, kInstructor };

	SCUBA_Cert	fCert { SCUBA_Cert::kOpenWater };
};




// We need to tell how to display StudentInfo
wostream & operator << ( wostream & o, const StudentInfo & s )
{
	const vector< wstring > SCUBA_Cert_Names { L"OpenWater", L"Advanced", L"Master", L"Instructor" };	

	o << s.fFirstName << L" ";
	o << s.fFamilyName << L",\t";
	o << s.fAge << L"\t";
	o << SCUBA_Cert_Names[ static_cast< size_t >( s.fCert ) ] << L" ";

	return o;
}


// Let's create a SCUBA class 
vector< StudentInfo >		SCUBA_Class {

	{ L"Phil", L"Curtis",	18,  StudentInfo::SCUBA_Cert::kAdvanced },
	{ L"Kamil", L"Cyganek", 15,  StudentInfo::SCUBA_Cert::kOpenWater },
	{ L"John", L"Kowalski", 23,  StudentInfo::SCUBA_Cert::kOpenWater },
	{ L"Michal", L"Brajta", 61,  StudentInfo::SCUBA_Cert::kInstructor },
	{ L"Anna", L"McLaghlan",18,  StudentInfo::SCUBA_Cert::kAdvanced },
	{ L"Bog", L"Cyganek",	49,  StudentInfo::SCUBA_Cert::kInstructor },
	{ L"Megan", L"Plant",	26,  StudentInfo::SCUBA_Cert::kMaster }

};


void SCUBA_Course( void )
{
	wcout << endl << L"Sorted by family name:" << endl;

	// -------------------
	// Sort by family name
	sort( SCUBA_Class.begin(), SCUBA_Class.end(), 
		[] ( const StudentInfo & a, const StudentInfo & b ) { return a.fFamilyName < b.fFamilyName; } );
	// Print them on the screen
	copy( SCUBA_Class.begin(), SCUBA_Class.end(), 
		ostream_iterator< StudentInfo, wchar_t >( wcout, L"\n" ) );

	wcout << endl << L"Sorted by age:" << endl;

	// -----------
	// Sort by age
	sort( SCUBA_Class.begin(), SCUBA_Class.end(), 
		[] ( const auto & a, const auto & b ) { return a.fAge < b.fAge; } );
	// Print them on the screen
	copy( SCUBA_Class.begin(), SCUBA_Class.end(), 
		ostream_iterator< StudentInfo, wchar_t >( wcout, L"\n" ) );

	wcout << endl << L"Instructors in the group:" << endl;

	// Find all with a given certificate
	const auto cert = StudentInfo::SCUBA_Cert::kInstructor;
	copy_if( SCUBA_Class.begin(), SCUBA_Class.end(), 
		// [ cert ] caption to access a copy of cert
		ostream_iterator< StudentInfo, wchar_t >( wcout, L"\n" ), 
		[ cert ] ( const auto & a ) { return a.fCert == cert; } );

	wcout << endl << endl;
}



///////////////////////////////////////////////////////////////////
// Variadic template example




// 0th function in the series
auto & multi_print_helper( ostream & o, const string sep )
{
	return o;
}

// First function in the series
template < typename T >
auto & multi_print_helper( ostream & o, const string sep, const T & val )
{
	o << val << sep;
	return o;
}

// A template function accepting an arbitrary number of parameters
template < typename T, typename ... Args >
auto & multi_print_helper( ostream & o, const string sep, const T & val, Args... args )
{
	o << val << sep;

	// Recursively call 
	return multi_print_helper( o, sep, args... );
}


void multi_print_helper_test( void )
{
	// Make a log file 
	ofstream log_file( "log_file.txt" );

	// A helper variadic lambda that joins multi_print_helper with the log file
	auto diagnostic_print = [ & log = log_file ] ( auto... params ) -> ostream &
	{	// Each output separate with " ", then add end-of-line
		return multi_print_helper( log, " ", params ... ) << endl;
	};


	int x { 1 }; double y { 2.0 }; string z { "three" };

	// Output as many objects of arbitrary type to the log file
	diagnostic_print( x, y, z );

	diagnostic_print( x, y, z, "Text", x == y, 5.0 );


	// This can be still used to output to the standard cout
	multi_print_helper( cout, ", ", x, y, z, "Text", x == y, 5.0 );
}



// -------------------------------------------



// All created tuples will be logged to a file
template < typename ... Args >
auto make_tuple_and_log( Args && ... vargs )
{
	multi_print_helper( ofstream( "mmpp.txt", ios::app ), "\t", vargs ... ) << endl;
	return make_tuple( vargs ... ); // Call stl::make_tuple
}



void TestMakeTuple( void )
{
	auto t0( make_tuple_and_log( 2, "A", 3.0 ) );

	auto t1( make_tuple_and_log( 4, "B" ) );

	auto t2( make_tuple_and_log() );

	// do somethign with tuples 

}




// -------------------------------------------





