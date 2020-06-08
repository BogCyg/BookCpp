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




void C_UnionTest( void )
{
	union LFValue
	{
		long	fLongVal;
		double	fDoubleVal;
	} LF_Obj = { 0 }; /* Create LF_obj and init to 0 */

	/* With a union we gain size */
	printf( "s_long = %d, s_float = %d, s_LFValue = %d\n", sizeof( long ), sizeof( double ), sizeof( union LFValue ) );

	/* From LF_Obj we can use only one field at a time */
	LF_Obj.fLongVal = 120; /* now we use LF_Obj as long */

	/* Print the bytes */
	int i = 0;
	printf( "\nBytes of LF_Obj.fLongVal = 120\n" );
	for( i = 0; i < sizeof( union LFValue ); ++ i )
		printf( "%x\t", * ( (unsigned char*)& LF_Obj + i ) );

	LF_Obj.fDoubleVal = 120.0; /* Now we use LF_Obj as a float */

	printf( "\nBytes of LF_Obj.fDoubleVal = 120.0\n" );
	for( i = 0; i < sizeof( union LFValue ); ++ i )
		printf( "%x\t", * ( (unsigned char*)& LF_Obj + i ) );

	/* However, type punning through a union is not recommended */
	/*printf( "\nfLongVal = %ld, fDoubleVal = %lf\n", LF_Obj.fLongVal, LF_Obj.fDoubleVal );*/

}




