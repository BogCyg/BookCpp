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




#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <array>
#include <random>
#include <fstream>
#include <tuple>
#include <cassert>
#include <time.h>





///////////////////////////////////////////////////////////////////////////////////


#include <iostream>

using std::cout, std::cin, std::endl;


// Function declaration - we introduce a function.
// Its full definition is elsewhere.
double SumOfSquares( double a, double b );


void SumOfSquaresTest( void )
{
	double x { 0.0 }, y { 0.0 };	// two floating point variables

	cout << "Enter two values" << endl;
	cout << "x = "; 
	cin >> x;
	cout << "y = ";
	cin >> y;

	// Sum will contain the value returned by SumOfSquares
	double sum = SumOfSquares( x, y );

	cout << "x*x + y*y = " << sum << endl;
}


///////////////////////////////////////////////////////////
// Computes and returnes sum of squares of its arguments
///////////////////////////////////////////////////////////
//
// INPUT:
//			a, b - floating point input values
// OUTPUT:
//			Sum of squares of a and b, i.e.: 
//			a * a + b * b
//
// REMARKS:
//			Parameters passed by value (copies)
//
double SumOfSquares( double a, double b )
{
	return a * a + b * b;
}




///////////////////////////////////////////////////////////


// Let's define an external constant pi
const double kPi = 3.1415926535897932385; 

namespace Deg_2_Rad_Val
{

	// Converts degs to radians.
	// Pass "deg" by a copy
	double Deg_2_Rad( const double deg )
	{
		// Whatever happens to deg here 
		// has an effect only here
		return kPi * deg / 180.0;
	}

}


namespace Deg_2_Rad_Ref
{


	// The same action but indirect access 
	// by a const reference.
	// In C++ we can use the same function names
	// provided that their params are different (overloading)
	double Deg_2_Rad( const double & deg )
	{
		// deg is a reference to an object
		// defined outside Deg_2_Rad;
		// deg can only be read since it is const reference
		return kPi * deg / 180.0;	// the same formula as before
	}


}

namespace Deg_2_Rad_IO_Ref
{
	// Converts "val" from degs to rads in place
	// Works but can surprise ...
	void Deg_2_Rad( double & val )
	{
		val *= kPi / 180.0;
	}

}


// An indirect version with a pointer. (The only way in old C)
// deg must be a valid pointer. 
void Deg_2_Rad( double * deg )
{
	// should we check whether deg is not nullptr?
	assert( deg != nullptr );

	* deg = kPi * * deg / 180.0;

	deg = nullptr ;	// deg is a local pointer - we can zero it here
					// but nothing happens to the outside object
}




// Function call examples
void FunctionCallTest( void )
{
	{
		double d { 0.0 };		// holds degrees

		cout << "Enter degs: ";
		cin >> d;

		double r { 0.0 };		// here we'll store radians

		r = Deg_2_Rad_Val::Deg_2_Rad( d );	// call Deg_2_Rad, d won't be affected

		cout << d << " degs = " << r << " rad" << endl;
	}

	// ----------------

	{
		double d { 0.0 };		// holds degrees

		cout << "Enter degs: ";
		cin >> d;

		double r { 0.0 };		// here we'll store radians

		r = Deg_2_Rad_Ref::Deg_2_Rad( d );	// call Deg_2_Rad, d won't be affected

		cout << d << " degs = " << r << " rad" << endl;	
	
	}
	
	// ----------------

	{

		double d { 0.0 };		// holds degrees

		cout << "Enter degs: ";
		cin >> d;

		double d_storage = d;		// here we'll store degrees for later

		Deg_2_Rad_IO_Ref::Deg_2_Rad( d );	// call Deg_2_Rad, d will be changed

		cout << d_storage << " degs = " << d << " rad" << endl;	

	}

	// ----------------

	{

		double d { 0.0 };		// holds degrees

		cout << "Enter degs: ";
		cin >> d;

		double d_storage = d;		// here we'll store radians for later

		Deg_2_Rad( & d );	// call Deg_2_Rad; d will be changed (!)

		cout << d_storage << " degs = " << d << " rad" << endl;	

	}



}



//
//float FuelConsumption( float km, float fuel );
//
//
//float FuelConsumption( float km, float fuel )
//{
//	return fuel / km * 100.0;
//}







// New way of defining constants
// with variable templates
template< typename T >
constexpr T gkPi = T( 3.1415926535897932385 );


template < typename C >
const C GetCircleArea( const C radius )
{
	return gkPi< C > * radius * radius;
}



///////////////////////////////////////////////////////

// Returns n-th element of the Fibonacci series.
// Recursive function
const int	FiboRecursive( const int n )
{
	assert( n < 100 );	// a "fuse" not to overrun the stack

	if( n == 0 || n == 1 ) 
		return n;
	else
		return FiboRecursive( n - 1 ) + FiboRecursive( n - 2 );
}


void FiboRecursive_Test( void )
{
	cout << "Enter Fibonacci level: ";

	int fibo {};	// define and init to 0
	cin >> fibo;	// read from the keyboard

	// display it out
	cout << "Fibonacci at level " << fibo << " is " << FiboRecursive( fibo ) << endl;
}

