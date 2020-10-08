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



#include <algorithm>
#include <random>

#include "TheCube.h"




TheCube	RetAbsCube( const TheCube & inCube );


// Test function for TheCube class
void TheCube_Test( void )
{
	const int dx { 15 }, dy { 13 }, dz { 11 };

	TheCube		cube( dx, dy, dz );

	// Random Mersenne twister
	std::mt19937		rand_gen{ std::random_device{}() }; 	

	// Fill the cube with random values; ref is a reference wrapper
	std::generate( cube.GetDataBuf(), cube.GetDataBuf() + cube.Size(), std::ref( rand_gen ) );
	//std::generate( cube.GetDataBuf(), cube.GetDataBuf() + cube.Size(), std::mt19937( std::random_device{}() ) );

	// Cannot move - only copy from cube since it is used further on
	TheCube		mirror_cube( cube );	


	cube.Element( 5, 7, 9 ) = -100.0;		// set an element
	assert( cube.Element( 5, 7, 9 ) == -100.0 );		// read and check

	std::ofstream outFile( "TheCube.bin", std::ios::binary );
	outFile << cube;
	outFile.close();	// so we can open it in the next line

	std::ifstream inFile( "TheCube.bin", std::ios::binary );
	TheCube		testCube;
	inFile >> testCube;


	// Check if data the same byte after byte
	assert( std::memcmp( cube.GetDataBuf(), testCube.GetDataBuf(), cube.Size() * sizeof( TheCube::value_type ) ) == 0 );


	// Call the move constructor
	TheCube abs_cube( RetAbsCube( cube ) ); 

	// Explicitly call the move assignment operator
	cube = static_cast< TheCube && >( abs_cube );	


	std::ofstream outAbsFile( "TheAbsCube.bin", std::ios::binary );
	outAbsFile << cube;

}



TheCube	RetAbsCube( const TheCube & inCube )
{
	// Create an empty return cube of the same dimensions
	TheCube outCube(	inCube.GetDim( TheCube::kx ), 
		inCube.GetDim( TheCube::ky ), 
		inCube.GetDim( TheCube::kz ) );		

	// Transform all elements to their absolute values
	std::transform( inCube.GetDataBuf(), inCube.GetDataBuf() + inCube.Size(), 
		outCube.GetDataBuf(), [] ( TheCube::value_type v ) { return std::fabs( v ); } );
	return outCube;			// Invokes the move semantics
}







