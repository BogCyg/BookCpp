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



#include "EMatrix.h"
#include <iterator>
#include <string>
#include <sstream>





// Stream out a matrix to the stream out. Assume text mode.
std::ostream & operator << ( std::ostream & out, const EMatrix & matrix )
{
	for( const auto & row : matrix/*.fData*/ )	// go row-by-row
	{
		for( const auto & data : row )	// go data in single row
			out << data << "\t";

		out << std::endl;		// print new line
	}

	return out;		// return the stream, so they can be chained
}

// Stream in a matrix from the stream in. Assume text mode.
std::istream & operator >> ( std::istream & in, EMatrix & matrix )
{
	// Dimensions have to be determined from the data layout.
	// Each new line constitutes a new row of a matrix.
	// So, we have to read strings line by line, and
	// from each string read data by data.

	matrix.fData.clear();		// get rid of whatever there was

	std::string str;	// an empty string
	while( getline( in, str ) )	// read the whole line into the string
	{
		// Create a string-stream from a string
		std::istringstream istr( str );

		using DType_Iter = std::istream_iterator< DataType >;

		// Here we move 
		matrix.fData.emplace_back(	std::make_move_iterator( DType_Iter{ istr } ), 
									std::make_move_iterator( DType_Iter{} ) );


	}

	return in;		// return the stream, so they can be chained
}




