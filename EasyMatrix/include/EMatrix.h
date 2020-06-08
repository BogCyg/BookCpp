///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////






// ----------------------------------------
// Part I

#include <iostream> 
#include <vector>







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

// Set to 1 for FIRST simple version
// Set to 2 for the SECOND object-oriented version
#define EM_VER 2


#if EM_VER == 1


// -----------------------------------------------------------
// Ver. 1.0



// EMatrix is a wrapper to RealMatrix. 
// A role of a wrapper is to facilitate some actions.
struct EMatrix
{


	RealMatrix	fData;	// data structure


	// A parametric constructor
	// rows, cols – number of rows and columns of a matrix (should be > 0)
	// initVal – an initial value of elements of a matrix
	EMatrix( Dim rows, Dim cols, DataType initVal = 0.0 )
		: fData( rows, RealVec( cols, initVal ) )
	{	
		// matrix == a vector of vectors of double
		assert( cols > 0 );
		assert( rows > 0 );
	}


	// Helpers
	auto	GetCols( void ) const { return fData[ 0 ].size(); }
	auto	GetRows( void ) const { return fData.size(); }

};

#else



// -----------------------------------------------------------
// Ver. 2.0



class EMatrix
{
	// -----------------------------------------------------------
	// Ver. 1.0

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


	// -----------------------------------------------------------
	// Ver. 2.0

	// As a result of overloaded subscript operators 
	// instead of m.fData[2][3] we can write directly m[2][3] 
	auto &			operator[] ( Dim idx ) { return fData[ idx ]; }			
	const auto &	operator[] ( Dim idx ) const { return fData[ idx ]; }

	// We need only these two pairs of functions to have a range-based for loop
	auto			begin() { return fData.begin(); }
	auto			end()	{ return fData.end(); }

	auto			begin() const { return fData.begin(); }
	auto			end()	const { return fData.end(); }




	// Let add some overloaded arithmetical operators
	EMatrix &		operator += ( const EMatrix & b );	// this will probably change this object
	EMatrix			operator + ( const EMatrix & b ) const;
	// We can add other operators here ...


	// friends are functions that can freely access fData
	friend std::ostream & operator << ( std::ostream & o, const EMatrix & matrix );
	friend std::istream & operator >> ( std::istream & i, EMatrix & matrix );


};






// ----------------------------------------
// Part III

EMatrix		operator + ( const EMatrix & a, const EMatrix & b );

EMatrix		operator * ( const EMatrix & a, const EMatrix & b );





#endif




