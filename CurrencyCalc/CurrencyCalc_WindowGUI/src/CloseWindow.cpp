///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////


#if _WIN32
	#include <windows.h>
#endif



#include "CloseWindow.h"




#if _WIN32


///////////////////////////////////////////////////////////
// This function closes the console window
///////////////////////////////////////////////////////////
//		
// INPUT:
//			none
//		
// OUTPUT:
//			none
//		
// REMARKS:
//		
//	
void CloseConsoleWindow( void )
{
	// Find a window and close it
	HWND h; 
	TCHAR szOldTitle[ MAX_PATH ]; 
	GetConsoleTitle( szOldTitle, MAX_PATH );
	h = FindWindow( NULL, szOldTitle );
	ShowWindow( h, SW_HIDE ); 
}

#else

void CloseConsoleWindow( void )
{
	// do we need it?

}

#endif





