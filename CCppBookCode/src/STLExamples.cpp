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




#include <string>
#include <iostream>
#include <iterator>


using namespace std;


void iterators_ex( void )
{
	string str { "The quick brown fox." };

	// Copy string to the screen
	copy( str.begin(), str.end(), ostream_iterator< string::value_type >( cout ) );
	cout << endl;

	// Copy string to the screen
	// cbegin is const begin
	copy( str.cbegin(), str.cend(), ostream_iterator< string::value_type >( cout ) );
	cout << endl;

	// Copy string in reverse order to the screen
	// rbegin is reverse begin
	copy( str.rbegin(), str.rend(), ostream_iterator< string::value_type >( cout ) );
	cout << endl;


}



