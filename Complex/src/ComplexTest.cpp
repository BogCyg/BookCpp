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





#include <fstream>

#include "Complex.h"




using std::cout, std::cin, std::endl;
using std::ofstream, std::ifstream;

using CppBook::TComplex;



// Simple operations with complex numbers 
// using the keyboard and the screen
void Complex_Test_Screen( void )
{
	//////////////////////////////////////////
	// Let's create few TComplex objects:
	CppBook::TComplex	a, b,			// a and b by default constructor
						c( 10., 20. );	// c by the parametric constructor

	TComplex d( c );	// yet another one, this time d contains a copy of c

	// Let's test how to stream out object d to the screen
	cout << d << endl;		
	operator << ( cout, d );	// we can also write like this
	cout << endl;				// then move to the new line

	cout << "Write re, press Enter, then im, press Enter" << endl;
	cin >> a;	// from the keyboard read new values to the object a

	c = b = a;	// copy a to b, then b to c (= is right associative)

	// Let's add two complex numbers b and d and display the result
	cout << "( " << a << " ) + ( " << b << " ) = ( " << a + b << " ) " << endl;	

	// To assign 5.0 to b, at first, 5.0 needs to be converted to TComplex, then assigned.
	b = 5.0;
	cout << "( " << a << " ) + ( " << b << " ) = ( " << a + b << " ) " << endl;	
}


// Simple operations with complex numbers 
// using the keyboard, the screen, and a file
void Complex_Test_File( void )
{
	// Create two complex objects
	TComplex	a, b;			
		
	// Enter two from the keyboard
	cout << "Enter 1st complex" << endl;
	cin >> a;

	cout << "Enter 2nd complex" << endl;
	cin >> b;

	// Let's try to copy results to a file opened in appending mode
	ofstream theFile( "ComplexTest.txt", std::ios::app );	 

	// Always check if the file opened correctly
	if( theFile.is_open() == true )
	{
		// Perform operations and print results to the file
		theFile << "a = " << a << ", b = " << b << endl;
		theFile << "a + b = " << a + b << endl;
		theFile << "a - b = " << a - b << endl;
		theFile << "a * b = " << a * b << endl;

		// However, division is different - it can throw an exception
		try
		{
			// Keep it in the try-catch clamp
			theFile << "a / b = " << a / b << endl << endl;
		}
		catch( std::exception & e )		// catch exceptions
		{
			// Standard exceptions will be processed here
			std::cerr << "Exception caught: "	<< e.what() << endl;	// print the cause 
		}
		catch( ... ) 
		{
			// Any other exception will be caught here
			std::cerr << "Unknown error" << endl;	
		}		

	}

}

