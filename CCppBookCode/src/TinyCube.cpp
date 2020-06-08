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
#include <vector>
#include <array>
#include <memory>
#include <cassert>




using std::vector, std::array;
using std::cout, std::endl;



template < typename ElemType >		// TEMPLATE preamble – ElemType is a placeholder 
class TinyCube						// for a later concrete type 
{
	public:

		static const int kDims = 3;		// the same for all objects of this class
		
		enum EDims { kx, ky, kz };		// shortcuts for 3 dimensions
	
	private:

		vector< ElemType >	fDataBuf;		// a vector to store data
		
		array< int, kDims >	fDim;

	public:

		// Parametric constructor - dx, dy, dz must be > 0
		TinyCube( const int dx, const int dy, const int dz )
			: fDim{ dx, dy, dz }, fDataBuf( dx * dy * dz, ElemType() )
		{
			assert( dx > 0 && dy > 0 && dz > 0 );
			assert( fDataBuf.size() == dx * dy * dz );
		}

		// Destructor does nothing; data will be deleted by the vector
		~TinyCube() {} 

	public:

		// Access elements by reference - bi-directional
		ElemType & Element( const int x, const int y, const int z )
		{ 
			const auto offset = ( z * fDim[ ky ] + y ) * fDim[ kx ] + x;
			return fDataBuf[ offset ]; 
		}

};


// Specialization for double
template <>
class TinyCube < double >
{
	public:
		
		static const int kDims = 3;		// the same for all objects of this class

		enum EDims { kx, ky, kz };		// shortcuts for 3 dimensions
	
	private:

		vector< double >	fDataBuf;		// a vector to store data
		
		array< int, kDims >	fDim;

	public:

		// Parametric constructor - dx, dy, dz must be > 0
		TinyCube( const int dx, const int dy, const int dz )
			: fDim{ dx, dy, dz }, fDataBuf( dx * dy * dz, 0.0 )
		{
			assert( dx > 0 && dy > 0 && dz > 0 );
			assert( fDataBuf.size() == dx * dy * dz );
		}


		// Destructor does nothing; data will be deleted by the vector
		~TinyCube() {} 

	public:

		// Access elements by reference - bi-directional
		auto & Element( const int x, const int y, const int z ) 
		{ 
			const auto offset = ( z * fDim[ ky ] + y ) * fDim[ kx ] + x;
			return fDataBuf[ offset ];		// subscript returns by reference
		}

};


template <>
class TinyCube < bool >
{
	public:

		static const int kDims = 3;		// the same for all objects of this class
		
		enum EDims { kx, ky, kz };		// shortcuts for 3 dimensions
	
	private:

		vector< bool >		fDataBuf;		// a vector to store data
		
		array< int, kDims >	fDim;

		// ...

	public:

		// Parametric constructor - dx, dy, dz must be > 0
		// Here we have just copied the original template
		// but for bool the internal representation can be
		// smaller since each byte can store 8 x (1/0) information.
		TinyCube( const int dx, const int dy, const int dz )
			: fDim{ dx, dy, dz }, fDataBuf( dx * dy * dz, false )
		{
			assert( dx > 0 && dy > 0 && dz > 0 );
			assert( fDataBuf.size() == dx * dy * dz );
		}


		// Destructor
		// does nothing, fDataBuf will be deleted by the unique_ptr
		~TinyCube() {} 

	public:

		// Access elements.
		// Here we have just copied the original template
		// but for bool the internal representation can be
		// smaller since each byte can store 8 x (1/0) information.
		// This requires changing access to the elements, though.
		bool Element( const int x, const int y, const int z )
		{ 
			const auto offset = ( z * fDim[ ky ] + y ) * fDim[ kx ] + x;
			return fDataBuf[ offset ];		// subscript returns by reference
		}

};






void MultiDimArray_Test( void )
{
	array< array< std::array< int, 2 >, 3 >, 4 >		_3D_int_array_obj;

	//_3D_int_array_obj[ 1 ][ 2 ][ 3 ] = -7;		// error
	_3D_int_array_obj[ 3 ][ 2 ][ 1 ] = -7;

	cout << _3D_int_array_obj[ 3 ][ 2 ][ 1 ];

}



void TinyCubeTest( void )
{
	TinyCube< double >	_3D_double_cube_obj( 2, 3, 4 );	// 2x3x4 cube of doubles

	_3D_double_cube_obj.Element( 1, 2, 3 ) = -3.14;
	assert( _3D_double_cube_obj.Element( 1, 2, 3 ) == -3.14 );


	typedef TinyCube< int > TinyCubeForInt;
	TinyCubeForInt			_3D_int_cube_obj( 1, 1, 1 );	// 1x1x1 cube of ints
	_3D_int_cube_obj.Element( 0, 0, 0 ) = -1700;
	assert( _3D_int_cube_obj.Element( 0, 0, 0 ) == -1700 );


	using StringCube = TinyCube< std::string >;
	StringCube		_3D_string_cube_obj( 3, 2, 1 );	// 3x2x2 cube of strings
	_3D_string_cube_obj.Element( 2, 1, 0 ) = "John";
	assert( _3D_string_cube_obj.Element( 2, 1, 0 ) == "John" );

}








