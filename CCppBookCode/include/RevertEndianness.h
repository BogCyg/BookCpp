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
#include <type_traits>		// for is_unsigned_v



///////////////////////////////////////////////////////////
// Template function to change endianness of integer types
// i.e. it reverts order of bytes in the input arg.
// Example: 0x78ABCDEF will be changed to 0xEFCDAB78
///////////////////////////////////////////////////////////
//
// INPUT:
//			in - integer like type
// OUTPUT:
//			byte reversed version of in
//
// REMARKS:
//
//
template < typename T >
constexpr auto RevertEndianness( T in ) 
{
	//static_assert( std::is_unsigned< T >::value );
	static_assert( std::is_unsigned_v< T > );

	T out { 0 };
	for( auto i { 0 }; i < sizeof( in ); ++ i )		// rotate bytes
	{
		out <<= 8;
		out |= in & 0xFF;
		in >>= 8;
	}
	return out;
}



inline void RevertEndianness_Test( void )
{
	// RevertEndianness can be computed in the compilation time
	// Notice 'u' in 0xABCDu - this makes 0xABCD an unsigned constant
	std::cout << std::hex << std::uppercase << "ABCD" << "\t <-> "  
							<< RevertEndianness( 0xABCDu ) << std::endl;

	// Compilation time since argument is constexpr
	constexpr unsigned int ui { 0xABCDu };
	std::cout << std::hex << std::uppercase << ui << "\t <-> " 
							<< RevertEndianness( ui ) << std::endl;

	long l { 0x01234567 };
	// This will not compile since l is not an 'unsigned' type
	//std::cout << std::hex << l << "\t <-> " 
	//						<< RevertEndianness( l ) << std::endl;

	unsigned long ul { 0x01234567ul };
	std::cout << std::hex << std::uppercase << ul << "\t <-> " 
							<< RevertEndianness( ul ) << std::endl;

	unsigned long long ull { 0x0123456789ABCDEFull };
	std::cout << std::hex << std::uppercase << ull << "\t <-> " 
							<< RevertEndianness( ull ) << std::endl;
}








