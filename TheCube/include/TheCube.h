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
#include <fstream>
#include <array>
#include <cassert>




using std::cout, std::cin, std::endl;	// Name aliases




class TheCube
{
public:

	using value_type = double;
	using size_type = int;

	static const size_type kDims { 3 };		// the same for all objects of this class

	enum EDims { kx, ky, kz };				// shortcuts for 3 dimensions

private:

	// A 'smart' pointer to the 1D buffer with all data
	std::unique_ptr< value_type [] >	fDataBuf;

	// An array of 3 dimensions
	std::array< size_type, kDims >		fDim;

public:


	// Default constructor
	TheCube( void )			// empty buffer
		:	fDataBuf( nullptr ), fDim { 0, 0, 0 }	
	{
	}

	// Parametric constructor
	TheCube( const int dx, const int dy, const int dz )
		: fDim{ dx, dy, dz }
	{
		// Allocate a 1D array of value_type elements and assign to fDataBuf
		fDataBuf = std::make_unique< value_type [] >( fDim[ kx ] * fDim[ ky ] * fDim[ kz ] );
	}


	// Copy constructor
	TheCube( const TheCube & cube )
	{
		fDim = cube.fDim;				// First copy the dimensions

		const auto	elems = fDim[ kx ] * fDim[ ky ] * fDim[ kz ];

		// Whatever was held by fDataBuf will be first deleted.
		// Then, a new buffer will be allocated and attached to fDataBuf
		fDataBuf = std::make_unique< value_type [] >( elems );

		// Finally, "deep" copy data to the "this" buffer
		//                dest             source                 bytes
		std::memcpy( fDataBuf.get(), cube.fDataBuf.get(), elems * sizeof( value_type ) );	
	}

	// Assignment operator
	TheCube & operator = ( const TheCube & cube )
	{
		// We cannot copy if the same object
		if( this != & cube )
		{
			fDim = cube.fDim;					// First copy the dimensions

			const auto	elems = fDim[ kx ] * fDim[ ky ] * fDim[ kz ];

			// Whatever was held by fDataBuf will be first deleted
			// Then new block will be allocated and assigned to fDataBuf
			fDataBuf = std::make_unique< value_type [] >( elems );

			// Finally, deep copy data to the "this" buffer		
			//         dest               source                 bytes
			memcpy( fDataBuf.get(), cube.fDataBuf.get(), elems * sizeof( value_type ) );	
		}
		return * this;
	}


	// Destructor - if planning to derive, make it virtual
	~TheCube() {}


	// Move constructor (C++11+)
	TheCube( TheCube && cube ) noexcept
		: fDataBuf( nullptr ), fDim { 0, 0, 0 }
	{
		// Swap (exchange) dimensions
		std::swap( fDim, cube.fDim );

		// Swap held pointers
		fDataBuf.swap( cube.fDataBuf );
	}



	// Move assignment operator (C++11+)
	TheCube & operator = ( TheCube && cube ) noexcept
	{
		// Swap all data members between: this and cube
		std::swap( fDim, cube.fDim );

		// Only exchange the pointers - do not copy the buffers!
		fDataBuf.swap( cube.fDataBuf );		

		return * this;
	}



public:

	// Getters/setters

	// Because of EDims as a parameter we cannot ask for non exisitent dimension
	auto	GetDim( EDims which_one ) const { return fDim[ which_one ]; }

	// Access elements by reference - bi-directional
	auto & Element( const int x, const int y, const int z ) const
	{ 
		const auto offset = ( z * fDim[ ky ] + y ) * fDim[ kx ] + x;
		return * ( fDataBuf.get() + offset ); 
	}

	auto	Size( void ) const { return fDim[ kx ] * fDim[ ky ] * fDim[ kz ]; }

	// It is a const function but it allows for data change
	auto	GetDataBuf( void ) const { return fDataBuf.get(); }

public:

	// Streaming operators are functions external to this class
	friend std::ostream & operator << ( std::ostream & o,	const	TheCube & cube );
	friend std::istream & operator >> ( std::istream & i,	TheCube & cube );

};


