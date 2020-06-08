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



// Let's include the definition of the TComplex class
#include "Complex.h"



namespace CppBook
{


	// Used to check against division by 0
	const double kDivThresh { 1e-36 };


	///////////////////////////////////////////////////////////
	// Overloaded arithmetic operators for the TComplex class
	///////////////////////////////////////////////////////////

	// +
	TComplex TComplex::operator + ( const TComplex & second_op ) const
	{
		TComplex retComplex( fRe + second_op.fRe, fIm + second_op.fIm );
		return retComplex;		// Return object by value
	}

	TComplex & TComplex::operator += ( const TComplex & second_op )
	{
		fRe += second_op.fRe, fIm += second_op.fIm;
		return * this;			// Return object by refernce
	}



	// -
	TComplex TComplex::operator - ( const TComplex & second_op ) const
	{
		TComplex retComplex( fRe - second_op.fRe, fIm - second_op.fIm );
		return retComplex;
	}

	TComplex & TComplex::operator -= ( const TComplex & second_op )
	{
		fRe -= second_op.fRe, fIm -= second_op.fIm;
		return * this;
	}


	// *
	TComplex TComplex::operator * ( const TComplex & second_op ) const
	{
		TComplex retComplex( fRe * second_op.fRe - fIm * second_op.fIm, fRe * second_op.fIm + fIm * second_op.fRe );
		return retComplex;
	}

	TComplex & TComplex::operator *= ( const TComplex & second_op )
	{
		fRe = fRe * second_op.fRe - fIm * second_op.fIm;
		fIm = fRe * second_op.fIm + fIm * second_op.fRe;
		return * this;
	}


	// div - can throw an exception of division by zero
	TComplex TComplex::operator / ( const TComplex & second_op ) const
	{
		auto div = second_op.fRe * second_op.fRe + second_op.fIm * second_op.fIm;
		if( fabs( div ) < kDivThresh )	// don't divide by small number or 0 (better than: div == 0.0)
			throw std::overflow_error( "div by 0 error" );	// if so, then throw simple text exception

		auto re = fRe * second_op.fRe + fIm * second_op.fIm;
		re /= div;

		auto im = fIm * second_op.fRe - fRe * second_op.fIm;
		im /= div;

		return TComplex( re, im );		// Return object by value
	}

	TComplex & TComplex::operator /= ( const TComplex & second_op )
	{
		auto div = second_op.fRe * second_op.fRe + second_op.fIm * second_op.fIm;
		if( fabs( div ) < kDivThresh )
			throw std::overflow_error( "div by 0 error" );

		auto re = fRe * second_op.fRe + fIm * second_op.fIm;
		re /= div;

		auto im = fIm * second_op.fRe - fRe * second_op.fIm;
		im /= div;

		// Copy the values
		fRe = re;
		fIm = im;

		return * this;		// Return object by refernce
	}



	/////////////////////////////////////////////////////////
	// Streaming operators - they do not need to be declared
	// as friends

	std::istream & operator >> ( std::istream & i, TComplex & complex )
	{
		double re {}, im {};
		i >> re;
		i >> im;
		complex.SetRe( re );
		complex.SetIm( im );
		return i;
	}

	std::ostream & operator << ( std::ostream & o, const TComplex & complex )
	{
		o << complex.GetRe() << " " << complex.GetIm();
		return o;
	}

	/////////////////////////////////////////////////////////

	double abs( const TComplex & c )
	{
		return std::sqrt( c.GetIm() * c.GetIm() + c.GetRe() * c.GetRe() );
	}


}		// end of the CppBook namespace

/////////////////////////////////////////////////////////



