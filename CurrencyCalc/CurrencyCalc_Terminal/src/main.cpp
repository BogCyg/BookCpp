///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////





#include <filesystem>
#include <io.h>
#include <fcntl.h>


#include "CurrencyCalcPlayGround.h"

#if 0
namespace CurrExchanger
{

	void Run( void );

}


namespace CurrExchanger
{
	namespace OnLine_CurrExchanger
	{
		void Run( void );
	}
}
#endif


#include <iostream>
#include <locale>


int main( void )
{
	setlocale( /*LC_ALL*/LC_CTYPE, "Polish" );	// to display national letters (but don't change financial format ',' vs '.')
	CurrExchanger::OnLine_CurrExchanger::Run();
	return 0; // Although not absolutely required, return the value from main
}






