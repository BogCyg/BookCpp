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

#include "QuadEq.h"


// With these we can simply write cout
// instead of std::cout, etc.
using std::cout, std::cerr, std::cin, std::endl;



// In C++ there are overloaded main functions
int main( void )
{
	// Text corresponding to TQuadEq::EEquationType 
	const std::string eq_types_text[] = {	"No real roots", 
											"One real root", 
											"Two real roots",
											"Linear equation, one root",
											"A contradictory equation"
										};


	cout << "Enter coefficients of the quadratic equation: a*x*x + b*x + c" << endl;
	double a = 0.0, b = 0.0, c = 0.0;
	cin >> a >> b >> c;

	TQuadEq		eq( a, b, c );		// Create an initialized  object

	// For the roots
	double x1 {}, x2 {};			// {} to initialize vars to zero

	TQuadEq::EEqType	eq_type {};

	try
	{
		eq_type = eq.GetRoots( x1, x2 );	// This can throw
	}
	catch( const std::exception & e )
	{
		cerr << e.what() << endl;	// print the reason
		return -1;	// Exit with a failure code
	}


	// Everything ok, so print results
	cout << eq_types_text[ static_cast< int >( eq_type ) ];
	
	// In addition, if there are roots, then print them out.
	switch( eq_type )
	{
		case TQuadEq::EEqType::kOne:
		case TQuadEq::EEqType::kLinOne:
			cout << ": " << x1 << endl;
			break;

		case TQuadEq::EEqType::kTwo:
			cout << ": " << x1 << ", " << x2 << endl;
			break;

		default :
			break;
	}

	return 0;	// Exit wit ok code
}