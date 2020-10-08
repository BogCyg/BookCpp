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
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>


#include <memory>
#include <string>


using std::cout, std::cin, std::endl;
using std::string, std::vector;



void ReferenceTest( void )
{

	int x = 10;

	int & x_ref = x;

	{
		x		= 12;		// Directly set x,		x == 12
		x_ref	= 12;		// Indirectly set x,	x == 12 


		// The same with a pointer
		int * x_ptr = & x;
		* x_ptr = 12;		// Indirectly set x,	x == 12

	}


	///////////////////////////////////////////////////

	{
		// int & x_ref;			// Wrong - a reference must be initialized !

		// int & x_ref = 12;		// Wrong - a non-const reference to const !

		const int & kBase_10 = 10;// Ok, kBase_10 refers to value 10 and cannot be changed
	}


	{


		const int & x_const_ref = x;

		cout << x_const_ref << endl;		// Ok - read only
		// x_const_ref = 12;		// Wrong - const ref only to read 



		int y = 13;

		x_ref = y;		// x == 13
		// Let's observe that x_ref is not re-connected to a new object "y".
		// Instead, the object "x" was assigned a new value of "y", i.e. 13.

	}

	{

		// A reference can be made to other objects but another reference.
		// Here is also a difference compared to pointers.

		int x = 12;						// Ok
		int & x_ref = x; 				// Ok
		// int & & x_ref_ref = x_ref;		// Wrong - reference to reference not allowed !

	
		{

			// a reference to reference by aliasing
			using	int_ref = int &;
			using	int_ref_ref = int_ref &;

			int_ref_ref		xx_ref { x };	// the same as int & 

			xx_ref = 12;	// change object x to 12

			* ( & xx_ref ) = 13;	// we can take an address / dereference via reference
									// and change object x to 13

			cout << xx_ref << endl;
		}

	}


	{
		std::string s;

		std::string & sr { s };

	}



	{
		double sum = 0.0;
		double & sum_ref = sum;

		// const ref to constant
		const double & kPi { 3.1415926535 };

		sum		= kPi;	// set kPi to sum
		sum_ref = kPi;	// the same via ref
	}





}


// Very nasty error - a function returns a reference
// to an object which was destroyed. 
// "returning address of local variable or temporary: char_counter_vec"
// DO NOT USE THIS FUNCTION !!!!!!!!!!!!!!
vector< int > &		CountCharsIn( const string & fileName )
{

	vector< int >	char_counter_vec;


	// open the file, read line by line
	// count chars and push them back to char_counter_vec
	// ...

	// finally, return the counted results

	assert( false );			// do NOT use this code

	return char_counter_vec;	// WRONG!! char_counter_vec will be destroyed
								// since it is local to this function
}

// Return a copy (or move)
vector< int >		CountCharsIn_copy_( const string & fileName )
{

	vector< int >	char_counter_vec;


	// open the file, read line by line
	// count chars and push them back to char_counter_vec
	// ...

	// finally, return the counted results

	return char_counter_vec;	// OK, char_counter_vec can be copied (in effect it 
								// will be moved since the compiler is smart enough
								// and employs Return Value Optimization (RVO) here)
}




// Try the versions
void CountCharsIn_Test( void )
{
	const string fileName( "Test.txt" );

	vector< int >	v;
		
	v = CountCharsIn( fileName );	// serious error lurks here ...

	v = CountCharsIn_copy_( fileName );	// ok


	// display results
	copy( v.begin(), v.end(), std::ostream_iterator< int >( cout, " " ) );

}



// Returns an uppercase copy of str
string	Conv2Upper( const string & str )
{
	string ret_str; 	// transform will copy-and-convert to uppercase
	transform( str.begin(), str.end(), back_inserter( ret_str ), toupper );
	return ret_str;		// return ret_str via a temp object 
						// - use move semantics thanks to string implementation
}


void Right_ReferenceTest( void )
{

	string &&	rr1( "A fox" );	// rr1 refers to a temporary object holding "A fox"



	string	s1( "is quick" );

	//string && rr2( s1 );		// error, cannot directly assign lref to rref

	string && rr2( " " + s1 );		// OK, bound to a temporary object
	


	string s2( s1 );			// copy s1 to s2, both strings can be used
	
	//string s3( static_cast< string && >( s1 ) );	// move s1 to s3 - no longer use of s1
	string s3( std::move( s1 ) );	// move s1 to s3 - no longer use of s1



	// output concatenation of strings
	cout << rr1 + rr2 << endl;



	string && rr3( Conv2Upper( s3 ) );	// take over an uppercase temporary


	// uppercase version
	cout << Conv2Upper( rr1 ) + " " + rr3 << endl;


	//A fox is quick
	//A FOX IS QUICK



	using int_vec = vector< int >;

	// rref to a temporary object
	int_vec && rv1 { 1, 5, 7, 13 };	

	// create iv1 and init based on rv1
	int_vec iv1( rv1 );		


	// create iv2 and (move) overtake data from iv1
	int_vec iv2( move( iv1 ) );	
	// iv1 is empty and should not be used


	// ------------------------

	// rvalue can be assigned only to const lref
	// int & ir1 = 25 + 7;		// error, non const ref cannot be initialized with const
	const int & ir1 = 25 + 7;	// OK, 32
	// ir1 = 55;				// error, assigning to const

	// rvalue can be assigned to rref
	int && ir2 = 25 + 7;	// OK, ir2 ==> 32
	ir2 = 55;				// OK, ir2 ==> 55


}


namespace ROV
{

	class MMatrix
	{	// ...
	};


	MMatrix		operator + ( const MMatrix & a, const MMatrix & b )
	{
		MMatrix		ret_m;
		// add ...
		return ret_m;	// apply ROV if possible
	}

	void MMatrixTest( void )
	{
		MMatrix	x, y, z;
		// ...
		z = x + y;
	}



}




void UniversalReference_Test( void )
{
	string str( "is quick" );

	auto && rref = "Fox";	// a universal reference + type deduction ==> rref

	auto && lref = str;		// a universal reference + type deduction ==> lref

	lref = " " + lref;		// append space in front of str

	cout << rref + lref << endl;	// "Fox is quick"
}



// ----------------------------------------




// The idea is to convey (forward) the type
// of a reference.
template< typename T >
auto a_min( T && a, T && b ) 
{
	return a < b ? std::forward< T >( a ) : std::forward< T >( b );
}

void a_min_test( void )
{
	string str_f( "Fox" ), str_d( "Dog" );

	string a = a_min( str_f, str_d );		// l-ref

	string c = a_min( string( "fox" ), string( "dog" ) );	// r-ref

	string b = a_min( "Fox", "Dog" );		// r-ref

	// mixed types, cannot deduce the type
	//string d = a_min( str_f, string("") );	

}


// ----------------------------------
// With S we can see what is going on
class S
{
	int fS {};
public:

	S( int v = 0 ) : fS( v ) { cout << "S(" << fS << ")" << endl; }

	S( const S & s ) : fS( s.fS ) { cout << "S&(=" << s.fS << ")" << endl; }

	S( const S && s ) : fS( s.fS ) { cout << "S&&(=" << s.fS << ")" << endl; }


public:

	bool operator < ( const S & s ) { return fS < s.fS; }
};


// If we remove std::forward in the a_min, then
// only the copy constructor will be called.
void s_min_test( void )
{
	S f( 1 ), d( 2 );			// default
	
	S a = a_min( f, d );		// l-ref
	
	S c = a_min( S( 3 ), S( 4 ) );		// r-ref
	
	S b = a_min( 5, 6 );				// default

	// mixed types, cannot deduce the type
	//S d = a_min( str_f, S( 7 ) );	

}


// ------------------------------------------------------------
// An example of PERFECT FORWARDING, i.e. lref goes as na lref,
// and rref as an rref, without unwanted conversion. 

void overloaded_fun( std::string & v ) 
{
	std::cout << "I'm lref version with " << v << std::endl;
}

void overloaded_fun( std::string && v ) 
{
	std::cout << "I'm rref version with " << v << std::endl;
}

template< typename T >
void pass_through( T && val ) 
{
	// Here is the main TRICK - try to run in two variants:
	// (1) with std::forward to "perfectly forward" passed rval refs
	// (2) with no std::forward
	overloaded_fun( std::forward< T >( val ) );	
	//overloaded_fun( static_cast< T&& >( val ) );		// std::forward is equivalent to this
}

void PassThroughTest( void )
{
	std::string str { "Brown" };

	pass_through( str );					// launch with lref (always lref)
	pass_through( "Fox" );					// launch with rref (always rref)
	pass_through( std::move( str ) );		// launch with rref but without std::forward will be through lref

}



