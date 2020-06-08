///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////


#include <FL/FL_ask.H>
#include <filesystem>

#include "CurCalc_GUI.h"
#include "CloseWindow.h"



int main()
{
	CloseConsoleWindow();	// Get rid of the console window

	namespace fs = std::filesystem;
	// Get full path to the initialization file
	std::wstring iniPath( fs::current_path() / fs::path( CurrExchanger::initDefaultFileName ) );

	// Create the currency exchanger object
	auto curExchObj = OL_CE::CreateCurExchanger( OL_CE::nbp_addr, iniPath );
	if( ! curExchObj )
		return fl_alert( "Cannot load currency information (no ini file, no Internet) - exiting ..." ), -1;	// Exit with error code

	// Create GUI object with the provided currency exchanger object
	CC_GUI	gCC_GUI( * curExchObj );		

	// Run application 
	return gCC_GUI.Create_GUI();
}




