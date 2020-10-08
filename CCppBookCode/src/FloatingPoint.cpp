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
#include <iomanip>
#include <iterator>
#include <array>
#include <random>
#include <fstream>
#include <limits>
#include <numeric>		// for inner product
#include <valarray>

#include <cassert>


using namespace std;


/////////////////////////////////////////////////////////////////////


// Numerical computations with float format

void Test_Float_1( void )
{

	double first_val	{ 0.1 };
	double scnd_val		{ 0.2 };

	double expected_result { 0.3 };

	if( first_val + scnd_val == expected_result )
		cout << "As expected?" << endl;
	else
		cout << "What's going on?" << endl;

}


void Test_Float_1b( void )
{

	double first_val	{ 0.1 };
	double scnd_val		{ 0.2 };

	double expected_result { 0.3 };

	const double kThresh { 1e-12 };

	if( std::fabs( ( first_val + scnd_val ) - expected_result ) < kThresh )
		cout << "As expected?" << endl;
	else
		cout << "What's going on?" << endl;

}


void Test_Float_1c( void )
{
	using FP_Type = float;

	FP_Type first_val	{ 0.3f };
	FP_Type scnd_val		{ 0.4f };

	FP_Type expected_result { 0.7f };
	
	FP_Type kThresh { 1e-12f };	// Let's assume an acceptable threshold or set to 0

	FP_Type eps = numeric_limits< FP_Type >::epsilon();


	FP_Type sum = first_val + scnd_val;

	FP_Type max_val = std::max( std::fabs( sum ), std::fabs( expected_result ) );

	// Let's modify the threshold to be at least as the second argument
	kThresh = std::max( kThresh, eps * max_val );
	

	if( std::fabs( sum - expected_result ) < kThresh )
		cout << "As expected?" << endl;
	else
		cout << "What's going on?" << endl;

}


// What to do if we do not know an acceptable threshold
void Test_Float_1d( void )
{

	double first_val	{ 0.1 };
	double scnd_val		{ 0.2 };

	double expected_result { 0.3 };


	double eps = numeric_limits< double >::epsilon();


	double sum = first_val + scnd_val;

	double max_val = std::max( std::fabs( sum ), std::fabs( expected_result ) );

	// Let's modify the threshold to be at least as the second argument
	double kThresh { eps * max_val };


	if( std::fabs( sum - expected_result ) <= kThresh )
		cout << "As expected?" << endl;
	else
		cout << "What's going on?" << endl;

}




/////////////////////////////////////////////////////////////////////

// This is a code snippet, kind of a template, to 
// code your iterative function that needs to check
// convergence by comparing consecutive values 
// of a control variable. 
void IterativeFunctionTemplate( void )
{

	double x_n {}, x_n_1 {};

	double eps = numeric_limits< double >::epsilon();

	// An anticipated convergence threshold
	double thresh { 1e-12 };

	// It is always good to have a fuse if computations do not converge
	const size_t kMaxIters { 1000 };

	for( size_t n = 0; n < kMaxIters; ++ n )
	{
		// do computations, x_n_1 is a new value of x_n
		// ...

		thresh = std::max( thresh, eps * std::max( std::fabs( x_n ), std::fabs( x_n_1 ) ) );
		
		if( std::fabs( x_n_1 - x_n ) <= thresh )
			break;		// x_n_1 and x_n are approximately equal

		x_n = x_n_1;	// copy for the next iteration
	}


}


/////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////
// This function generates all floating-point values
// for the chosen floating-point representation
///////////////////////////////////////////////////////////
//
// INPUT:	SignificandDigits - a total number of digits in
//				the significand (i.e. mantissa), including the
//				leading 1 (a normalized versions assumed)
//			Base - computation base
//			Exp_min, Exp_max - the inclusive range of exponents 
//
// OUTPUT:
//
//
// REMARKS:
//			Only positive values are returned. There is
//			the same number of negative.
//			Mantissa == significand
//
vector< double >	Generate_FP_Numbers( const int SignificandDigits, const int Base, const int Exp_min, const int Exp_max )
{
	vector< double > retVals;

	assert( SignificandDigits > 1 );
	assert( Base > 1 && Base < 22 );
	assert( Exp_min < Exp_max );


	const double total_variation = pow( Base, SignificandDigits );	// A total number of values on the significant - 1

	const double divisor = total_variation / Base;

	// Go through all exponents
	for( int E = Exp_min; E <= Exp_max; E += 1 )
	{
		const double cur_exponent = pow( Base, E );
	
		for( double mant = 0.0; mant < total_variation; mant += 1.0 )
		{
			double val = (double) mant / divisor;

			if( val < 1.0 )
				continue;	// To leave only normalized values, skip all with the leading 0
			
			val *= cur_exponent;

			retVals.push_back( val );
		}
	}

	return retVals;
}


void Test_Float_3( void )
{

	int p { 3 };
	int B { 2 };
	int E_min { -1 };
	int E_max { 2 };

	vector< double >	fp_vals = Generate_FP_Numbers( p, B, E_min, E_max );

	ofstream fp_file( "fp_vals.txt" );

	fp_file << p << " " << B << " " << E_min << " " << E_max << endl;

	copy( fp_vals.begin(), fp_vals.end(), ostream_iterator< double >( fp_file, " " ) );

}


/////////////////////////////////////////////////////////////////////


void Test_Float_4( void )
{

	// Let's find epsilon for single precision floating-point
	const float kBase { 2.0f };

	// We will start from this and then this will be successively halved
	const float kEpsInit { 1.0f };

	// Stores the last computed epsilon
	float store_eps {};

	// Iterate until adding eps to 1.0f does not change 1.0f
	for( float eps = kEpsInit; 1.0f + eps != 1.0f; eps /= kBase )
		store_eps = eps;	// We need to catch the one before the last

	cout << "Machine epsilon = " << store_eps << endl;
	cout << "Machine epsilon = " << numeric_limits< float >::epsilon() << endl;




	// -------------------------
	// Print some values on float


	cout.setf( ios::boolalpha );		// print plain 'true' or 'false'

	cout << "numeric_limits< double >::epsilon() = " << numeric_limits< double >::epsilon() << endl;

	cout << "numeric_limits< double >::radix = " << numeric_limits< double >::radix << endl;
	cout << "numeric_limits< double >::digits (mantissa) = " << numeric_limits< double >::digits << endl;

	cout << "numeric_limits< double >::min() = " << numeric_limits< double >::min() << endl;
	cout << "numeric_limits< double >::max() = " << numeric_limits< double >::max() << endl;

	cout << "numeric_limits< double >::has_denorm = " << numeric_limits< double >::has_denorm << endl;
	cout << "numeric_limits< double >::denorm_min() = " << numeric_limits< double >::denorm_min() << endl;
	cout << "numeric_limits< double >::lowest() = " << numeric_limits< double >::lowest() << endl;

	cout << "numeric_limits< double >::has_infinity = " << numeric_limits< double >::has_infinity << endl;

	// round_to_nearest or round_toward_zero
	cout << "numeric_limits< double >::round_style = " << 
		( numeric_limits< double >::round_style == std::round_to_nearest ? "round_to_nearest" : "round_toward_zero" ) << endl;

	cout << "numeric_limits< double >::round_error() = " << numeric_limits< double >::round_error() << endl;


	// -------------------------
	// Play with denorms

	const auto kInfinity = numeric_limits< double >::infinity();

	double val = 0.0;
	double next_from_val = nextafter( val, kInfinity );
	cout << "nextafter( " << setprecision( 20 ) << val
		<< " ) = " << next_from_val
		<< hexfloat << " (" << next_from_val << ")\n" << defaultfloat;

	val = 1.0;
	next_from_val = nextafter( val, kInfinity );
	cout << "nextafter( " << setprecision( 20 ) << val
		<< " ) = " << next_from_val
		<< hexfloat << " (" << next_from_val << ")\n" << defaultfloat;

	// -------------------------
	// Play with special values

	double zero { 0.0 };

	double inf { 1.0 / zero };	// let's generate infinity, no exception

	cout << "infinity = " << inf << endl;
	cout << "inf == inf ? " << ( inf == kInfinity ) << endl;
	cout << "123.0 + inf == " << 123.0 + inf << endl;
	cout << "123.0 / inf == " << 123.0 / inf << endl;

	// Let's generate NaN

	double nan = sqrt( -0.1 );

	cout << "123.0 + nan == " << 123.0 + nan << endl;


	// -------------------------

	unsigned long df = 0b0'10001100'11110000111100000000000; 
	float * df_f_ptr = (float *) & df;
	cout << "df_float = " << * df_f_ptr << endl;		// this is not (float) df

	// -------------------------

}



/////////////////////////////////////////////////////////////////////


void BadInitTest( void )
{
	// A vector with 10 values 0.5
	vector< double > vec( 10, 0.5 );

	// Try the first accumulate and see what happens
	//auto sum = accumulate( vec.begin(), vec.end(), 0 );	// here is the error, should be 0.0
	auto sum = accumulate( vec.begin(), vec.end(), 0.0 );

	cout << "sum = " << sum << endl;

	cout << "Surprise?" << endl;


}




/////////////////////////////////////////////////////////////////////

// This is a quadratic solver rewritten
// to avoid potential floating-point
// catastrophic cancellation when subtracting
// similar magnitude values.
void QuadraticSolver( void )
{

	double a {}, b {}, c {};

	// Read in a, b, c ...


	double x1 {}, x2 {};

	double d = b * b - 4.0 * a * c;
	if( d > 0.0 )
	{
		if( b < 0.0 )
		{
			x1 = ( -b + sqrt( d ) ) / ( a + a );	// –b becomes positive and we have addition
			x2 = c / x1;
		}
		else
		{
			x1 = ( -b - sqrt( d ) ) / ( a + a );	// adding two negative values
			x2 = c / x1;
		}
	}

	// ...
}


/////////////////////////////////////////////////////////////////////


// Here we study limits of the values for the valid 
// division of the following form:
// 
// double a {}, b {}, c {};
// ...
// c = a / b;
//
// If division is possible, the above means that:
// a == b * c
// 
// Hence, the division is not possible if b == 0.
// But what are the conditions for a and b that the division
// is possible? In this example we investigate 
// this problem.
//
// We assume only nonnegative values - if negatives are allowed, 
// then use fabs.
//
void Float_Mult_Test( void )
{
	//using FP = double;
	using FP = float;

	constexpr auto kMin { std::numeric_limits< FP >::min() };
	constexpr auto kMax { std::numeric_limits< FP >::max() };

	constexpr auto kEpsilon { std::numeric_limits< FP >::epsilon() };

	constexpr auto kCapacity { kMin * kMax };


	// These variables are used in the division.
	FP a {}, b {}, c {};


	// Certainly we must care for BOTH: THE DIVISOR AND THE DIVIDENT !
	c = kMax / kMax;		// ok
	c = kMin / kMin;		// ok
	//c = kMax / kMin;		// this will produce "inf"!


	// ------------------------
	// CASE 0:
	// Check the extreme values
	a = kCapacity;
	b = kMin;


	if( a <= kCapacity && b >= kMin )	// The problem is that kCapacity less than 4.0
	{
		c = a / b;
		auto a_bis = c * b;
		assert( std::fabs( a - a_bis ) <= ( a * kEpsilon ) );
	}
	else
	{
		;		// what to do? throw?
	}




	// --------------------------------------------------------------
	// CASE 1:
	// But in practice ( a <= kCapacity ) does NOT hold (a is larger)
	// In such a case, let's assume we know a_max <== this is the only one assumption we need!
	const FP a_max { 1e20f };		// Must be positive since this is the magnitude
	assert( a_max <= kMax );		// certainly we cannot exceed the maximum capacity of the representation

	// Now we are able to compute b_min, as follows:
	const auto b_min { std::max( kMin, a_max / kMax ) };		// the second conditions is the same as: ( kMin * a_max ) / kCapacity

	// Let's assume we have some real measurements ...
	a = 2e5f;
	b = 2e-15f;

	// If the following condition is true, then we can divide
	if( std::fabs( a ) <= a_max && std::fabs( b ) >= b_min )
	{
		c = a / b;
		auto a_bis = c * b;
		assert( std::fabs( a - a_bis ) <= ( a * kEpsilon ) );
	}
	else
	{
		;		// what to do? throw?
	}


	// -----------------------------------------------
	// CASE 2:
	// But what to do if we have no idea on the a_max?
	// We can choose b_min relatively to e.g. the machine epsilon.
	// But remember that: kEpsilon < kMin
	// so usually there will be room on max of a, i.e. a_max_eps_rel < a_max 
	// Here we set b_min = kEpsilon but it can be any other value >= kMin
	const auto a_max_eps_rel { kEpsilon * kMax };			// the same as: ( kEpsilon * kCapacity ) / kMin

	a = 2e5f;
	b = 2e-7f;

	// Now the condition for the save division is as follows
	if( std::fabs( a ) <= a_max_eps_rel && std::fabs( b ) >= kEpsilon )
	{
		c = a / b;
		auto a_bis = c * b;
		assert( std::fabs( a - a_bis ) <= ( a * kEpsilon ) );
	}
	else
	{
		;		// what to do? throw?
	}


	// CASE 2b:
	// In practice, if we know our domain well, the first condition can go into the assert
	assert( std::fabs( a ) <= a_max_eps_rel );
	if( std::fabs( b ) >= kEpsilon )
	{
		c = a / b;
		auto a_bis = c * b;
		assert( std::fabs( a - a_bis ) <= ( a * kEpsilon ) );
	}
	else
	{
		;		// what to do? throw?
	}




}



/////////////////////////////////////////////////////////////////////

