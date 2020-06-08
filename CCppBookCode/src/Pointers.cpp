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
#include <fstream>
#include <iterator>

#include "range.h"

using namespace std;
using CppBook::range;



void PointerTestFun( void )
{

	{

		char c = 0;			// a variable initialized to 0 

		char * ptr = & c;	// a pointer initialized to point at c

		c = 'A';			// DIRECTLY assign 'A' to c

		* ptr = 'A';		// INDIRECTLY assign 'A' to c via the pointer ptr



		char * * ptr_2_ptr = nullptr;	// a pointer to a pointer initialized to nullptr (0)

		ptr_2_ptr = & ptr;				// now ptr_2_ptr points at ptr

		* * ptr_2_ptr = 'B';			// INDIRECTLY assign 'B' to c via the pointer to pointer 

	}

	//////////////////////////////////////////

	{

		const int kSize = 128;
		int tab[ kSize ];

		/* Array access with the subscript [] operator */
		for( int i = 0; i < kSize; ++ i )
			tab[ i ] = 0;

		/* Array access via the const pointer */
		for( int i = 0; i < kSize; ++ i )
			* ( tab + i ) = 0;

		/* Array access via the pointer */
		int * tab_ptr = tab;	/* tab is constant, tab_ptr is variable */
		for( int i = 0; i < kSize; ++ i )
			* tab_ptr ++ = 0;

	}

	//////////////////////////////////////////

	{
		// An example of pointer arithmetic on 2D array
		const int kRow = 5, kCol = 7;

		double arr[ kRow ][ kCol ];

		for( int r = 0; r < kRow; ++ r )
			for( int c = 0; c < kCol; ++ c )
				* ( * ( arr + r ) + c ) = 0.0;		// works because arr + r moves to the r-th row
	}

	//////////////////////////////////////////

	{

		char text[] = { "The quick brown fox" };

		int cnt = 0;

		// Measure length of the text
		while( * ( text + cnt ) != 0 )
			cnt ++;

		cout << "\"" << text << "\" contains " << cnt << " characters" << endl;
		cout << "However, memory occupation is " << cnt + 1 << " since there is an invisible sentinel 0 at the end of each text." << endl;

	}

	{
		string s { "Fox" };	// C++ init

		const string * s_ptr { & s };	// C++ init

		cout << * s_ptr + * s_ptr;
		// print "FoxFox"
	}

	{
		double d {};	// C++ init

		double * d_ptr { nullptr };	// C++ init

		d_ptr = & d;
	}




}


#include <iostream>
#include <functional>


namespace CppBook
{


	namespace FunPointers
	{




		static double derivative(const std::function<double(double)> &f, double x0, double eps) 
		{
			double eps2 = eps / 2;
			double lo = x0 - eps2;
			double hi = x0 + eps2;
			return (f(hi) - f(lo)) / eps;
		}

		static double f(double x) 
		{
			return x * x;
		}

		int test() 
		{
			double x = 1;
			//std::cout << "d/dx(x ^ 2) [@ x = " << x << "] = " << derivative(f, x, 1e-5) << std::endl;
			return 0;
		}


	}



}


//typedef double ( * real_fun ) ( double );

double deriv( double ( * f ) ( double ), double x0, double eps = 1e-12 )
{
	// Let's use the definition of a derivative
	return ( f( x0 ) - f( x0 + eps ) ) / eps;
}

double pow_x_2_x( double x )
{
	return pow( x, x );
}

void deriv_test_fun( void )
{
	double x0 = 1.3;
	cout << "x2x'(x0=1.3)" << deriv( pow_x_2_x, x0 ) << endl;
}




struct DerivPackage
{
	double ( * fDerivFun ) ( double );		// a function for derivative

	double fx0;

	double fEps;

	DerivPackage( double ( * f ) ( double ), double x0, double eps = 1e-12 ) 
		: fDerivFun( f ), fx0( x0 ), fEps( eps )
	{}
};


double deriv( const DerivPackage & dp )
{
	// Let's use the definition of a derivative
	return ( dp.fDerivFun( dp.fx0 ) - dp.fDerivFun( dp.fx0 + dp.fEps ) ) / dp.fEps;
}





void deriv_test_fun_2( void )
{

	/*vector< double >*/auto x( range< double >( -3.0, +3.0, 0.05 ) ); 

	vector< double > y;

	//std::generate_n( back_inserter( y ),  );

	//deriv_test_fun_2;


	cout << deriv( pow_x_2_x, 1.3 ) << endl;

}


// --------------------------------------------------


namespace BCpp_Simple_Derivatives
{

	using Real_Fun = std::function< double( double ) >;

	// Derivative is also a 1D real function
	auto deriv( const Real_Fun & fun, double x0, double eps = 1e-5 )
	{
		// Let's use the definition of a derivative
		return ( fun( x0 + eps ) - fun( x0 ) ) / eps;
	}


		// Define a square function (lambda expression)
	Real_Fun	x2_fun = [] ( double x ) { return pow( x, 2.0 ); };

	// Define a compound function ("normal" function definition)
	double fun_tan( double x )
	{
		return tanh( pow( x, 3.0 ) );
	}


	void deriv_test_fun( void )
	{


		// Fill vectors with argument, value of x2_fun, derivatives of the two functions
		vector< double >	x, fx, dfx_1, dfx_2, d2fx;
		for( auto arg : range( -3.0, +3.0, 0.1 ) )
		{
			x.		push_back( arg );
			fx.		push_back( x2_fun( arg ) );
			dfx_1.	push_back( deriv( x2_fun, arg ) );
			dfx_2.	push_back( deriv( fun_tan, arg ) );
		}

		// Store results in one file
		ofstream outFile( "x_fun_plot.txt" );

		// Copy each vector to the outFile
		copy( 	x.begin(), x.end(), ostream_iterator< double >( outFile, " " ) ); 
		outFile << endl;
		copy( 	fx.begin(), fx.end(), ostream_iterator< double >( outFile, " " ) ); 
		outFile << endl;
		copy( 	dfx_1.begin(), dfx_1.end(), ostream_iterator< double >( outFile, " " ) ); 
		outFile << endl;
		copy( 	dfx_2.begin(), dfx_2.end(), ostream_iterator< double >( outFile, " " ) );
		outFile << endl;

	}



}




namespace BCpp_Derivatives
{

	using Real_Fun = std::function< double( double ) >;


	// Derivative is also a 1D real function


	auto deriv( const Real_Fun & fun, double x0, double eps = 1e-5 )
	{
		// Let's use the definition of a derivative
		return ( fun( x0 + eps ) - fun( x0 ) ) / eps;
	}


	// Returns lambda computing 2nd deriv
	auto _2nd_deriv( const Real_Fun & fun )
	{
		// Let's use the definition of a derivative
		return [ & fun ] ( double x )	{ return deriv( 
															[ & fun ]( double x ) { return deriv( fun, x ); }, 
															x ); 
										};
	}


	double fun_tan( double x )
	{
		return tanh( pow( x, 3.0 ) );
	}


	void deriv_test_fun_ex( void )
	{

		// This is definition of our function
		Real_Fun	x2_fun =	[] ( double x ) 
								{ 
									return pow( x, 2.0 ); 
								};



		Real_Fun	x2_fun_2deriv = _2nd_deriv( x2_fun );


		double xxx = x2_fun_2deriv( 2.0 );


		vector< double >	x, fx, dfx_1, dfx_2, d2fx;
		for( auto arg : range( -3.0, +3.0, 0.1 ) )
		{
			x.		push_back( arg );
			fx.		push_back( x2_fun( arg ) );
			dfx_1.	push_back( deriv( x2_fun, arg ) );
			dfx_2.	push_back( deriv( fun_tan, arg ) );
			d2fx.	push_back( _2nd_deriv( x2_fun )( arg ) );
		}

		// Store the results
		ofstream outFile( "x_x_fun_plot.txt" );

		copy( x.begin(), x.end(), ostream_iterator< double >( outFile, " " ) ); outFile << endl;
		copy( fx.begin(), fx.end(), ostream_iterator< double >( outFile, " " ) ); outFile << endl;
		copy( dfx_1.begin(), dfx_1.end(), ostream_iterator< double >( outFile, " " ) ); outFile << endl;
		copy( dfx_2.begin(), dfx_2.end(), ostream_iterator< double >( outFile, " " ) ); outFile << endl;
		copy( d2fx.begin(), d2fx.end(), ostream_iterator< double >( outFile, " " ) ); outFile << endl;


		// ---------------
		// 2nd version
		dfx_1.clear();
		for_each( x.begin(), x.end(), [ & dfx_1 ] ( const auto & val ) { dfx_1.push_back( 
			
			deriv( 	
					[] ( const auto x ) { return 3 * pow( x, 5.0 ) * tanh( x ); }, 
				
					val ) 
		
		); } );



		// ---------------
		// 3rd version

		class QuadEq
		{
			double fa {-2.0}, fb {5.3}, fc {0.15};
		public:
			double operator() ( const double x )
			{
				return x * ( fa * x + fb ) + fc;
			}
		} qe;



		dfx_1.clear();
		for_each( x.begin(), x.end(), [ & dfx_1, & qe ] ( const auto & val ) { dfx_1.push_back( 
			
			deriv( 	
					std::bind( & QuadEq::operator(), qe, std::placeholders::_1 ), 
					val ) 
		
		); } );


	}


}




// --------------------------------------------------



