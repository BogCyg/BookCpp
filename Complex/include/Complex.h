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






// This include is to use the istream and ostream classes
#include <iostream>




///////////////////////////////////////////
// Our own namespace to uniquely identify
// contained classes
///////////////////////////////////////////
namespace CppBook
{


////////////////////////////////////////////
// A class to represent complex numbers
////////////////////////////////////////////
class TComplex
{
	private:

		// Data members should be in the private section of the class

		double fRe {};		// real part
		double fIm {};		// imaginary part

	public:


		///////////////////////////////////////////////////////////
		// Default constructor
		///////////////////////////////////////////////////////////
		TComplex( void ) 
			: fRe( 0.0 ), fIm( 0.0 )	// special data intialization
		{
			fRe = 0;					// such initialization is possible but 
		}								// the above is better


		///////////////////////////////////////////////////////////
		// A parametric constructor 
		///////////////////////////////////////////////////////////
		TComplex( double re, double im ) : fRe( re ), fIm( im ) {}
		
		///////////////////////////////////////////////////////////
		// Copy constructor - make this object and make its state
		// the same as the supplied one (i.e. "c"). 
		// default means to copy fRe and fIm from "c".
		///////////////////////////////////////////////////////////
		TComplex( const TComplex & c ) = default;

		///////////////////////////////////////////////////////////
		// Overloaded assignment operator - default means to 
		// copy fRe and fIm.
		///////////////////////////////////////////////////////////
		TComplex & operator = ( const TComplex & c ) = default;

		///////////////////////////////////////////////////////////
		// Destructor, does nothing, but stated explicitly
		///////////////////////////////////////////////////////////
		~TComplex() = default;			

	public:

		///////////////////////////////////////////////////////////
		// Converting constructor - allows the creation of TComplex
		// from a double type object (i.e. it is a conversion 
		// from double to TComplex).
		///////////////////////////////////////////////////////////
		TComplex( double re ) : fRe( re ), fIm( 0.0 ) {}


	public:

		// Getters & Setters to access data members of the class
		double GetRe( void ) const { return fRe; }	// "const" since we only read 
		double GetIm( void ) const { return fIm; }	// data, not changing the state
		
		void SetRe( double re ) { fRe = re; }		// here we change the state
		void SetIm( double im ) { fIm = im; }		// so it is not "const"

	public:

		///////////////////////////////////////////////////////////
		// Overloaded "equal" compare operator
		///////////////////////////////////////////////////////////
		bool operator == ( const TComplex & c ) const
		{
			return fRe == c.fRe && fIm == c.fIm;
		}

	public:

		///////////////////////////////////////////////////////////
		// Overloaded arithmetic operators
		///////////////////////////////////////////////////////////

		// +
		TComplex operator + ( const TComplex & second_op ) const;

		TComplex & operator += ( const TComplex & second_op );


		// -
		TComplex operator - ( const TComplex & second_op ) const;

		TComplex & operator -= ( const TComplex & second_op );


		// *
		TComplex operator * ( const TComplex & second_op ) const;

		TComplex & operator *= ( const TComplex & second_op );


		// div - can throw and exception of division by zero
		TComplex operator / ( const TComplex & second_op ) const;

		TComplex & operator /= ( const TComplex & second_op );

};


///////////////////////////////////////////////////////////////
// Overloaded streaming operators - always outside the class

std::istream & operator >> ( std::istream & i, TComplex & complex );

std::ostream & operator << ( std::ostream & o, const TComplex & complex );

///////////////////////////////////////////////////////////////

// Returns module of a TComplex
double abs( const TComplex & c );

}		// end of the CppBook


/////////////////////////////////////////////////////////



