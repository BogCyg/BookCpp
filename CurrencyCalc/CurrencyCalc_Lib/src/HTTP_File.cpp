///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////




#include "HTTP_File.h"

#if _WIN32

	#include <urlmon.h>

	#pragma comment(lib, "urlmon.lib")

#else

#endif


namespace CppBook
{


bool	HTTP_File_Body_Windows::Load_HTTP_File( const std::wstring & internet_addr, const std::wstring & localName )
{
#if _WIN32   // Should be 1 on 32 bit and 64 bit Windows
	return URLDownloadToFile ( NULL, internet_addr.c_str(), localName.c_str(), 0, NULL ) == S_OK;
#else
	return false;
#endif
}




}	// CppBook


///////////////////////////////////////

// This can go to a differetn .cpp file
namespace CppBook
{


bool	HTTP_File_Body_Linux::Load_HTTP_File( const std::wstring & internet_addr, const std::wstring & localName )
{
#if __linux__   // Should be 1 on 32 bit and 64 bit Linux
	return false;		// To be implemented
#else
	return false;
#endif
}




}	// CppBook


///////////////////////////////////////

// This can go to a differetn .cpp file
namespace CppBook
{


bool	HTTP_File_Body_MacOS::Load_HTTP_File( const std::wstring & internet_addr, const std::wstring & localName )
{
#if macintosh   // Should be 1 on Apple
	return false;		// To be implemented
#else
	return false;
#endif
}




}	// CppBook




