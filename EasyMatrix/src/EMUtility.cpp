///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////


// System headers in < >
#include <iostream>


// Own header in " "
#include "EMUtility.h"
#include "MarsXorShift.h"



#if EM_VER == 1


// -----------------------------------
// Input/output functions



// Ask the user to enter values for matrix m 
// from the keyboard.
void AskUserForMatrixData( EMatrix & m )
{
	const Dim kCols = m.GetCols();
	const Dim kRows = m.GetRows();

	for( Dim r = 0; r < kRows; ++ r )
	{
		std::cout << "Enter data for row no. " << r << " of " << kRows << std::endl;
		for( Dim c = 0; c < kCols; ++ c )
		{
			std::cout << c << ": ";
			std::cin >> m.fData[ r ][ c ];		// read a value from the keyboard
		}
	}
	std::cout << std::endl;	// new line again
}



// Prints contents of a matrix m on the screen
void ShowMatrix( const EMatrix & m )
{
	for( const auto & row : m.fData )	// go row-by-row
	{
		for( const auto & data : row )	// go through the data in single row
			std::cout << data << "\t";	// separate data with tab

		std::cout << std::endl;		// print new line
	}
	std::cout << std::endl;	// new line again
}





// -----------------------------------
// Math functions



// Add two matrices, return the result:
// c = a + b
// Dimensions of a and b must be the same.
EMatrix		AddMatrix( const EMatrix & a, const EMatrix & b )
{
	assert( a.GetRows() == b.GetRows() );	// dim must be the same
	assert( a.GetCols() == b.GetCols() );

	EMatrix	c { a };	// Make c the same as a

	for( Dim row = 0; row < b.GetRows(); ++ row )
		for( Dim col = 0; col < b.GetCols(); ++ col )
			c.fData[ row ][ col ] += b.fData[ row ][ col ];

	return c;
}

// Multiply two matrices, return the result:
// c = a * b
// Dimensions of a and b must comply for multiplication
EMatrix		MultMatrix( const EMatrix & a, const EMatrix & b )
{
	const auto a_cols = a.GetCols();
	const auto a_rows = a.GetRows();

	const auto b_cols = b.GetCols();
	const auto b_rows = b.GetRows();	

	assert( a_cols == b_rows );	// Dimensions must be the same

	EMatrix	c( a_rows, b_cols, 0.0 );	// Output matrix has such dimensions

	for( Dim ar = 0; ar < a_rows; ++ ar )	// Traverse rows of a
		for( Dim bc = 0; bc < b_cols; ++ bc )	// Traverse cols of b
			for( Dim ac = 0; ac < a_cols; ++ ac ) // Traverse cols of a == rows of b
				c.fData[ ar ][ bc ] += a.fData[ ar ][ ac ] * b.fData[ ac ][ bc ];

	return c;
}
	




// -----------------------------------
// Random init functions



// Does random initialization of a matrix m
void RandInit( EMatrix & m )
{
	MarsXorShift	randMachine;
	for( auto & row : m.fData )		// go row-by-row
		for( auto & data : row )	// go through the data in a single row
			data = randMachine.GetNext() & 0xFFFF;	// cast, type promotion
}





// ---------------------------------------------------------------


#else	// EM_VER > 1





// Overloaded operators 

// It can be used as follows: c = a + b;
EMatrix		operator + ( const EMatrix & a, const EMatrix & b )
{
	assert( a.GetRows() == b.GetRows() );	// dim must be the same
	assert( a.GetCols() == b.GetCols() );

	EMatrix	c { a };	// Make c the same as a

	for( Dim row = 0; row < b.GetRows(); ++ row )
		for( Dim col = 0; col < b.GetCols(); ++ col )
			c[ row ][ col ] += b[ row ][ col ];

	return c;
}

// It can be used as follows: c = a * b;
EMatrix		operator * ( const EMatrix & a, const EMatrix & b )
{
	const auto a_cols = a.GetCols();
	const auto a_rows = a.GetRows();

	const auto b_cols = b.GetCols();
	const auto b_rows = b.GetRows();	

	assert( a_cols == b_rows );	// Dimensions must be the same

	EMatrix	c( a_rows, b_cols, 0.0 );	// Output matrix has such dimensions

	for( Dim ar = 0; ar < a_rows; ++ ar )	// Traverse rows of a
		for( Dim bc = 0; bc < b_cols; ++ bc )	// Traverse cols of b
			for( Dim ac = 0; ac < a_cols; ++ ac ) // Traverse cols of a == rows of b
				c[ ar ][ bc ] += a[ ar ][ ac ] * b[ ac ][ bc ];

	return c;
}




// Does random initialization of a matrix m
void RandInit( EMatrix & m )
{
	MarsXorShift	randMachine;
	for( auto & row : m )			// go row-by-row
		for( auto & data : row )	// go through data in a single row
			data = randMachine.GetNext() & 0xFFFF;	// cast, type promotion
}


#endif




