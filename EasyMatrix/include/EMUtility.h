///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////


// Own header in " "
#include "EMatrix.h"




// Add two matrices, return the result:
// c = a + b
// Dimensions of a and b must be the same.
EMatrix		AddMatrix( const EMatrix & a, const EMatrix & b );

// Multiply two matrices, return the result:
// c = a * b
// Dimensions of a and b must comply for multiplication
EMatrix		MultMatrix( const EMatrix & a, const EMatrix & b );


// Prints contents of a matrix m on the screen
void ShowMatrix( const EMatrix & m );

// Solicitates a user to enter all matrix data 
// from the keyboard.
void AskUserForMatrixData( EMatrix & m );

// Does random initialization of a matrix m
void RandInit( EMatrix & m );





#if EM_VER > 1

// Overloaded operators 

EMatrix		operator + ( const EMatrix & a, const EMatrix & b );

EMatrix		operator * ( const EMatrix & a, const EMatrix & b );

#endif








