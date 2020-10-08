/*

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

*/


#include <stdlib.h>
#include <stdio.h>



/* Function declaration. */
void ToBinConvert( int val );


/* The CProg converts a decimalvalue into an 
   equivalent in one the bases: oct, bin, hex. 
   Param no. 1 is a decimal integer value. 
   An optional param no. 2 is the output base "oct", "bin", "hex" 
   If not provided, then the same value is displayed. */


/* C program starts with the main function (assumed C99) */
int main( int argc, char ** argv )
{

	printf( "Value converter. Calling format:\nCPro.exe dec_val [bin,oct,hex]\n" );

	switch( argc ) 		/* argc conveys the number of arguments */
	{
		case 2:

			{	/* Only one param - display as it is */
				int val = atoi( argv[ 1 ] ); /* Converts ASCII to int */
				printf( "%d [dec] = %d [dec]\n", val, val );
			}

			break;

		case 3:

			{	/* Two params */
				int val = atoi( argv[ 1 ] );
				char * base = argv[ 2 ];

				/* For the base we need to check only its first letter */
				switch( base[ 0 ] )
				{
					case 'h': /* check lowercase */
					case 'H': /* and uppercase at the same time */

						/* printf will do conversion for us */
						printf( "%d [dec] = 0x%x [hex]\n", val, val );
						break;

					case 'o':
					case 'O':

						/* printf will do the conversion for us */
						printf( "%d [dec] = 0%o [oct]\n", val, val );
				
						break;

					case 'b':
					case 'B':

						/* Here we need to do the conversion ourselves */
						printf( "%d [dec] = ", val ); 
						ToBinConvert( val ); 
						printf( " [bin]\n" );

						break;

					default:
				
						printf( "Wrong name param. Should be one of: [bin,oct,hex]\n" );
						break;	
				
				}

			}

			break;

		default:

			printf( "Call with 1 or 2 params.\nCPro dec_val [hex,oct,bin]\n" );
			break;
	
	}

	return 0;	/* Return value 0 indicates SUCCESS. */
}


/* Recursivly print bits in reverse order thanks to recursion. */
void ToBinConvert( int val )
{
	if( val > 1 )
		ToBinConvert( val >> 1 );	/* Recursive call */

	printf( "%d", val & 0x01 );		/* Print the last bit */
}




