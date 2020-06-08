///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////


// System headers in < >
#include <iostream>
#include <fstream>


// Own header in " "
#include "EMUtility.h"
#include "MarsXorShift.h"


void RandInit( EMatrix & m );



// Here we show hot to use "raw" RealMatrix
void Easy_Matrix_First_Test( void )
{

	// -------------------------
	// Using RealMatrix as it is

	RealMatrix		m = {
							{ 2, 2, 0, 11 },
							{ 3, 4, 5, 0 },
							{ -1, 2, -1, 7 }
						};

	// Add next row
	m.push_back( { 5, 3, 5, -3 } );

	// Accumulate elements except the diagonal
	double non_diagonal_sum {};

	for( Dim r = 0; r < m.size(); ++ r )
		for( Dim c = 0; c < m[ 0 ].size(); ++ c )
			if( c != r )
				non_diagonal_sum += m[ r ][ c ];

	std::cout << "Sum of m except the diagonal " << non_diagonal_sum << std::endl;


}




#if EM_VER == 1


// To use a function we need only to provide its declaration.
// However, to make a full program, function definitions must
// be also added in some of the source files.
void		AskUserForMatrixData( EMatrix & m );
void		ShowMatrix( const EMatrix & m );
EMatrix		MultMatrix( const EMatrix & a, const EMatrix & b );




// Here we show how to use EMatrix wrapper
void Easy_Matrix_Second_Test( void )
{
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << "In this example we will:" << std::endl;
	std::cout << "* Create a 3x4 matrix M1 (you will be asked to enter its data)" << std::endl;
	std::cout << "* Print M1" << std::endl;
	std::cout << "* Create a 4x2 matrix M2 (you will be asked to enter its data)" << std::endl;
	std::cout << "* Print M2" << std::endl;
	std::cout << "* Compute and print a product M1 * M2" << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;


	EMatrix		matrix_1( 3, 4 );
	AskUserForMatrixData( matrix_1 );

	std::cout << "You've just entered M1 - is it correct?" << std::endl;
	ShowMatrix( matrix_1 );


	EMatrix		matrix_2( 4, 2 );
	AskUserForMatrixData( matrix_2 );

	std::cout << "You've just entered M2 - is it correct?" << std::endl;
	ShowMatrix( matrix_2 );


	std::cout << "The matrix product of M1 * M2 is:" << std::endl;
	ShowMatrix( MultMatrix( matrix_1, matrix_2 ) );



}





#else // EM_VER > 1


// Here we show hot to stream out and in EMatrix objects
void Easy_Matrix_Third_Test( void )
{
	EMatrix	matrix_1( 3, 3 );

	RandInit( matrix_1 );


	{
		std::cout << matrix_1;	// stream it to the screen	
		
		std::ofstream oma( "ema.txt" );

		oma << matrix_1;	// with the same operator << stream it to the file
	}

	{
		EMatrix matrix_2( 1, 1 );	// there must be at least 1 element

		std::ifstream ima( "ema.txt" );

		ima >> matrix_2;			// stream in from an input file

		std::cout << std::endl << matrix_2 << std::endl;		// show it on the screen
	}


	// With overloaded operators operations are even easier
	//std::cout << "M1 + M1 = \n" << matrix_1 + matrix_1 << std::endl;	// 'operator +' is ambiguous
//	std::cout << "M1 + M1 = \n" << matrix_1.operator + ( matrix_1 ) << std::endl;	
//	std::cout << "M1 * M1 = \n" << matrix_1 * matrix_1 << std::endl;

}


// Here we show hot to stream out and in EMatrix objects
void Easy_Matrix_Fourth_Test(void)
{
	EMatrix	matrix_1( 200, 200 ), matrix_2( 200, 200 );

	RandInit( matrix_1 );
	RandInit( matrix_2 );

//	EMatrix	matrix_3( matrix_1.operator + ( matrix_1 ) );

	EMatrix	matrix_4( matrix_1 * matrix_2 );

//	std::cout << matrix_3[10][20] << std::endl;
	std::cout << matrix_4[10][20] << std::endl;


	// With overloaded operators operations are even easier
	//std::cout << "M1 + M1 = \n" << matrix_1 + matrix_1 << std::endl;	// 'operator +' is ambiguous
	//std::cout << "M1 + M1 = \n" << matrix_1.operator + (matrix_1) << std::endl;
	//std::cout << "M1 * M1 = \n" << matrix_1 * matrix_1 << std::endl;

}


void Easy_Matrix_Zeroth_Test( void )
{
	EMatrix		m ( 2, 3 );
	std::cin >> 	m; 		// Call the insertion operator upon std::cin and m
	std::cout << 	m; 		// Call the extraction operator with std::cout and m


	// The same as the call
	operator << ( std::cout, m );	// Call the extraction operator with std::cout and m
}



#endif





