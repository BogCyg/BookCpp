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







#include "Derived_PESEL.h"




void Derived_PESEL_Test( void )
{
	std::cout << "Size with inherited object: " << sizeof( PESEL ) << std::endl;
	std::cout << "Size of PESEL::BaseClass: " << sizeof( PESEL::BaseClass ) << std::endl;
}


