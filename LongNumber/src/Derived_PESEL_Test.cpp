///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2020
///////////////////////////////////////////////////////







#include "Derived_PESEL.h"




void Derived_PESEL_Test( void )
{
	std::cout << "Size with inherited object: " << sizeof( PESEL ) << std::endl;
	std::cout << "Size of PESEL::BaseClass: " << sizeof( PESEL::BaseClass ) << std::endl;
}


