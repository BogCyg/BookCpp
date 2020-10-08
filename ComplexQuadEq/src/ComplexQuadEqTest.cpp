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
#include "ComplexQuadEq.h"


using std::cout, std::endl;



void ComplexQuadEq_Test( void )
{
	double a { 5.0 }, b { 2.0 }, c { 1.0 };

	TComplexQuadEq		cqe( a, b, c );


	TComplex r1, r2;

	TComplexQuadEq::EEqType eq_type = cqe.GetRoots( r1, r2 );

	if( eq_type == TComplexQuadEq::EEqType::kOne || 
		eq_type == TComplexQuadEq::EEqType::kTwo )
	{
		// Check if correct - there are many abs functions, but
		// thanks to the CppBook namespace we do not confuse them
		assert( CppBook::abs( r1 * ( r1 * a + b ) + c ) < 1e-12 );
		assert( CppBook::abs( r2 * ( r2 * a + b ) + c ) < 1e-12 );

		// Print out the results:
		cout << "a=" << a << ", b=" << b << ", c=" << c << endl;
		cout << "Root_1=" << r1 << ", Root_2=" << r2 << endl;
	}
	else
	{
		cout << "This is a deficient quadratic equation" << endl;
	}

}








