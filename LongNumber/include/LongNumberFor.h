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



#include <cassert>
#include <string>
#include <array>
#include <iostream>
#include <algorithm>
#include <exception>


using std::string;
using std::istream, std::ostream;


// ===============================================================================



// This class efficiently stores a series of numbers, such as 12345678901234567890
// of a given length. Each number is stored in a nibble (i.e. 4 bits).
//
// The auto keyword in a template parameter -
// the type is deduced at the point of instantiation. 
//
template < auto MAX_NUMBERS >
class TLongNumberFor
{
	public:

		//enum { kMaxNumbers = MAX_NUMBERS };
		inline static const auto kMaxNumbers { MAX_NUMBERS };

	private:

		// --------------------------------
		// A class can define another class
		// This class is just a placeholder
		struct NibblePair
		{
				unsigned char fFirst	: 4;		// define two bit fields
				unsigned char fSecond	: 4;		// of a total size of 1 byte

				NibblePair() : fFirst( 0 ), fSecond( 0 ) {}
		};
		// --------------------------------


		static const auto kNumOfBytes = ( kMaxNumbers >> 1 ) + ( kMaxNumbers & 0x01 );

		using NibbleArray = std::array< NibblePair, kNumOfBytes >;
		NibbleArray	fData {};		// Here we efficiently store the nibbles - enforce zero-initialization by adding {}


		// Helper function 
		// Returns true if first nibble 
		bool IsFirstNibble( int index ) const { return ( index & 0x01 ) == 0; }		// inline functions
		
		// Returns address of a number in the fData structure
		auto ReComputeIndex( int index ) const { return index >> 1; }

	public:

		// Construction part
		TLongNumberFor( void ) 
		{ 
			assert( kMaxNumbers > 0 );
			assert( sizeof( NibblePair ) == sizeof( unsigned char ) );		// at first check our invariant
			assert( sizeof( fData ) == ( kMaxNumbers >> 1 ) + ( kMaxNumbers & 0x01 ) );	// some bit manipulation, but be careful about the hierarchy
#if ALLOW_INHERITANCE == 0																		
			assert( sizeof( * this ) == sizeof( fData ) );		// that the object does not contain more than bare data
#endif
		}

#if ALLOW_INHERITANCE == 1
		virtual ~TLongNumberFor() {}	// A virtual destructor to allow inheritance
#endif

	public:

		// Type converting constructor - assumes big endiannes,
		// i.e. the rightmost character will be at 0 index,
		// e.g. "123" will be allocated as: 0 ... 0 1 2 3
		TLongNumberFor( const string & s ) 
		{
			assert( s.length() <= kMaxNumbers );	// should we throw?

			// template type deduction has to exactly match the passed types
			auto char_len = std::min( static_cast< decltype( kMaxNumbers ) >( s.length() ), kMaxNumbers );

			if( char_len < 1 )
				return;				// nothing to do, exit

			for( auto i { 0 }; i < char_len; ++ i )
			{
				// Traverse from the leftmost char of the string
				auto digit { s[ char_len - i - 1 ] - '0' };

				assert( digit >= 0 && digit <= 9 );
				if( ! ( digit >= 0 && digit <= 9 ) )
					return;

				SetNumberAt( i, digit );
			}
		}





		// Type converter - assumes big endiannes,
		// i.e. the rightmost character will be at 0 index,
		// e.g. "123" will be allocated as: 0 ... 0 1 2 3
		operator string() const
		{
			string str;

			// Build the string
			for( int i { kMaxNumbers - 1 }; i >= 0; -- i )
			{
				auto a_digit { GetNumberAt( i ) };
				if( a_digit == 0 && str.length() == 0 )
					continue;				// skip leading left 0s
				else
					str += '0' + a_digit;	// let's use the simple patterns
			}

			return str;
		}

	public:

		bool operator == ( const TLongNumberFor & obj )
		{
			// Treat array as a series of bytes
			return std::memcmp( & fData[ 0 ], & obj.fData[ 0 ], sizeof( fData ) ) == 0;
		}

	public:

		// Retuns a ditig at position
		int GetNumberAt( int position ) const
		{
			assert( position < kMaxNumbers );
			if( position >= kMaxNumbers )
				throw std::out_of_range( "GetNumberAt position out of range" );		// if wrong position then throw
			return IsFirstNibble( position ) ? fData[ ReComputeIndex( position ) ].fFirst : fData[ ReComputeIndex( position ) ].fSecond;
		}

		void SetNumberAt( int position, int val )
		{
			assert( val >= 0 && val <= 9 );		// check that we don't abuse it
			assert( position < kMaxNumbers );
			if( position >= kMaxNumbers )
				throw std::out_of_range( "SetNumberAt position out of range" );		// if wrong position then throw
			IsFirstNibble( position ) ? ( fData[ ReComputeIndex( position ) ].fFirst = val ) : ( fData[ ReComputeIndex( position ) ].fSecond = val );
		}

		// Resets all numbers to 0
		void ClearAll( void )
		{
			fData.fill( NibbleArray::value_type() );	// set all to 0
		}


		// Overloaded subscript operator but ONLY to READ.
		// To write, we will need a proxy pattern (see below).
		const int operator [] ( int position ) const
		{
			assert( position < kMaxNumbers );
			return GetNumberAt( position );		// can throw
		}

#define TURN_ON_PROXY
#ifdef TURN_ON_PROXY
	private:

		// The proxy pattern private area

		// -------------------------------------------------------------------
		// This nested class realized the PROXY pattern
		class RetObjProxy
		{
			public:

				using MotherClass = typename TLongNumberFor< MAX_NUMBERS > ;

			private:


				// Can't use a reference here since
				// an uninitialized reference type data member or const data member 
				// makes the compiler implicitly declare a default constructor as deleted.
				// That would be fine, since we wish a deleted default constructor.
				// 
				// However, it holds also that
				// a const or reference type data member makes the compiler declare a  
				// copy assignment operator as deleted. 
				// This does not work for us - we need a copy assignment. 

				//MotherClass & fMyMother;	// A reference to the mother TLongNumberFor class
				MotherClass * fMyMother {};	// A pointer to the mother TLongNumberFor class
					
				int fPosition {};			// Local index storage for the operator []

			public:

				// Constructor
				// myMother - a TLongNumberFor class we connect to
				// position - index position
				RetObjProxy( MotherClass * myMother, int position )
					: fMyMother( myMother ), fPosition( position )
				{
					assert( fMyMother != nullptr );
					assert( fPosition < MotherClass::kMaxNumbers );
				}


				// Forbidden default constructor
				RetObjProxy( void ) = delete;

				RetObjProxy & operator = ( const RetObjProxy & r )
				{
					return * this;
				}
		
		public:

				// Called when: int x = id[ 8 ]
				// Right side (read) operation
				// Conversion operator to int - for read operations
				operator int () const
				{
					assert( fMyMother != nullptr );
					return fMyMother->GetNumberAt( fPosition );
				}

				// Called when: id[ 8 ] = 5
				RetObjProxy & operator = ( int val )
				{
					assert( fMyMother != nullptr );
					fMyMother->SetNumberAt( fPosition, val );	
					return * this;
				}

				// Called when: id[ 8 ] = id[ 7 ]
				RetObjProxy & operator = ( RetObjProxy & r )
				{
					assert( fMyMother != nullptr );
					fMyMother->SetNumberAt( fPosition, r.fMyMother->GetNumberAt( r.fPosition ) );	
					return * this;
				}

		};
		// End of proxy
		// -------------------------------------------------------------------


	public:


		// The main idea behind the subscript operator in TLongNumberFor (this is not a proxy)
		// is to return a proxy object rather than any value. 
		// The returned proxy will behave differently being on the left 
		// or right side of the assignment operator. 
		RetObjProxy operator [] ( int position )
		{
			assert( position < kMaxNumbers );
			// Here we create the proxy object providing "this" 
			// as its "mother" class.
			// Return by value (copy elision, guaranteed in C++17)
			return RetObjProxy( this, position );
		}
	// -------------------------------------------------------------------
#endif
};


/////////////////////////////////////////////////////////////////////////////////
// Extraction operator
template < typename auto MAX_NUMBERS >
ostream & operator << ( ostream & o, const TLongNumberFor< MAX_NUMBERS > & longNumb )
{
	for( auto i { TLongNumberFor< MAX_NUMBERS >::kMaxNumbers - 1 }; i >= 0; -- i )
		o << longNumb.GetNumberAt( i );
	return o;
}


/////////////////////////////////////////////////////////////////////////////////
// Insertion operator
template < typename auto MAX_NUMBERS >
istream & operator >> ( istream & i, TLongNumberFor< MAX_NUMBERS > & longNumb )
{
	string str;
	i >> str;			// read as a string
	longNumb = str;		// call conversion
	return i;
}





