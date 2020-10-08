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
#include <iomanip>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstring>	// for memset
#include <string>
#include <limits>	// for basic types' limits

#include <cmath>	// for math function


#if _WIN32
	// To display wchar we need this in Windows
	#include <io.h>
	#include <fcntl.h>
#endif


// ----------------------------------------------------




using std::cout, std::endl, std::numeric_limits;

// ----------------------------------------------------


void BasicTypes_Examples( void )
{
	// Create and init c
	char c { 'Y' };

	std::cout << "Press N to exit" << endl;
	std::cin >> c;	

	// Operator == to compare, || is logical OR
	bool exit_flag = c == 'N' || c == 'n';
	if( exit_flag )
		return;		// Exit now


	int x { 100 };	// Create x and set 100

	x = 0x64;			// in hex (leading 0x)
	x = 0144;			// in octal (leading 0)
	x = 0b01100100;		// as binary (0b, C++14+)


	// Set to 1111111...111
	// Operator ~ negates all bits
	// 0UL is an unsigned long version of 0
	unsigned long light_register { ~ 0UL };	


	std::cout << "Enter value \n";
	// Create double and init with 0.0 (0 is int)
	double val { 0.0 };		

	std::cin >> val;
	if( val >= 0.0 )
	{
		std::cout << "sqrt( " << val << " ) = " 
			<< sqrt( val ) << endl;
	}
	else
	{
		std::cout << "Negative value" << endl;
	}


	// Unicode letter
	wchar_t		w_letter { L'A' };

	// Its memory size in bytes
	size_t	w_letter_bytes = sizeof( w_letter );

	// wcout is necessary to display Unicode
	std::wcout << w_letter << L" bytes = " 
			<< w_letter_bytes << std::endl;
}


using std::wcout, std::endl, std::wstring, std::vector, std::make_unique;


void MoreOnBasicTypes( void )
{
	// Print basic facts about char
	cout << "bytes of char = " << sizeof( char ) << endl; 
	cout << "char lowest = " << +numeric_limits< char >::lowest() << endl; 
	cout << "char min = " << +numeric_limits< char >::min() << endl; 
	cout << "char max = " << +numeric_limits< char >::max() << endl; 


	// Print basic facts about int
	cout << "bytes of int = " << sizeof( int ) << endl; 
	cout << "int lowest = " << numeric_limits< int >::lowest() << endl; 
	cout << "int min = " << numeric_limits< int >::min() << endl; 
	cout << "int max = " << numeric_limits< int >::max() << endl; 

	// Check whether long is long enough to store 11 digits values
	const int bits_in_byte = 8;
	bool longFitFlag = ( std::log( 99999999999.0 ) / std::log( 2.0 ) + 1 ) 
						< sizeof( long ) * bits_in_byte - 1;

	cout	<< "We " << ( longFitFlag ? "can" : "cannot" ) 
			<< " store 11 digits using the long type" << endl;

#if _WIN32
	// We need this in Windows to print Unicode characters in the console window
	auto old_console_mode =	_setmode( _fileno(stdout), _O_U16TEXT );
#endif

	wchar_t pl_letter = L'¥';
	wcout << pl_letter << L" needs " << sizeof( pl_letter ) << L" bytes." << endl;
	
	wstring holiday_pl( L"œwiêto" );

	// We cannot use sizeof here - we need to call size()
	size_t holiday_pl_len = holiday_pl.size();

	wcout << holiday_pl << L" has " << holiday_pl_len << L" characters\n";

#if _WIN32
	// Restore the previous mode of the console 
	setmode( _fileno(stdout), old_console_mode );
#endif

}




// ----------------------------------------------------


void VariablesConstWithInitialization( void )
{
	// ------------------------
	{
		// Vars and const initialized with {}
		int x {};	// Create x and set to 0
		x += 1;		// Can increase by 1

		// Create const y and set to 100 - cannot change
		const int y { 100 };
		//y += 1;		// Error, cannot change constant

		// Create c and set to ASCII code of 'A'
		char c { 'A' };
		// Can display on the screen
		std::cout << "c = " << c << std::endl;

		// A variable of floating arithmetics
		double radius { 2.54 }; 

		// Create const kPi of floating type
		const double kPi { 3.141592653589 };
		// Compute and display area
		std::cout << "Area = " << kPi * radius * radius;

		bool flag { true };	// A logical var init to true

	}


	{
		// ------------------------
		// Vars and const initialized with ()
		//int x();	// z is int and set to 0?? No !! 
		int x ( 0 ); // Create x and set to 0
		x += 1;		 // Can increase by 1

		int y( 100 );	// Ok, var x with 100
		y += 1;

		// A variable of floating arithmetics
		double radius ( 2.54 ); 

		// Create const kPi of floating type
		const double kPi ( 3.141592653589 );
		// Compute and display area
		std::cout << "Area = " << kPi * radius * radius;

		bool flag ( true );	// A logical var init to true
	}



	{
		// ------------------------
		// Vars and const initialized with assignment =
		int x = 0; // Create x and set to 0
		x += 1;		 // Can increase by 1

		// A variable of floating arithmetics initialized
		// from an initialization list
		double radius = { 2.54 }; 

		// Create const kPi of floating type
		const double kPi = 3.141592653589;
		// Compute and display area
		std::cout << "Area = " << kPi * radius * radius;	
	
		bool flag = true;	// A logical var set to true
	}

}




// ----------------------------------------------------

// a global var - even if not initialized 
// will be set to 0
int		var;	

void var_test_fun( void )
{
	int var = -1;				// hides global "var"
	cout << var  << endl;		// prints -1

	// {} block opens new scope and a local stack
	{
		int var = 3;			// hides two previous "var"
		cout << var << endl;	// prints 3
	}	// here the inner "var" will be deleted

	var = ::var;			// set "var" with a value of the global "var"
	cout << var  << endl;		// prints 0
}


// ----------------------------------------------------


// Example of using static in a function.
// No matter how many times we call this funtction
// it will display only N times.
void do_action_N_times( const int N, const int to_display )
{
	// This static is alive through the program lifetime.
	// It can be accessed only from withing this function.
	// This static will be initialized to N only ONCE.
	static int n_counter = N;		
	
	// Allow action at most N times, no matter how many
	// times we call this function.
	if( n_counter > 0 )
	{
		-- n_counter;	// decrement by 1
		cout << to_display << endl;
	}
}


void do_action_test( void )
{
	const int kIterations = 1000;
	const int kNumOfActions = 5;

	for( int k = 0; k < kIterations; ++ k )
		do_action_N_times( kNumOfActions, k );
}



// ----------------------------------------------------


// An example of the static linkage 


// file_a.cpp

int x = 5;			// global scope

static int y = 7;	// static - scope only in translation unit
					// behaves like a global but only in this unit


// file_b.cpp

extern int x;

extern int y;		
// trying to use "y" will generate 
// a linker error (LNK2001: unresolved external symbol "int y")



// ----------------------------------------------------

#include <memory>

void HeapAllocExample( void )
{
	// Define a smart pointer large_buffer containing 100000 bytes
	// allocating on the heap.
	const auto	kSize { 100000 };
	auto		large_buffer( make_unique< unsigned char [] >( kSize ) );

	// Initialize the buffer to 0
	std::memset( large_buffer.get(), 0, kSize );

	large_buffer[ 0 ] = 'A';
	// Do something with large_buffer
	// ...


	// large_buffer is a local object, so it will be automatically 
	// destroyed at the exit of this function - thanks to this
	// it will destroy also the buffer of 100000 bytes
}




// ----------------------------------------------------
// auto examples


void auto_test( void )
{

	{
		int x { 0 };

		double y { 0.0 };

		cout << "x=" << x << endl;
		cout << "y=" << y << endl;
	}


	{
		auto x { 0 };

		auto y { 0.0 };

		cout << "x=" << x << endl;
		cout << "y=" << y << endl;
	}

	{
		// An object x of type char 
		// because 'c' is a constant char
		auto x { 'c' };

		// Let's define a vector with elements of the same type as object x
		vector< decltype( x ) >		vec( 10, x );
	
		// Print all characters on the screen - k will be char type
		for( auto k : vec )
			cout << k;

		cout << endl;

		// The same with explicit type
		for( char k : vec )
			cout << k;

		cout << endl;

		// Now k will be const char type
		for( const auto k : vec )
			cout << k;
	
		cout << endl;


		// Now k will be const char reference type
		for( const auto & k : vec )
			cout << k;
	
		cout << endl;


		// By using auto we avoid searching for an exact type
		// and unwanted type conversions.
		auto vec_size { vec.size() };

		cout << "vec_size=" << vec_size << endl;
	}


	{
		auto text { "The quick brown fox" };
	
		// What type is text? Do we need to know?
		cout << text << endl;
	}


}





// ----------------------------------------------------




