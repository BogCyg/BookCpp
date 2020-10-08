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








