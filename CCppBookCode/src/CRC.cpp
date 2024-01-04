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



#include <cassert>
#include <vector>



/////////////////////////////////////////////////////////////////
// Returns a remainder of the CRC sum.
/////////////////////////////////////////////////////////////////
//		
// INPUT:	crc - previously computed crc value
//			byte - new value to be reflected by the new crc		
//		
// OUTPUT:	new crc value		
//		
// REMARKS:
//			At the beginning the crc parameter should be set to 0.
//			The function counts 8-bit CRC for transmission of bytes	
//		
unsigned char CalcCRC( unsigned char crc, unsigned char byte )
{
	// A representation of the polynomial with bits reversed and omitted MSBit==1
	const unsigned short kPoly = 0xE0;

	unsigned short x { crc };
	x ^= byte;

	// Check each bit of x
	const auto kBitsInByte { 8 };
	for( auto count { 0 }; count < kBitsInByte; ++ count )
	{
		bool carry = ( x & 1 ) != 0;
		x = ( x >> 1 ) & 0x7fff;	// Shift right and mask
		if( carry ) 
			x ^= kPoly;				// XOR with the polynomial
	}

	return x & 0xFF;	// Return CRC as a single byte
}







void CRC_Test( void )
{

	std::vector< unsigned char >		data { 1, 7, 13, 7, 0, 0, 5, 55, 100 };

	unsigned char crc { 0 };

	for( auto d : data )
		crc = CalcCRC( crc, d );


	// To verify, if done again, the result should be 0
	data.push_back( crc );
	crc = 0;
	for( auto d : data )
		crc = CalcCRC( crc, d );

	assert( crc == 0 );

	// Simulate a bit error in the buffer
	data[ data.size() / 2 ] ^= 0x10;

	crc = 0;
	for( auto d : data )
		crc = CalcCRC( crc, d );

	assert( crc != 0 );


}


// --------------------------------------------------------



