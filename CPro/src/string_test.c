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
#include <string.h>
#include <ctype.h>



void C_string_test( void )
{
	char s1[ 13 ] = "Quick fox";
	char s2[] = "fox";

	/* Output length of both strings */
	printf( "len(s1)=%d, len(s1)=%d\n", strlen( s1 ), strlen( s2 ) );

	/* Check if strings are the same */
	printf( "cmp(s1,s2)=%d\n", strcmp( s1, s2 ) );

	char s3[ 64 ] = "\0";	/* Large buffer, empty string */
	strcpy( s3, s1 );		/* Copy s1 to s3 */
	printf( "cmp(s1,s3)=%d\n", strcmp( s1, s3 ) );

	strcat( s3, " jumped" ); /* Join two strings */
	printf( "s3=%s\n", s3 );

	/* Find if s2 is part of s1 */
	printf( "s2 is a part of s1: %s\n", strstr( s1, s2 ) != NULL ? "yes" : "no" );


	/* ----------------------------- */

	#define line_len 256
	char line_buf[ line_len ] = { 0 };

	/* Open a file to read in text mode */
	FILE * fp_in = fopen( "Fox.txt", "r" );

	if( fp_in )
	{
		if( fgets( line_buf, line_len, fp_in ) )
		{
			/* Line of text in the buffer - convert to uppercase */
			for( char * ptr = line_buf; * ptr; ++ ptr )
				* ptr = toupper( * ptr );

			FILE * fp_out = fopen( "FoxUpper.txt", "w" );
			if( fp_out )
			{
				fputs( line_buf, fp_out ); /* write it out */
				fclose( fp_out );
			}
		}
	
		fclose( fp_in );
	}

}


void C_memory_block_test( void )
{
	/* Alloc a buffer with text. Move by few chars to make room.  */

	#define BUF_SIZE	256

	char buf[ BUF_SIZE ];

	memset( buf, 0, BUF_SIZE ); /* fill buf with 0 */

	char * text = "quick brown fox.";

	/* Get text length + sentinel 0 */
	int text_total_len = strlen( text ) + 1;

	/* Copy text to buf */
	memcpy( buf, text, text_total_len );

	char * prefix = "The "; 

	/* Move to make room at the beginning of text */
	memmove( buf + strlen( prefix ), buf, text_total_len );

	/* Copy prefix but not 0 */
	memcpy( buf, prefix, strlen( prefix ) );

	printf( "%s\n", buf );

}





void C_heap_memory_block_test( void )
{
	/* Alloc a buffer with text. Move by few chars to make room.  */

	/* Size of heap allocation can be set in run-time. */
	int buf_size = 256;

	/* Allocate memory on the heap */
	unsigned char * buf = malloc( buf_size );

	if( buf == NULL )
		return; /* Error, cannot allocate memory. Exiting.*/

	memset( buf, 0x00, buf_size ); /* fill buf with 0 */

	char * text = "quick brown fox.";

	/* Get text length + sentinel 0 */
	int text_total_len = strlen( text ) + 1;

	/* Copy text to buf */
	memcpy( buf, text, text_total_len );

	char * prefix = "The "; 

	/* Move to make room at the beginning of text */
	memmove( buf + strlen( prefix ), buf, text_total_len );

	/* Copy prefix but not 0 */
	memcpy( buf, prefix, strlen( prefix ) );

	printf( "%s\n", buf );

	free( buf ); /* Do NOT FORGET to release memory. */
}


void C_string_len( void )
{
	char text[] = { "The quick brown fox" };

	int cnt = 0;

	// Measure the length of the text
	while( * ( text + cnt ) != 0 )
		cnt ++;

	printf( "\"%s\" contains %d letters\n", text, cnt );
}


// -----------------------------------------------------


void BuiltIn_ArrayTest_1( void )
{

	//#define kArrSize 12
	enum Dim { kTabSize = 4 };
	int val = 3;
	int tab[ kTabSize ] = { val };	// Init all elems to 0

	// Set new values to arr
	for( int i = 0; i < kTabSize; ++ i )
		tab[ i ] = i;

	// arr is a const pointer to its first element,
	// so we can also write this
	for( int i = 0; i < kTabSize; ++ i )
		* ( tab + i ) = i;



	// Array access via the pointer
	int * tab_ptr = tab;		// tab is constant, tab_ptr is variable
	for( int i = 0; i < kTabSize; ++ i )
		* tab_ptr ++ = 0;

	// A size of an array can be found with the sizeof as follows
	#define ARR_SIZE(arr)	( sizeof( arr ) / sizeof( arr[0] ) )

	for( int i = 0; i < ARR_SIZE( tab ); ++ i )
		printf( "%d, ", tab[ i ] );

	printf( "\n\n" );
}


void BuiltIn_ArrayTest_2( void )
{
	/* Multidimensional arrays */
	enum Dims { kRows = 2, kCols = 2 };

	/* kRows is external, kCols internal index */ 
	double affineMatrix[ kRows ][ kCols ] = { 0.0 };

	/* Set all off-diagonal elements to -1 */
	for( int r = 0; r < kRows; ++ r )
		for( int c = 0; c < kCols; ++ c )
			if( r != c )
				affineMatrix[ r ][ c ] = -1.0;

	/* The same with pointers */
	for( int r = 0; r < kRows; ++ r )
		for( int c = 0; c < kCols; ++ c )
			if( r != c )
				* ( * ( affineMatrix + r ) + c ) = -1.0;


}




