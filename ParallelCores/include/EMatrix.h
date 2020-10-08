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






// ----------------------------------------
// Part I

#include <iostream> 
#include <vector>


#define USE_OPEN_MP		1




// A type alias declaration for a vector of double values (real approx.)
using RealVec = std::vector< double >;

// A type alias for vector dimensions (size)
using Dim		= RealVec::size_type;

// A type alias for vector type (e.g. double)
using DataType	= RealVec::value_type;


// A type alias for a vector of vectors with doubles = a real matrix
using RealMatrix = std::vector< RealVec >;



// ----------------------------------------
// Part II

#include <cassert>




class EMatrix
{

private:

	RealMatrix	fData;	// data structure (encapsulation)

public:

	// A parametric constructor
	EMatrix( Dim rows, Dim cols, DataType initVal = 0.0 )
		: fData( rows, RealVec( cols, initVal ) )
	{	// matrix == a vector of vectors of double
		assert( cols > 0 );
		assert( rows > 0 );
	}


	// Helpers
	auto	GetCols( void ) const { return fData[ 0 ].size(); }
	auto	GetRows( void ) const { return fData.size(); }


	// Thanks to this overloaded subscript operators 
	// instead of m.fData[2][3] we can write directly m[2][3] 
	auto &			operator[] ( Dim idx ) { return fData[ idx ]; }			
	const auto &	operator[] ( Dim idx ) const { return fData[ idx ]; }

	// We need only these two pairs of functions to have a range-based for loop
	auto			begin() { return fData.begin(); }
	auto			end()	{ return fData.end(); }

	auto			begin() const { return fData.begin(); }
	auto			end()	const { return fData.end(); }



	// friends are functions which can freely access fData
	friend std::ostream & operator << ( std::ostream & o, const EMatrix & matrix );
	friend std::istream & operator >> ( std::istream & i, EMatrix & matrix );


};






// ----------------------------------------

EMatrix		operator + ( const EMatrix & a, const EMatrix & b );

EMatrix		operator * ( const EMatrix & a, const EMatrix & b );





