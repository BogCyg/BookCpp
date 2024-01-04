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





#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cassert>

#include <cmath>




using namespace std;




namespace User
{
	class SafeSqrt
	{
		public:

			static bool sqrt( const double & val, double & result )
			{
				if( val >= 0.0 )
					return result = ::sqrt( val ), true;		// call global scope sqrt, then return true
				return false;
			}
	};
}


void workerFun( void )
{


}




// A matrix with row or column -major data organisation
template < typename T >
class OrdMatrixFor
{
		T * fData;			// data buffer
		int	fCol, fRow;		// dimensions

		T * (OrdMatrixFor::*data_offset)( int c, int r );	// pointer to a member function
		
		// Two alternative member functions for data access in memory
		T * col_major_ind( int c, int r ) { return fData + c * fRow + r; }
		T * row_major_ind( int c, int r ) { return fData + r * fCol + c; }	// default

	public:
		// If row_major is true (default), data is set row-major
		OrdMatrixFor( int col, int row, bool row_major = true )
			:	fCol( col ), fRow( row ),	// init the pointer member function
				data_offset( row_major == true ?	& OrdMatrixFor::row_major_ind : 
													& OrdMatrixFor::col_major_ind ) 
		{
			fData = new T [ col * row ];	// alloc buffer
		}
		~OrdMatrixFor() { delete [] fData; }		// free memory
		
		// Access an element using right data offset (two equivalent alternatives)
		void SetElem( int c, int r, double v ) { * (this->*data_offset)( c, r ) = v; }
		double GetElem( int c, int r ) { return * ((*this).*data_offset)( c, r ); }
};




// Convert Cartesian (x, y) into polar (mag, angle) coordinates
bool Cart_2_Polar( const double & x, const double & y, double & mag, double & angle )
{
	// write everything in 1 line
	return fabs( x ) > 1e-32 ? mag = sqrt( x * x + y * y ), angle = atan( y / x ), true : false;
}


//double get_PI()
//{
//    double pi;
//    __asm
//    {
//        fldpi
//        fstp pi
//    }
//    return pi;
//}
//
//double PI = get_PI();




// constexpr for the compile time constant
constexpr double kPi = 3.141592653589793238463;

// User-defined literal - to convert xx_deg into radians
constexpr long double operator"" _deg ( long double deg )
{
    return deg * kPi / 180.0;
}

void UserTypeConstant_Test( void )
{
	//                          cos expects radians
	cout << "cos( 30_deg )=" << cos( 30.0_deg ) << endl;
}


//constexpr long double operator"" _inn ( long double deg )
//{
//    return deg*3.141592/180;
//}


void OperatorReview( void )
{
	//assert( false );

	// GROUP 0
	{


		double x = 1.3, sigma = 0.5;
		double gauss_val = exp( - x * x / ( 2.0 * sigma * sigma ) );


		const double kPi = 3.14159;
		// [=] capture denotes accessing external objects by value
		auto area_fun = [=] ( const double & r ) { return kPi * r * r ; };
		cout << area_fun( 13.7 ) << endl;	// area of a circle with r=13.7

	}


	cout << endl;



	// GROUP 1
	{
		cout << "Enter a floating point value to compute its square root: ";

		double x {}, res {};
		cin >> x;		// user enters a value
		if( User::SafeSqrt::sqrt( x, res ) == true )
			cout << "sqrt(" << x << ")=" << res << endl;
		else
			cout << "A value must be positive." << endl;
	}


	char * ptr = "The book";
	char first_letter = * ptr ++;
	char third_letter = * ++ ptr;

	char T = * ptr ++, h = * ptr ++;


	double r = 13.0;
	const double kPi = 3.14159;
	double circ = 2.0 * kPi * r;



	long slider_position = 256;

	long initial_slider_pos {};		// let's set this to 75% of the slider_position

	initial_slider_pos = 75 / 100 * slider_position;	// oops, 0 ?
	initial_slider_pos *= 75 / 100;						// 0 again
	initial_slider_pos = 75 * slider_position / 100;	// 192

	initial_slider_pos = 0.75 * slider_position;	// ok, but implicit type conversions


	// GROUP 2
	{
		// The class (struct) to hold partial accuracies of a classifier
		struct Accuracy 
		{ 
			double fTP, fFP, fTN, fFN; // true-positive, false-positive, etc.
			Accuracy( void ) : fTP{}, fFP{}, fTN{}, fFN{} {}
		} a;	// let's define the class "Accuracy" and the object "a"

		a.fTP ++;		// let's access and increase fTP
		// ...

		//Accuracy * ptr = new Accuracy;	// create on a heap
		//ptr->fTP ++;	// access and increast fTP through a pointer
		// ...
		//delete ptr;		// don't forget to get rid of the object

		Accuracy * ptr = & a;	// create a pointer ptr and make it point at a
		ptr->fTP ++;	// access and increast fTP through a pointer

		(&a)->fTP ++;	// can do this way
	}




	// Group 3
	{
	

		{
			// Create a 2D array
			vector< vector< int > >	table = {	{ 1, 2, 3 },
									{ 4, 5, 6 },
									{ 7, 8, 9 },
								};

			double sum {};	

			// let's compute a sum of square roots of all elements in "table"
			for( size_t r = 0; r < table.size(); ++ r )
				for( size_t c = 0; c < table[0].size(); ++ c )
					sum += sqrt( double ( table[r][c] ) );	// type conversion and call sqrt()
															
		}


		{
			// Create a 2D array
			const int kRows = 3, kCols = 4;
			int	table[ kRows ][ kCols ] = {		{ 1, 2, 3, 4 },
												{ 5, 6, 7, 8 },
												{ int {} }	// fill last row with "default" int's (i.e. 0)
											};

			double sum {};	// default "double", the same effect as sum = 0.0

			// let's compute a sum of square roots of all elements in "table"
			for( int r = 0; r < kRows; ++ r )
				for( int c = 0; c < kCols; ++ c )
					sum += sqrt( double ( table[ r ][ c ] ) );	// type convert and call sqrt()
					//sum += sqrt( (double) * ( * ( table + r ) + c ) );	// alternatively use this: through pointer and old style cast
															
		}



		struct XXX
		{
			// Copy length bytes from src to dst memory area
			void MemCopy( unsigned char * src, unsigned char * dst, int length )
			{
				while( length -- > 0 )		// copy length elements
					* dst ++ = * src ++;	// copy bytes, then advance pointers
			}
	
	
		};


		{
		
			void workerFun( void );	// function declaration

			try 
			{
				workerFun();		// call some action, can throw an exception
			}
			catch( std::exception & e )		// catch exception
			{
				cerr << "Caught: "	<< e.what( ) << endl;	// find what it is
				cerr << "Type: "	<< typeid( e ).name( ) << endl;	// print to error stream
			}
			catch( ... ) 
			{
				cerr << "Unknown error" << endl;
			}		
		
		}




	}




	// Group 4
	{
	
		// sizeof
		int x = 5;
		int dummy = sizeof x ++;


		{
			int dummy = sizeof ( unsigned char );
		}


		{
			// Not well spaced in memory
			struct NotTooGood
			{
				char	c {};
				double	d {};
				int		i {};
			};
		
			// The same information but less bytes
			struct BetterPacked
			{
				double	d {};				
				int		i {};				
				char	c {};
			};

			cout << "NotTooGood : " << sizeof( NotTooGood ) << " - " << alignof( NotTooGood ) << endl;

			cout << "BetterPacked : " << sizeof( BetterPacked ) << " - " << alignof( BetterPacked ) << endl;


		}




		UserTypeConstant_Test( );


		{
			long arr[ 16 ];	// array of 16 long integers
			// a way to compute the number of elems of an array
			assert( sizeof( arr ) / sizeof( arr[0] ) == 16 );

			long * arr_ptr = arr; // make a pointer to the first elem of arr

			int sizeof_arr_ptr = sizeof( arr_ptr );
			// sizeof( arr_ptr ) returns size of the pointer by itself (not an array!)
			assert( sizeof( arr_ptr ) != sizeof( arr ) );	

			long ( & ref_arr )[ 16 ] = arr;	// make a reference to long [16]
			int sizeof_ref_arr = sizeof( ref_arr );
			// reference returns size of the array
			assert( sizeof( ref_arr ) / sizeof( ref_arr[0] ) == 16 ); 

			cout << "sizeof ok" << endl;
		}


		double a {}, b {};
		// ...
		double p = - b / ( + 2.0 * a );	// unary + before the binary *


		class AAA
		{
			public:
		
				// Copy memory starting from the higher addresses down
				void BackwardMemCopy( unsigned char * dst, unsigned char * src, int num_of_bytes )
				{
					src += num_of_bytes;	// src is one address after the source buffer
					dst += num_of_bytes;	// dst is one address after the destination buffer

					while( num_of_bytes -- > 0 )
						* -- dst = * -- src;	// First decrement, then copy bytes
						//* ( dst = dst - 1 ) = * ( src = src - 1 );	// First decrement, then copy bytes
				}
		

				void test( void )
				{
					// ...
					const int kBytes = 256;
					unsigned char source[ kBytes ];
					unsigned char destination[ kBytes ];
					// ...
					BackwardMemCopy( & destination[ 0 ], & source[ 0 ], kBytes );

				
				}
		
		};


		class FFFFF
		{
			typedef short DATA_TYPE;
			// For a given type kSignMask has 1 only on its MSB
			const int kSignMask = 1 << 8 * sizeof( DATA_TYPE ) - 1;
			// ~kSignMask holds all 1s except MSB
			DATA_TYPE DataValueAbs( DATA_TYPE value ) { return value & ~kSignMask; }	// works with sign/mag format
		};




		char * text = "The quick brown fox";
		std::cout << text << " @ 0x";
		std::cout.setf( std::ios::hex, std::ios::basefield );
		std::cout << (size_t) text << " address." << endl;


		ifstream inputFile( "image.raw", ios::binary | ios::in );

		std::cout.setf( std::ios::dec, std::ios::basefield );

		// new and delete

		class MiniMatrix
		{
				double * fData;		// data buffer
				int	fCol, fRow;		// dimensions
		
			public:

				MiniMatrix( int col, int row ) : fCol( col ), fRow( row ) 
				{
					fData = new double [ col * row ];	// alloc buffer
				}
				~MiniMatrix() { delete [] fData; }		// free memory
		
				void SetElem( int c, int r, double v ) { * ( fData + r * fCol + c ) = v; }
				double GetElem( int c, int r ) { return * ( fData + r * fCol + c ); }
		};


		struct CommExcept_Handler
		{
			enum { kExcSize = 256 };	// exception vector size
			// Assembly code for this handler goes here (just an example ...)
			const unsigned char asm_code[ kExcSize ] = { 0x01, 0x02, 0x03, 0x04 };	// the rest fill with 0
		};

		size_t	CommExcept_Addr = 0x00000200;	// Comm Exception vector address (in uP space)



		class A
		{
				const double kPi = 3.14159;
			public:
				double circumference( double r ) { return 2.0 * kPi * r; }
				double area( double r ) { return kPi * r * r; }

			public:
				double get_circle( double (A::*p)( double ), double radius )
				{
					return (this->*p)( radius );		// to call through "p" we need an object (this)
				}
		};

		A	obj;
		double radius = 123.0;
		cout << obj.get_circle( & A::circumference, radius );
		cout << obj.get_circle( & A::area, radius );




		// In computing, row-major order and column-major order are methods for 
		// storing multidimensional arrays in linear storage such as random access memory.

		// The difference between the orders lies in which elements of an array are contiguous in memory. 
		// In a row-major order, the consecutive elements of a row reside next to each other, whereas the same holds true for consecutive elements of a column in a column-major order.

		const int kCols = 13, kRows = 20;
		OrdMatrixFor< double >	matrix_r( kCols, kRows, true ), matrix_c( kCols, kRows, false );
		matrix_r.SetElem( 1, 2, 3.0 );
		matrix_c.SetElem( 1, 2, 3.0 );


		/*
		// Interesting constructions ....
		{

			int x = 100;


			while( x --> 0 ) // read: (x--) > 0 
			{
				printf( "%d ", x );
			}

			while( 0 <-------------------- x )
			{
			   printf( "%d ", x );
			}

			// Out: 90 80 70 60 50 40 30 20 10
		}
		*/


	}




	// Group 5
	{
		double T_Cels {}, T_Fahr { 100.0 };

		T_Cels = 5 / 9 * ( T_Fahr - 32 );		// oops, always 0, why?
		
		T_Cels = 5.0 / 9.0 * ( T_Fahr - 32.0 );	// better with floating point data

	
		int year = 2020;	// Check whether it is a leap year 
		// Divides by 4 and not by 100, or divides by 400
		bool is_leap_year = ( year % 4 == 0 ) && ( year % 100 != 0 ) || ( year % 400 == 0 );

	}


	// Group 6
	{
		int	x = 7;
		int y = -8;
		int z = 0;

		z = x + y;		// "z" becomes -1
		z = x - y;		// 15

	}




	// Group 7
	{
		int	x = 13;

		// << as binary and overloaded operator
		cout <<   x << 1   << endl;		// print 13, then 1 ==> 131
		cout << ( x << 1 ) << endl;		// mult by 2 ==> 26
		cout << ( x >> 1 ) << endl;		//  div by 2 ==> 6


		// Right shifts are logical or arithmetical? Let's make a mask
		const unsigned char kMask_Arithm = ~ 0 >> 1;
		const unsigned char kMask_Logic = ~ 0U >> 1;

		cout << "kMask_Arithm = " << ios::hex << kMask_Arithm << endl;
		cout << "kMask_Logic = " << ios::hex << kMask_Logic << endl;

		// Let's check on signed and unsigned values

		// We expect arithmetic shifts for the signed 
		char sx = -69;	// == 0b10111011
		sx >>= 1;		// == 0b11011101
		sx <<= 1;		// == 0b10111010

		// Logical shifts for the unsigned
		unsigned char uy = 187;		// == 0b10111011
		uy >>= 1;					// == 0b01011101
		uy <<= 1;					// == 0b10111010

	}


	// Group 8
	{
		float	a = 2.0f, b = 10.0f, c = 4.0f;		// add suffix f to define float constants 
		float	delta = b * b - 4.0f * a * c;
		float	x1 = 0.0f, x2 = 0.0f;

		if( fabs( a ) > 1e-12f && delta >= 0.0f )	// better than: a != 0.0
		{
			float sq_delta = sqrt( delta );
			x1 = ( - b - sq_delta ) / ( 2.0f * a );
			x2 = ( - b + sq_delta ) / ( 2.0f * a );
		}


	}



	// Group 9
	{

		char c = getchar();
		if( c == 'Y' || c == 'y' )		// operator == has higher precedence than ||
		{
			// Proceed if user pressed 'Y' or 'y'...
		}


	}



	// Group 10 - 12
	{

		unsigned char bulb_control_register = 0xAB;		// '1' means 'on', '0' is 'off'
		unsigned char bulb_index = 3;					// counting from the right


		// turn on bulb at bulb_index
		bulb_control_register = bulb_control_register | ( 1 << bulb_index );

		// turn off bulb at bulb_index
		bulb_control_register = bulb_control_register & ~( 1 << bulb_index );


		// toggle bult at bulb_index: if on, then off, and vice versa
		bulb_control_register = bulb_control_register ^ ( 1 << bulb_index );	// ^ is not the power operator


	}



	// Group 13, 14
	{
		cout << "Enter a floating point value: ";
		double x {};
		cin >> x;

		const double kValMin = -1.0, kValMax = +2.0;	// define the range

		if( x >= kValMin && x <= kValMax )	// check whether "x" is in the range
		{
			// proceed ...
		}


		// see previous definitions ...
		if( x < kValMin || x > kValMax )	// check whether "x" is out of the range
		{
			// proceed ...
		}

		cout << endl << endl;
	}





	// Group 15 (this is a separate group in C)
	{
		double x {};
		// ...
		// sign_of_x contais -1 or 1 depending on a sign of "x"
		int sign_of_x = x < 0.0 ? -1 : +1;
	}





	// Group 15 (ctd.)
	{
		short s = -31000;	// pay attention to the maximum range of a variable
		const long double kPi = 3.14159265358979;
		vector< long > v = { 1, 2, 3, 4 };	// assign with a initialization list

		{
			const double kPi = 3.14159;
			double angle { 60.0 };	// first in degs

			angle /= 180.0;
			angle *= kPi;		// now angle is in rad
		}

		// The number of bits reserved for the "short" type
		int bits_in_type = sizeof( short );
		bits_in_type <<= 3;		// mult by 8


		
		{
			unsigned int a = 0xAB, b = 0xCD;

			a ^= b; 			// Exchanging two int's without an auxiliary variable
			b ^= a;
			a ^= b;

			assert( a == 0xCD && b == 0xAB ); 		// Now values are exchanged
		}


		double x {}, y {}, z {};
		const double kEpsilon = 1e-32;

		try
		{
			if( fabs( y ) > kEpsilon )
				z = x / y;
			else
				throw std::overflow_error( "Div by 0" );
		}
		catch( std::exception & e )
		{
			cerr << e.what() << endl;
		}
		catch( ... )
		{
			cerr << "Unknown exception!" << endl;
		}
				
		vector< string > words { "The", "quick", "brown", "fox" };

	}



	// Group 16
	{
		int q = 1;

		q = 5, 6, 7, 8;			// Do you know what value takes on q?
								// What is the value of the enitre expression?
								// Good question on exams ...

		double x = 10.0, y = 12.0;
		double mag {}, angle {};
		
		bool retVal = Cart_2_Polar( x, y, mag, angle );

		retVal = Cart_2_Polar( 0.0, y, mag, angle );


		{
		
			int a { -1 }, b { -2 };

			a, b = 3, 4;	// what will be result of this?

			int c = ( a, b = 3, 4 );	// what of this?

		}

	}



}



// Order evaluation example
int f( int & x )
{
	return x += 2;
}

int g( int & x )
{
	return x *= 4;
}

void h( void )
{
	int x = 10;
	int p = f( x ) + g( x );	// can be 48 or 42
	// ... 
}





class Fl_Widget;

// The class to create GUI (FLTK framework)
class SCUBA_Log_GUI_Creator
{		// ...
	public:
		// Callback function for GUI button click;
		// Upon call "obj" points to "this" of this class
		static void theButtonCallback( Fl_Widget * widgetPtr, void * obj ) 
		{
			assert( typeid( obj ) == typeid( SCUBA_Log_GUI_Creator ) );	// check to be sure during debug
			// Now convert void * to TClassRegistry_GUI_Creator *
			SCUBA_Log_GUI_Creator * theObj = reinterpret_cast< SCUBA_Log_GUI_Creator * >( obj );
			theObj -> Action_On_Button();	// call my local function for action on button click
		}

	protected:
		virtual bool Action_On_Button( void ) // local virtual function
		{
			// Do something here...
			return true;
		}

	public:
#if 0
		// Create the main window with the FLTK library
		virtual int CreateGUI( void )
		{
			Fl_Window	main_win( 100, 200, "SCUBA diving log" );

			// Add some widgets such as buttons, combos, ...


			// Add a button as a local object
			Fl_Return_Button theButton( 20, 20, 80, 20, "Action button" ); 
			
			// Link action on button via the callback function
			theButton.callback( theButtonCallback, this );		

			// Finalize adding new widgets ...

			return Fl::run();	// Show the main window and widgets
		}
#endif
};






bool check_if_not_empty_string( char * p )
{
	// the second cond is evaluated only if first is true
	if( p != 0 && * p != 0 )	
		return true;
	else
		return false;
}



// This function shows real precedence of the conditional operator ?:
// as well as the throw operator.
// In C++ these have THE SAME PRECEDENCE and the right-to-left associativity.
// In C ?: has higher priority than the assignment operators (there is no throw).
void OperatorPrecedenceTest( bool flag )
{

	int x = 0, y = 0; 
	cout << "x=" << x << ", y=" << y << endl; 

	int sign_of_x = x < 0.0 ? -1 : +1;			// this works in C++ as expected since both operators "=" as well as "?:" are right-associative,
	cout << "sign_of_x=" << sign_of_x << endl;	// so the latter executes first; in C also but because "?:" has a higher precedence


	// ?: and = have the same precedence
	// and the right-to-left associativity
	flag ? x : y = 13;
	cout << "x=" << x << ", y=" << y << endl; 

	// In C++ the above is interpreted as the following expression:
	flag ? x : ( y = 13 );
	cout << "x=" << x << ", y=" << y << endl; 

	// In C this would be interpreted differently, as follows:
	( flag ? x : y ) = 13;
	cout << "x=" << x << ", y=" << y << endl << endl; 




	// --------------------
	// Now let's test throw

	int p {};

	try
	{
		p = flag ? 12 : throw 13;
		p = flag ? 12 : ( throw 13 );	// the above is interpreted as this expression
	}
	catch( ... )
	{
		cout << "throw cuaght" << endl;
	}

	cout << "p=" << p << endl << endl;	// if throw is generated, then is not changed, i.e. p == 0
										// otherwise p is changed, so p == 12

}


