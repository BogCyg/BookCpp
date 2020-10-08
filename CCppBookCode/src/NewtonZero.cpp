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
#include <functional>
#include <algorithm>
#include <limits>
#include <tuple>
#include <cassert>






namespace NewtonZero
{
	using FP = double;
	using Real_Fun = std::function< FP( FP ) >;

	// Derivative is also a 1D real function
	auto deriv( const Real_Fun & fun, const FP x0, const FP eps = 1e-5 )
	{
		// Let's use the definition of a derivative
		return ( fun( x0 + eps ) - fun( x0 ) ) / eps;
	}


	///////////////////////////////////////////////////////////
	// Finds zero crossing of the supplied function 
	///////////////////////////////////////////////////////////
	//
	// INPUT:	fun - a function object
	//			start_x - estimated starting point
	//			thresh - a convergence threshold
	// OUTPUT:
	//			a tuple containing a pair of values:
	//			- the found zero position
	//			- true if computations converged
	//
	// REMARKS:
	//			Only if true is returned can the result be valid
	//
	auto FindZero( const Real_Fun & fun, const FP start_x, const FP thresh = 1e-10 )
	{
		FP x_n { start_x };

		const FP eps = std::numeric_limits< FP >::epsilon();

		// Only if true can computations be correct
		bool reach_converg { false };

		// It is always good to have a fuse in case computations do not converge
		const size_t kMaxIters { 1000 };

		for( size_t n = 0; n < kMaxIters; ++ n )
		{
			// Set the threshold
			const FP loc_thresh = std::max( thresh, eps * std::fabs( x_n ) );

			FP df_x = deriv( fun, x_n );

			// Check if we can safely divide
			if( std::fabs( df_x ) <= eps )
				break;

			// This is the Newton step
			FP delta = - fun( x_n ) / df_x;

			// Check for convergence 
			if( std::fabs( delta ) <= loc_thresh )
			{
				reach_converg = true;		// result can be OK
				break;		
			}

			x_n += delta;	// Update the argument by delta and iterate
		}

		// Return the result - valid only if reach_converg == true
		return std::make_tuple( x_n, reach_converg );
	}


}	// End of NewtonZero




// Some test functions
namespace NewtonZero
{

	void NewtonZero_Test( void )
	{	
		auto [ val, flag ] = FindZero(	[] ( double x ) { return x * x + x - 6.0; }, -1.5 );
	
		std::cout << "Zero at " << ( flag ? std::to_string( val ) : "none" ) << std::endl;
	}

}


namespace NewtonZero
{

	// Compute the square root of the arg
	auto SquareRootApproxNewton( const FP arg )
	{
		// This is a reverse function of the square root
		auto sq_root = [ arg = arg ] ( double x ) { return x * x - arg; };
	
		return FindZero( sq_root, 1.0 );
	}


	void SquareRoot_Test( void )
	{
		std::cout << "Enter positive value to compute the square root "; 

		double arg {};
		std::cin >> arg;
		if ( arg < 0.0 ) return;

		auto [ val, flag ] = SquareRootApproxNewton( arg );
		
		if( flag )
			std::cout << "sqrt( " << arg << " )= " << val << std::endl;	
		else
			std::cout << "Cannot compute the square root" << std::endl;

	}

}	// End of NewtonZero


