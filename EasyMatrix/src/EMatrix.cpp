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





#if EM_VER > 1

// Stream out a matrix to the stream out. Assume text mode.
std::ostream & operator << ( std::ostream & out, const EMatrix & matrix )
{
	for( const auto & row : matrix/*.fData*/ )	// go row-by-row
	{
		for( const auto & data : row )	// go through the data in single row
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
	// from each string read item by data item.

	matrix.fData.clear();		// get rid of whatever was there 

	std::string str;	// an empty string
	while( getline( in, str ) )	// read the entire line into the string
	{
		// Create a string-stream from a string
		std::istringstream istr( str );

#define SIMPLE 1
#if SIMPLE 

		DataType	data {};		// temporary data
		RealVec		one_row;		// at first, create the empty row
		while( istr >> data )		// read from the string-stream to data
			one_row.push_back( data );	// fill one row

		matrix.fData.emplace_back( one_row );	// emplace the row into the matrix

#else
		using DType_Iter = std::istream_iterator< DataType >;

		// Here we move 
		matrix.fData.emplace_back(	std::make_move_iterator( DType_Iter{ istr } ), 
									std::make_move_iterator( DType_Iter{} ) );

#endif

	}

	return in;		// return the stream, so they can be chained
}




	// Let add some overloaded arithmetical operators
	EMatrix &		EMatrix::operator += ( const EMatrix & b )	
	{
		assert( GetRows() == b.GetRows() );	// dim must be the same
		assert( GetCols() == b.GetCols() );

		for( Dim row = 0; row < b.GetRows(); ++ row )
			for( Dim col = 0; col < b.GetCols(); ++ col )
				fData[ row ][ col ] += b[ row ][ col ];

		return * this;	
	}

	EMatrix			EMatrix::operator + ( const EMatrix & b ) const
	{
		// Where does matrix "a" come from? It is "this".
		assert( GetRows() == b.GetRows() );	// dim must be the same
		assert( GetCols() == b.GetCols() );

		EMatrix	c { * this };	// Make c the same as a

		c += b;		// call the add and assing operator +=

		return c;	
	}




#endif






#if 0


// Stream in a matrix from i.
// Assume text mode.
std::istream & operator >> ( std::istream & i, EMatrix & matrix )
{
	// Dimensions have to be determined from the data layout.
	// Each new line constitutes a new row of a matrix.
	// So, we have to read strings line by line, and
	// from each string read item by data item.

	matrix.GetMatrixData().clear();		// get rid of whatever was there
	
	for( std::string str; getline( i, str ); )
	{
		// Create a string-stream from a string
		std::istringstream istr( str );

		using DType_Iter = std::istream_iterator< DataType >;

		// Here we move 
		matrix.fData.emplace_back(	std::make_move_iterator( DType_Iter{ istr } ), 
									std::make_move_iterator( DType_Iter{} ) );
	}

	return i;
}


#endif












