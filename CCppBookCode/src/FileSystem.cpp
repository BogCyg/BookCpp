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
#include <iterator>
#include <vector>
#include <string>
#include <cassert>

#include <fstream>
#include <filesystem>



using namespace std;

namespace fs = std/*::experimental*/::filesystem;




void PrintDirTree( const fs::path & inDirPath, const wstring & separator = L"" )
{
	if( ! fs::exists( inDirPath ) || ! fs::is_directory( inDirPath ) )
		return;		// exit if wrong path (not existing or not a dir)

	// Iterate through

	for( const auto & file_obj : fs::directory_iterator( inDirPath ) )
	{
		// Ok, file_obj can be either a file or another nested directory

		if( fs::is_directory( file_obj ) )
		{
			wcout << separator << file_obj.path().filename() << endl;
			auto len = wstring( file_obj.path().filename() ).size();
			wcout << separator << wstring( len, L'-' ) << endl;

			PrintDirTree( file_obj, separator + L"\t" );	// recursive call - go inside the tree
		}
		else
		{
			if( fs::is_regular_file( file_obj ) )
			{
				// We are interested in regular files
				wcout << separator << file_obj.path().filename() << endl;
			}
			else
			{
				// Other type (pipe, socket, block, etc.)

			}

		}



	}


}




void PrintDirTree_TEST( const wstring & inDirPath )
{
	PrintDirTree( inDirPath );

}


//////////////////////////////////////////////////////////////////////




void RecursivelyTraverseDirectory( const wstring & inDirPath_str )
{
	const fs::path inDirPath( inDirPath_str );

	if( fs::exists( inDirPath ) && fs::is_directory( inDirPath ) )

		for( auto	iter = fs::recursive_directory_iterator( inDirPath ); 
					iter != fs::recursive_directory_iterator(); ++ iter  )

			wcout	<< std::wstring( 3 * iter.depth(), L' ' ) 
					<< ( fs::is_directory( * iter ) ? L"[+]" : L"|--" ) 
					<< iter->path().filename() << endl;
	
}


void DisplayPathParts( const wstring & inPath_str )
{
	const fs::path inPath( inPath_str );

	// We can iterate through different parths of a path
	for( const auto & p : inPath )
		wcout << p << "\n";
}


void DisplayDirFileInfo( const wstring & inPath_str )
{
	const fs::path inPath( inPath_str );

	wcout << L"exists - \t\t" << fs::exists( inPath ) << endl;

	// Let's call all important members of fs::path
	wcout << L"filename - \t\t"			<< inPath.filename() << endl;
	wcout << L"stem - \t\t"				<< inPath.stem() << endl;	
	wcout << L"extension - \t\t"		<< inPath.extension() << endl;	
			    
	// If a file, then print its size in bytes
	if( fs::is_regular_file( inPath ) )
		std::cout << "file size - \t\t" << fs::file_size( inPath ) << endl;

	wcout << L"parent_path - \t\t"		<< inPath.parent_path() << endl;
	wcout << L"relative_path - \t\t"	<< inPath.relative_path() << endl;
			    
	wcout << L"root_directory - \t\t"	<< inPath.root_directory() << endl;
	wcout << L"root_name - \t\t"		<< inPath.root_name() << endl;
	wcout << L"root_path - \t\t"		<< inPath.root_path() << endl;
}


void DisplaySpaceInfo( const wstring & inPath_str )
{
	fs::space_info dir_space = fs::space( inPath_str );

	wcout << L"Space infor for: " << inPath_str << endl;

	wcout << L"capacity - \t\t"		<< dir_space.capacity << endl;
	wcout << L"free - \t\t"			<< dir_space.free << endl;
	wcout << L"available - \t\t"	<< dir_space.available << endl;
}


void CreateDirAndFiles( const wstring & inDirPath_str, const wstring & subDir )
{
	try
	{
		// There are conversions std::(w)string <==> fs::path
		fs::path inDirPath( inDirPath_str );

		// Use overloaded operator /= to 
		inDirPath /= subDir;	// add sub directory

		// Create some directorie
		fs::path sub_1_path { inDirPath / L"SubDir_1" };
		fs::create_directories( sub_1_path );	// create subDir/_1

		fs::path sub_2_path { inDirPath / L"SubDir_2" };
		fs::create_directories( sub_2_path );	// create subDir/_2

		// Create a new file
		wofstream( sub_1_path / L"file_1.txt" ) << L"Fox";		

		// Create a second directory & file by fs::copy
		fs::copy(	sub_1_path / L"file_1.txt",		// from
					sub_2_path / L"file_2.txt",		// to
					fs::copy_options::overwrite_existing ); 

		// Move file_2.txt to the first directory
		fs::rename( sub_2_path / L"file_2.txt",		// from
					sub_1_path / L"file_2.txt" );	// to

		// Remove all dir and files - be careful!
		fs::remove_all( inDirPath );
	}
	catch( fs::filesystem_error & error )
	{
        wcout << error.what() << endl;
	}
}




// --------------------------------------------------------





///////////////////////////////////////////////////////////
// Transform a text file into another text
// file with all characters changed to uppercase.
///////////////////////////////////////////////////////////
void TransformFileToUppercase( void )
{
	ifstream inFl( "InFile.txt" );
	ofstream outFl( "OutFile.txt" );

	if( inFl.is_open() && outFl.is_open() )
		for( string str; getline( inFl, str ); outFl << str << endl )
			transform( str.begin(), str.end(), // Contains loop inside
				str.begin(), toupper );			
}


// --------------------------------------------------------




