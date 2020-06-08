/*

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

*/


#include <stdlib.h>
#include <stdio.h>



/* Simple struct to store coeffs of the quadratic equation */
struct QE
{
	float a, b, c;
};

/* struct QE is a tag and we need to introduce the type QE */
/* The name of a struct is a tag, rather than the type. */
typedef		struct QE			QE;




/* Initialize QE to 0 */
void Init_0( QE * qe )
{
	qe->a = 0.0;
	qe->b = 0.0;
	qe->c = 0.0;
}

/* Initialize QE to values */
void Init( QE * qe, float a, float b, float c )
{
	qe->a = a;
	qe->b = b;
	qe->c = c;
}




/* Computes a discriminant of the quadratic equation */
float ComputeDelta( QE * qe )
{
	return qe->b * qe->b - 4.0 * qe->a * qe->c;
}



/* Function to test the behavior of QE */
void Test_QE( void )
{
	/* These objects are not initialized */
	QE		eq_1;
	QE		eq_2;

	/* Initialize eq_1 to 0 */
	Init_0( & eq_1 );
	Init_0( & eq_2 );


	float a = 0.0, b = 0.0, c = 0.0;

	/* Read 3 params from the keyboard. scanf accepts pointers, so & is used */
	scanf( "%f%f%f", & a, & b, & c );

	/* Directly set data members of eq_2 */
	eq_2.a = a;
	eq_2.b = b;
	eq_2.c = c;

	/* Compute a discriminant */
	float delta = ComputeDelta( & eq_2 );

	/* Print delta on the screen */
	printf( "delta=%lf\n", delta );

}







