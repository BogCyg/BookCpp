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




#include <vector>
#include <iostream>
#include <iomanip>
#include <random>
#include <numeric>		// for inner product





namespace InnerProducts
{

	using DVec = std::vector< double >;
	using DT = DVec::value_type;
	using ST = DVec::size_type;

	using std::inner_product;
	using std::transform;
	using std::accumulate;
	using std::sort;

	using std::cout, std::endl;

	auto InnerProduct_StdAlg( const DVec & v, const DVec & w )
	{
		// The last argument is an initial value
		return inner_product( v.begin(), v.end(), w.begin(), DT() );
	}


	auto InnerProduct_SortAlg( const DVec & v, const DVec & w )
	{
		DVec z;		// Stores element-wise products

		// Elementwise multiplication: c = v .* w
		transform(	v.begin(), v.end(), w.begin(), 
					back_inserter( z ), 
					[] ( const auto & v_el, const auto & w_el) { return v_el * w_el; } );

		// Sort in ascending order
		sort( z.begin(), z.end() );		// Is it magic?
	
		// The last argument is an initial value
		return accumulate( z.begin(), z.end(), DT() );
	}


	// In the Kahan algorithm each addition is corrected by a correction
	// factor. In this algorithm the non associativity of FP is assumed, i.e.:
	// ( a + b ) + c != a + ( b + c )
	auto InnerProduct_KahanAlg( const DVec & v, const DVec & w )
	{
		DT theSum {};

		// volatile prevents the compiler from applying any optimization
		// on the object since it can be changed by someone else, etc.,
		// in a way that cannot be foreseen by the compiler.

		volatile DT c {};		// a "correction" coefficient

		const ST kElems = std::min( v.size(), w.size() );

		for( ST i = 0; i < kElems; ++ i )
		{
			DT y = v[ i ] * w[ i ] - c;	// From y subtracts the correction factor

			DT t = theSum + y;	// Add corrected summand to the running sum theSum
			// But theSum is big, y is small, so its lower bits will be lost

			c = ( t - theSum ) - y; // Low-order bits of y are lost in the summation. 
		// High-order bits of y are computed in ( t - theSum ). Then, when y
		// is subtracted from this, the low order bits of y are recovered (negative).
		// Algebraically, c should always be 0 (beware of compiler optimization).

			theSum = t;
		}

		return theSum;
	}



	void InnerProduct_Test( void )
	{
		const int kElems = 100000;

		DVec	v( kElems );
		DVec	w( kElems );
	
		std::mt19937		rand_gen{ std::random_device{}() }; 	// Random Mersenne twister

		// ref is a reference wrapper
		std::generate( v.begin(), v.end(), ref( rand_gen ) );
		std::generate( w.begin(), w.end(), ref( rand_gen ) );

		// Now let's double our vectors with one negative reflection

		// Lambda has to be mutable to allow change of the variable n
		v.resize( 2 * kElems );
		std::generate( v.begin() + kElems, v.end(), 
							[ n = 0, & v ] () mutable { return - v[ n ++ ]; } );
		w.resize( 2 * kElems );
		std::generate( w.begin() + kElems, w.end(), 
							[ n = 0, & w ] () mutable { return + w[ n ++ ]; } );

		// The inner product should be close to 0.0, 
		// so let's check the two algorithms.

		cout 	<< "Stand alg error = \t"	<< std::setprecision( 8 ) 
				<< fabs( InnerProduct_StdAlg( v, w ) ) << endl;
		cout 	<< "Sort alg error = \t"	<< std::setprecision( 8 ) 
				<< fabs( InnerProduct_SortAlg( v, w ) ) << endl;
		cout 	<< "Kahan alg error = \t"	<< std::setprecision( 8 ) 
				<< fabs( InnerProduct_KahanAlg( v, w ) ) << endl;
	}

}





