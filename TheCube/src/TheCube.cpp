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




#include "TheCube.h"







#include <iostream>
#include <fstream>
#include <cassert>





std::ostream & operator << ( std::ostream & o, const TheCube & cube )
{
	// Out data as binary streams
	o.write(	reinterpret_cast< const char * >(  & cube.fDim[ 0 ] ), 
		sizeof( cube.fDim ) );		// sizeof returns size of the whole array 
	o.write(	reinterpret_cast< const char * >(  cube.fDataBuf.get() ), 
		cube.Size() * sizeof( TheCube::value_type ) );
	return o;
}


std::istream & operator >> ( std::istream & i, TheCube & cube )
{
	// First read dimensions
	i.read( reinterpret_cast< char * >( & cube.fDim[ 0 ] ), sizeof( cube.fDim ) );	
	if( i )		// Check if the stream OK
	{
		cube.fDataBuf = std::make_unique< TheCube::value_type [] >( cube.Size() );

		const auto cube_bytes = cube.Size() * sizeof( TheCube::value_type );
		// read() accepts a number of bytes
		i.read( (char*)cube.fDataBuf.get(), cube_bytes );	// Read the rest of the data 

		assert( i );
	}
	return i;
}







