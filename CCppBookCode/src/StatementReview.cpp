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
#include <fstream>
#include <cassert>
#include <vector>
#include <array>
#include <string>
#include <utility>
#include <algorithm>

#include <cmath>
#include <ctype.h>

// Introduce the range class to facilitate range for
#include "range.h"	// "" are for user-created headers



using std::cout, std::cin, std::endl, std::cerr;
using std::vector, std::string;
using std::ofstream, std::ifstream;

using CppBook::range;


// 4.14.1		Blocks of Statements and Access to Variables



#include <chrono>
#include <iostream>


 // a function that returns 'auto' cannot be used before it is defined
// A function to find prime numbers
vector< int > EratosthenesSieve( const int val )
{
	// Create a "marker" vector. Each value with "false"
	// after computations is a prime number. 
	// At the beginning fill all values with "false"
	vector< bool >	values( val, false );	// create a vector 

	// This is our vector to return primem numbers
	vector< int >	primes;		// at the beggining it is empty

	// Now traverse the array and find out all primes by marking all multiples
	for( int i = 2; i < val /*sqrt( val )*/; ++ i )
	{
		if( values[ i ] == false )
		{
			primes.push_back( i );		// put next prime to our basket

			for( int j = i + i; j < val; j += i )	// e.g. 7 => 2*7, 3*7, 4*7, ...
				values[ j ] = true;
		}
	}

	return primes;
}


// Returns a vector with Fibonacci numbers up to max_val
vector< int >	FibonacciNumbers( const int max_val )
{
	vector< int >	fibo_num_vec;

	int a = 0, b = 1;
		
	while( a < max_val )
	{
		fibo_num_vec.push_back( a );	

		int tmp = a;	// a temporary to exchange a and b

		a = b;			// a becomes "old" b
		b = tmp + b;	// b becomes a sum of "old" a and b
	}

	return fibo_num_vec;
}



namespace CppBook
{
	// Defines an RGB pixel with three byte values
	class RGB_Pixel
	{
		public:

			enum EColor 
			{ 
				kRed, kGreen, kBlue 
			};	

			unsigned char GetRed( void ) const { return fData[ kRed ]; }
			// ...

		private:	

			// An array with 3 byte values
			std::array< unsigned char, kBlue + 1 >	fData;
	};


}	// No ; when closing a namespace (namespace can be split in many places)




namespace CppBook
{

	class AlgorithmClass		// should contain operator()
	{
		public:

			virtual void operator () ( void );
	};

	class AlgPerformanceMeter
	{
		public:



			auto operator() ( AlgorithmClass & alg, const int iterations = 1 )
			{
				using timer = std::chrono::high_resolution_clock;
			
				auto time_start = timer::now();
				  
					// Run an algorithm a number of iterations 
					for( auto i : range( iterations ) )
						alg();

				auto time_end = timer::now();

				auto duration = time_end - time_start;

				return std::chrono::duration_cast< std::chrono::milliseconds >( duration );
			
			}

	
	};




}	// no ;






namespace CppBook
{


void CondStatements( void )
{


	{
		double val {};
		cin >> val;						// read val from keyboard

		if( val > 0.0 )					// if val larger than 0.0
			cout << std::log( val );	// output natural logarithm of val
		else
			cout << "Error - Negative argument" << endl;
	
	
	}



	{
	
		bool flag = false;									// define a flag
		char c = 'Y';										// define variable
		cout << "Proceed with computations? (Y/N)" << endl;	// ask the user
		cin >> c;											// get answer

		if( c == 'Y' )
		{
			cout << "Continue" << endl;		// "Yes"
			flag = true;
		}
		else
		{
			cout << "Stop" << endl;			// "No"
			flag = false;
		}

		// continue computations if flag == true ...
	
	}


	{
	
		// is_open returns bool (true if ok)
		if( ofstream outFile( "Log.txt"); outFile.is_open() )
		{
			outFile << "Operation successful" << endl;
		}
	
		
	}

}



// A function that reads a video and converts into a tensor object 
string GenerateTensorFromVideo( const string & videoPath, 
								const string & outFileName = string(""), 
								const string & outFileExt = string("") );

int _main( int argc, char ** argv )
{
	string outMsg;
	switch( int x {}; argc )
	{
		case 2:
			outMsg = GenerateTensorFromVideo( argv[ 1 ] );
			break;

		case 3:
			outMsg = GenerateTensorFromVideo( argv[ 1 ], argv[ 2 ] );
			break;

		case 4:
			outMsg = GenerateTensorFromVideo( argv[ 1 ], argv[ 2 ], argv[ 3 ] );
			break;

		case 1:
		default:
			outMsg =  "Exiting due to wrong number of on-line parameters.\n";
			break;
	}

	cout << outMsg;		// write out output message
	return 1;
}

string GenerateTensorFromVideo( const string & videoPath, 
								const string & outFileName /*= string("")*/, 
								const string & outFileExt /*= string("")*/ )
{
	// ...

	return string( "" );
}




///////////////////////////////////////////////////////////
// This function changes endianness 
// i.e. it reverts order of bytes in the input arg.
// Example: 0x78ABCDEF will be changed to 0xEFCDAB78
///////////////////////////////////////////////////////////
//
// INPUT:
//			in - integer like type
// OUTPUT:
//			byte reversed version of in
//
auto Revertendianness( unsigned long in ) 
{
	unsigned long out { 0 };
	for( auto i { 0 }; i < sizeof( in ); ++ i )		// rotate byte-by-byte
	{
		out <<= 8;
		out |= in & 0xFF;
		in >>= 8;
	}
	return out;
}



int SleepingThread( void * p )
{
	int milisecToSleep = * (int*) p;
	for(;;)
		;//Sleep( milisecToSleep );

	return 0;
}


void LoopStatements( void )
{

	// 1
	{
		const size_t kSize { 16 };	// size_t for dimensions
		std::vector< int > tab( kSize );	// Reserve kSize ints

		// Set consecutive kSize odds
		for( auto i { 0 }; i < tab.size(); ++ i )
			tab[ i ] = 2 * i + 1; 



		{
			ifstream inFl( "InFile.txt" );
			ofstream outFl( "OutFile.txt" );

			if( inFl.is_open() && outFl.is_open() )
				for( string str; getline( inFl, str ); outFl << str << endl )
					transform( str.begin(), str.end(), // Contains loop inside
						str.begin(), toupper );			
		}

	}


	// 2
	{
	
		unsigned long flag = 0xABCDEF;

		flag = Revertendianness( flag );		// make use of constexpr
	
	}


	// 3
	{
	
		vector< int >		vec;

		for( auto i : { 0, 1, 2, 3, 4, 5 } )
			vec.push_back( 2 * i );

		// now vec contains consecutive even values ...

	}



	// 4
	{

		// Display values from -10 up to -64 (excl.) with step -2
		for( auto i : range( -10, -64, -2 ) )
			std::cout << i;


	}





	// 5
	{

		const size_t kSize = 16;
		std::array< int, kSize > tab;

		// fill all values with 0 - use pointers
		int i = 0;
		while( i < tab.size() )
			tab[ i ++ ] = 0;

	}




	// 6
	{

		const size_t kSize = 16;
		std::array< int, kSize > tab;

		// fill all values with 0 - more readable
		int i = 0;
		while( i < tab.size() )
		{
			tab[ i ] = 0;
			i ++;
		}


	}



	// 7
	{

		const size_t kSize = 16;
		std::array< int, kSize > tab;

		// fill the array - this time do-while
		int i = 0;
		do tab[ i ++ ] = 0; while ( i < tab.size() );


	}



	// 8
	{
		cout << endl << endl;

		int age = 0;

		do
		{
			cout << "Enter your age ..." << endl;		
			cin >> age; // read age from keyboard

		} while( age <= 0 || age > 150 );			
		// Ask until valid range


	}



	// 9 break statement
	{

		for( ;; )
		{
			// Do something
			// ...

			cout << "Proceed? [y/n] "; 
			char ans {};
			cin >> ans;

			if( ans == 'n' || ans == 'N' )
				break;		// the way to exit the loop
		}



	}


	// 10
	{
		const auto kRows { 12 };
		const auto kCols { 12 };
		std::array< std::array< int, kCols >, kRows > _2D_array;

		// ... read _2D_array from a file

		// Add all components of array 
		// except for the diagonal
		double sum = 0.0;
		for( int r = 0; r < kRows; ++ r )
		{
			for( int c = 0; c < kCols; ++ c )
			{
				if( r == c )
					continue; // if diagonal, skip

				sum += _2D_array[ r ][ c ];
			}
		}

	}



	// 11
	{

		const int kBufLen = 1024;
		char buf[ kBufLen ];

		// Read line-by-line 
		for( ifstream inFile( "InFile.txt" ); inFile && ! inFile.eof(); )
		{
			if( ! inFile.getline( buf, kBufLen) )
				goto exit; // exit the loop

			// process buffer ...
		}


		exit:
			cout << "Loop terminated" << endl;


		// Old C style of opening and processing a file.
		// Still can find in books on Linux, embedded systems, ...
		FILE	*	theFile = NULL;	// C style file object

		if( ! ( theFile = fopen( "OldFile.txt", "r" ) ) )
			goto file_proc_error;

		/* Read comma separated values */
		/* However, everything can happen in the file */
		int r = 0, c = 0;

		file_proc_error:
			printf( "Error reading params from a file. Exiting...\n" );

	}



	// 12
	{
		cout << "\nEnter 2 floating-point values: ";

		double x = 0.0, y = 0.0;
		cin >> x >> y; // Read x and y from keyboard

		try
		{
			if( fabs( y ) < 1e-12 ) // Check magnitude
					throw string( "Error - div by 0" );// Throw excpt

			cout << x / y ; // Divide
		}
		catch( string & str )
		{
			cerr << str; // Display cause of error on cerr
		}


	}











}






}		// CppBook namespace end


void my_func(int* pA) // a pointer to an int
{
	//do things with pA, an int*
    
	cout << sizeof( pA );
}


void my_func1(int(&a)[10]) // a reference to an int[10]
{
	//do things with a , an int[10]

	cout << sizeof( a );
	cout << a[ 2 ];

}


void ArrayExample( void )
{
	char * message = R"(
							On the issue of passing arrays into functions, almost all tutorials say

							“You can't pass an array by value because they are not copyable so instead you pass a pointer to its first element”

							and in doing so they mislead us with a false binary choice. We swallow it so easily because the next thing they tell us is

							“You just have to pass the name of the array and it will automatically decay to a pointer to the first element”.

							As a result the following practice has been canonised:
							Hide   Copy Code
						)";



	int arr[10];
	my_func( arr );  //just pass the name of the array

	//and the following rarely considered and the syntax even more rarely achieved




	int arr2[10];
	my_func( arr2 );  //just pass the name of the arrat here too


}




void PlayGame( void )	// declaration
{
	
}


void Switch_17_test( void )
{


	bool answer_expected { true };				
	cout << "Do you want to play a game? [Y/N]" << endl;

	do
	{
		cin.clear(); // clear the input buffer
		switch( char c {}; std::cin >> c, c )
		{
			case 'Y':
			case 'y':	
				answer_expected = false;
				cout << "Let's play our game" << endl;
				PlayGame();
				break;

			case 'N':
			case 'n':	
				answer_expected = false;
				cout << "Let's stop our game" << endl;
				break;

			default:
				answer_expected = true;
				cout << "Press only \'Y\' for yes or \'N\' for no" << endl;
				break;
		}

	} while( answer_expected == true );



}



