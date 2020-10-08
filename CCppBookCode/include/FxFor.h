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



#pragma once


#include <iostream>
#include <iomanip>
#include <cassert>
#include <limits>







///////////////////////////////////////////////////////////
// Class for fixed-point data types. 
// No saturation, no overflow control
// SupportType - defines an UNSIGNED integer type for the whole number
// Prec - defines a number of fractional bits
// ACC_TYPE - Accumulator type (for intermediate results)
///////////////////////////////////////////////////////////
template< typename ST, int Prec, typename ACC_TYPE = unsigned long long >
//template< typename ST, typename ST Prec, typename ACC_TYPE = unsigned long long >
class FxFor
{
private:

	// Stores the whole number
	ST	fValue {};

public:

	// Returns an internal representation in Sign/Magnitude format
	constexpr ST GetInternalValue( void ) const 
		{ return fValue; }		

	// Returns an internal representation in the two's complement (C2) format
	constexpr ST GetInternalValue_in_C2( void ) const 
		{ return IsPositive() ? fValue : ( ~fValue | kSignMask ) + 1; }

	constexpr void SetInternalValue( ST new_val ) 	
		{ fValue = new_val; }


public:
	
	// Local const for precision
	enum : ST	{ kPrec = Prec };

private:

	// Let's define some useful flags
	enum : ST	{	
				kSignMask	= ST(1) << ( 8 * sizeof( ST ) - 1 ),		// sign bit (integer MSB)
				kIntegerLSB = ST(1) << kPrec,							// LSB of the integer part
				kFractMSB	= kPrec > 0 ? ST(1) << kPrec - ST(1) : 0	// MSB of the fract part
			};


	// A shortcut to this type
	using FxType = FxFor< ST, Prec, ACC_TYPE >;

public:

	// Some raw data manipulators
	constexpr ST DataValueAbs( void ) const { return fValue & ~kSignMask; }	// Return the absolute value (always positive)
																		 
	constexpr ST GetMagnitudeOfIntegerPart( void ) const 
		{ return DataValueAbs() >> kPrec; }

	constexpr ST GetFractionalPart( void ) const { return fValue & ( kIntegerLSB - 1 ); }

public:

	// ===================================================
	// Class default constructor
	constexpr FxFor( void ) : fValue( 0 ) 					
	{
		static_assert( sizeof( ST ) * 8 > kPrec );
		//static_assert( fValue >= 0 );		will not compile since fValue is not known during compilation
		assert( sizeof( ST ) * 8 > kPrec );
	}

	// Type converting constructors
	constexpr FxFor( int x )
	{
		assert( sizeof( ST ) * 8 > kPrec );
		fValue = x < 0 ? - x << kPrec | kSignMask : x << kPrec;
	}

	constexpr FxFor( char x )
	{
		assert( sizeof( ST ) * 8 > kPrec );
		fValue = x < 0 ? - x << kPrec | kSignMask : x << kPrec;
	}

	constexpr FxFor( short x )
	{
		assert( sizeof( ST ) * 8 > kPrec );
		fValue = x < 0 ? - x << kPrec | kSignMask : x << kPrec;
	}

	constexpr FxFor( long x )
	{
		assert( sizeof( ST ) * 8 > kPrec );
		fValue = x < 0 ? - x << kPrec | kSignMask : x << kPrec;
	}


	constexpr FxFor( double x );							// class constructor


	template< typename D, int P, typename A >
	constexpr FxFor( const FxFor< D, P, A > & f )			// mixed copy constructor
	{
		// At first copy the integer part not to loose the MSB
		fValue = f.GetMagnitudeOfIntegerPart() << kPrec;
		// Then copy the most significant part of the fractional part
		fValue |= f.kPrec > kPrec ? f.GetFractionalPart() >> f.kPrec - kPrec 
									: f.GetFractionalPart() << kPrec - f.kPrec;
		// Finally set the sign
		if( f.IsNegative() )
			MakeNegative();
	}

	// ===================================================

	template< class D, int P, typename A >
	constexpr FxType & operator = ( const FxFor< D, P, A > & f )	// mixed assignement
	{
		// For different types, it can cause loss of data
		if( (void*)& f != (void*)this )		// self-assignment protection
		{
			// At first copy the integer part not to loose the MSB
			fValue = f.GetMagnitudeOfIntegerPart() << kPrec;
			// Then copy the most significant part of the fractional part
			fValue |= f.kPrec > kPrec ? f.GetFractionalPart() >> f.kPrec - kPrec 
										: f.GetFractionalPart() << kPrec - f.kPrec;
			// Finally, set the sign
			if( f.IsNegative() )
				MakeNegative();
		}

		return * this;
	}



	// Conversion operators:

	constexpr operator char()			const;
	constexpr operator short()			const;
	constexpr operator int()			const;
	constexpr operator long()			const;

	constexpr operator double()			const;

	// ===================================================
	// Helpers:

	constexpr bool IsNegative( void ) const 
		{ return ( fValue & kSignMask ) == 0 ? false : true; }
	constexpr bool IsPositive( void ) const 
		{ return ( fValue & kSignMask ) != 0 ? false : true; }		// 0 is also positive
	 
	constexpr void ChangeSign( void ) { fValue ^= kSignMask; }		// Simple XOR will do this nicely

	constexpr void MakeNegative( void ) 
		{ assert( fValue != 0 ); fValue |= kSignMask; }				// Turn the sign bit ON

	constexpr void MakePositive( void ) { fValue &= ~kSignMask; }	// Turn the sign bit OFF

	constexpr void MakeAbs( void ) { MakePositive(); }				// Get rid of the sign, i.e. make it positive

	constexpr FxType GetAbs( void ) const 
		{ FxType tmp( * this ); tmp.MakeAbs(); return tmp; }		// Return the absolute value


	// ===================================================
	// Basic library of operations:

	constexpr FxType operator + ( FxType f ) const;
	constexpr FxType operator - ( FxType f ) const;
	constexpr FxType operator * ( FxType f ) const;
	constexpr FxType operator / ( FxType f ) const;
	 
	constexpr FxType & operator += ( FxType f );	
	constexpr FxType & operator -= ( FxType f );
	constexpr FxType & operator *= ( FxType f );
	constexpr FxType & operator /= ( FxType f );
	 
	constexpr FxType & operator - ( void );		

	// ===================================================

	constexpr FxType operator & ( FxType f ) const;
	constexpr FxType operator | ( FxType f ) const;
	constexpr FxType operator ^ ( FxType f ) const;
	 
	constexpr FxType & operator &= ( FxType f );
	constexpr FxType & operator |= ( FxType f );
	constexpr FxType & operator ^= ( FxType f );
	 
	constexpr FxType & operator ~ ( void );

	// ===================================================

	constexpr FxType operator ++ ( int );	// postfix
	constexpr FxType & operator ++ ();		// prefix
	 
	constexpr FxType operator -- ( int );	// postfix
	constexpr FxType & operator -- ();		// prefix
	 
	// ===================================================
	 
	constexpr FxType operator << ( int shift ) const;
	constexpr FxType operator >> ( int shift ) const;
	 
	constexpr FxType & operator <<= ( int shift );
	constexpr FxType & operator >>= ( int shift );

	// ===================================================
	// Comparators:

	constexpr bool operator ==	( FxType f ) const;
	constexpr bool operator !=	( FxType f ) const;
	constexpr bool operator <	( FxType f ) const;
	constexpr bool operator <=	( FxType f ) const;
	constexpr bool operator >	( FxType f ) const;
	constexpr bool operator >=	( FxType f ) const;

	// ===================================================

};

///////////////////////////////////////////////////////////







// ===================================================
// The type converting constructor: float to fixed
//template< typename ST, int Prec, typename ACC_TYPE >
template< typename ST, int Prec, typename ACC_TYPE >
constexpr FxFor< ST, Prec, ACC_TYPE >::FxFor( double x ) : fValue( 0 )
{			
	bool minus_sign { false };
	if( x < 0.0 )
	{
		minus_sign = true;		// remember the sign,
		x = -x;					// then take the absolute value
	}


	ST int_part = static_cast< ST >( x );	// here we use the standard conversion from the double
											// which cuts off the fraction

	fValue = int_part;
	fValue <<= kPrec;		// put integer part into its place

	double fract_part = x - int_part;

	double scaled_fraction = fract_part * static_cast< double >( kIntegerLSB );
	ST fraction = static_cast< ST >( scaled_fraction );

	fValue |= fraction;			// join the two together

	if( minus_sign == true && fValue != 0 )		
		MakeNegative();			// finally consider the sign

}			




// We repeat the same code as for the "double" conversion to
// avoid implicit conversion from "float" to "double" if a additional 
// function were used.
template< typename ST, int Prec, typename ACC_TYPE >
constexpr FxFor< ST, Prec, ACC_TYPE >::operator double() const
{ 
	// Start from the fraction
	double retVal = static_cast< double >( GetFractionalPart() ) / static_cast< double >( kIntegerLSB );

	retVal += GetMagnitudeOfIntegerPart();	// now add the integer part
	return IsNegative() ? - retVal : retVal;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr FxFor< ST, Prec, ACC_TYPE >::operator char() const
{ 
	constexpr char kMaxOutMagnitude { std::numeric_limits< char >::max() };
	// The fractionalRemainder takes on 1 if the fractional part is greater or equal to 0.5
	// and the magnitude value is less than the maximum for the output type (otherwise
	// there would be an overflow in the output value);
	assert( GetMagnitudeOfIntegerPart() <= kMaxOutMagnitude );		// otherwise we'll have an overflow in this conversion
	ST fractionalRemainder = ( fValue & kFractMSB ) == 0 || GetMagnitudeOfIntegerPart() >= kMaxOutMagnitude ? ST(0) : ST(1);
	char out_val { static_cast< char >( GetMagnitudeOfIntegerPart() + fractionalRemainder ) };
	return IsPositive() ? out_val : - out_val;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr FxFor< ST, Prec, ACC_TYPE >::operator short() const
{ 
	constexpr short kMaxOutMagnitude { std::numeric_limits< short >::max() };
	// The fractionalRemainder takes on 1 if the fractional part is greater or equal to 0.5
	// and the magnitude value is less than the maximum for the output type (otherwise
	// there would be an overflow in the output value)
	assert( GetMagnitudeOfIntegerPart() <= kMaxOutMagnitude );		// otherwise we'll have an overflow in this conversion
	ST fractionalRemainder = ( fValue & kFractMSB ) == 0 || GetMagnitudeOfIntegerPart() >= kMaxOutMagnitude ? ST(0) : ST(1);
	short out_val { static_cast< short >( GetMagnitudeOfIntegerPart() + fractionalRemainder ) };
	return IsPositive() ? out_val : - out_val;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr FxFor< ST, Prec, ACC_TYPE >::operator int() const
{ 
	constexpr int kMaxOutMagnitude { std::numeric_limits< int >::max() };
	// The fractionalRemainder takes on 1 if the fractional part is greater or equal to 0.5
	// and the magnitude value is less than the maximum for the output type (otherwise
	// there would be an overflow in the output value)
	assert( GetMagnitudeOfIntegerPart() <= kMaxOutMagnitude );		// otherwise we'll have an overflow in this conversion
	ST fractionalRemainder = ( fValue & kFractMSB ) == 0 || GetMagnitudeOfIntegerPart() >= kMaxOutMagnitude ? ST(0) : ST(1);
	int out_val { static_cast< int >( GetMagnitudeOfIntegerPart() + fractionalRemainder ) };
	return IsPositive() ? out_val : - out_val;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr FxFor< ST, Prec, ACC_TYPE >::operator long() const
{ 
	constexpr long kMaxOutMagnitude { std::numeric_limits< long >::max() };
	// The fractionalRemainder takes on 1 if the fractional part is greater or equal to 0.5
	// and the magnitude value is less than the maximum for the output type (otherwise
	// there would be an overflow in the output value)
	assert( GetMagnitudeOfIntegerPart() <= kMaxOutMagnitude );		// otherwise we'll have an overflow in this conversion
	ST fractionalRemainder = ( fValue & kFractMSB ) == 0 || GetMagnitudeOfIntegerPart() >= kMaxOutMagnitude ? ST(0) : ST(1);
	long out_val { static_cast< long >( GetMagnitudeOfIntegerPart() + fractionalRemainder ) };
	return IsPositive() ? out_val : - out_val;
}


// ===================================================

// prefix
template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator ++ ()
{
	* this += 1;
	return * this;
}
template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator -- ()
{
	* this -= 1;
	return * this;
}

// postfix
template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator ++ ( int )
{
	FxType tmp( * this );	// this unfortunately requires a temporary copy
	* this += 1;
	return tmp;
}
template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator -- ( int )
{
	FxType tmp( * this );	// this unfortunately requires a temporary copy
	* this -= 1;
	return tmp;
}



// ===================================================

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator + ( FxType f ) const
{
	FxType tmp( * this );
	return tmp += f;
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator - ( FxType f ) const
{
	f.ChangeSign();
	return operator + ( f );
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator * ( FxType f ) const
{
	FxType tmp( * this );
	return tmp *= f;
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator / ( FxType f ) const
{
	FxType tmp( * this );
	return tmp /= f;
}


// ===================================================

//
// C++ standard stands that: The RIGHT shift is quaranteed to be logical (0-fill)
// if the shifted value has an unsigned type or if it has a nonnegative value;
// otherwise the result is implementation dependent.
// The LEFT (...) vacated bits are 0-filled.
//
template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator <<= ( int shift )
{
	IsPositive() ? fValue <<= shift : fValue <<= shift, MakeNegative();
	return * this;
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator >>= ( int shift )
{
	IsPositive() ? fValue >>= shift : ( fValue &= ~kSignMask ) >>= shift, MakeNegative();
	return * this;
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator << ( int shift ) const
{
	FxType tmp( * this );
	tmp.fValue <<= shift;
	return tmp;
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator >> ( int shift ) const
{
	FxType tmp( * this );
	tmp.fValue >>= shift;
	return tmp;
}

// ===================================================

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator += ( FxType f )
{
	// We perform the sign-magnitude arithmetic
	bool first_is_negative	= IsNegative();
	bool second_is_negative = f.IsNegative();

	if( first_is_negative )
	{
		if( second_is_negative )
		{
			// Both are negative

			MakeAbs();				// Take the absolute value of the first operand
			f.MakeAbs();			// Take the absolute value of the second operand


			fValue += f.fValue;		// Add the bare magnitudes;


			MakeNegative();			// And negate the result
		}
		else
		{
			// The first is negative, the second is positive

			MakeAbs();	// simply operate on magnitue (disregarding the sign bit)

			// Here we compare only the magnitudes; The second is positive, so there is no need to get its abs
			if( fValue <= f.fValue )		// "soft" to make 0 positive		
			{
				fValue = f.fValue - fValue;	// and we do NOT change the sign
			}
			else
			{
				fValue -= f.fValue;
				assert( IsPositive() );
				if( fValue != 0 )
					MakeNegative();					// and negate the result
			}
		}
	}
	else
	{
		if( second_is_negative )
		{
			// The first is positive, the second is negative

			f.MakeAbs();	// simply operate on magnitue (disregarding the sign bit)

			// Here we compare only the magnitudes; 
			// The first is positive, so there is no need to get its abs
			if( fValue >= f.fValue )	// "soft" to make 0 positive		
			{
				fValue -= f.fValue;		// and we do NOT change the sign
			}
			else
			{
				fValue = f.fValue - fValue;
				assert( IsPositive() );
				if( fValue != 0 )
					MakeNegative();			// and negate the result
			}
		}
		else
		{
			// Both are positive

			fValue += f.fValue;
		}
	}

	return * this;
}


template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator -= ( FxType f )
{
	f.ChangeSign();
	return operator += ( f );
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator *= ( FxType f )
{
	// We perform the sign-magnitude arithmetic
	bool first_is_negative	= IsNegative();
	bool second_is_negative = f.IsNegative();

	// First we need an accumulator that is long enough to store the result.
	ACC_TYPE theAccumulator = DataValueAbs();		
	// we load here a value which is then shifted, e.g. if we
	// load a fixed 1.0 then this value in acc is NOT a unit 
	// but the value shifted to the left by kPrec
	assert( sizeof( theAccumulator ) >= 2 * sizeof( ST ) );

	theAccumulator *= f.DataValueAbs();		// multiply the POSITIVE magnitudes 
	
	// Now we need to shift the result right by the Prec 
	// to cut off the least-significant kPrec bits (will be lost!).
	// What is left fits well into the fixed format: int.frac
	theAccumulator >>= kPrec;

	// Copy the shifted accumulator to the return object
	fValue = static_cast< ST >( theAccumulator );

	// Finally, set the sign of the result
	if( ( first_is_negative ^ second_is_negative ) && fValue != 0 )
		MakeNegative();

	return * this;
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator /= ( FxType f )
{
	if( f.fValue == 0 )
	{
		return * this;							// error, trying to divide by zero! (set an error flag?)
	}

	// We perform the sign-magnitude arithmetic
	bool first_is_negative	= IsNegative();
	bool second_is_negative = f.IsNegative();

	// First we need an accumulator that is long enough to store the result.
	ACC_TYPE theAccumulator = DataValueAbs();	// a divident goes here
	assert( sizeof( theAccumulator ) >= 2 * sizeof( ST ) );


	theAccumulator <<= kPrec;					// we need to shift the first operand
												// to accomodate for the integer division used 
												// in the next statement

	theAccumulator /= f.DataValueAbs();			// divide the magnitudes- we employ here the available
												// standard division of the POSITIVE integers

	fValue = static_cast< ST >( theAccumulator );	// copy back the result

												// Finally set the sign of the result
	if( ( first_is_negative ^ second_is_negative ) && fValue != 0 )
		MakeNegative();

	return * this;
}


template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator - ( void )
{
	ChangeSign();
	return * this;
}


///////////////////////////////////////////////////////////
// Logical operators:


template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator & ( FxType f ) const
{
	FxType tmp( * this );
	return tmp &= f;
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator | ( FxType f ) const
{
	FxType tmp( * this );
	return tmp |= f;
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator ^ ( FxType f ) const
{
	FxType tmp( * this );
	return tmp ^= f;
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator ~ ( void )
{
	fValue = ~ fValue;
	return * this;
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator &= ( FxType f )
{
	fValue &= f.fValue;
	return * this;
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator |= ( FxType f )
{
	fValue |= f.fValue;
	return * this;
}

template< typename ST, int Prec, typename ACC_TYPE >
typename constexpr FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator ^= ( FxType f )
{
	fValue ^= f.fValue;
	return * this;
}






///////////////////////////////////////////////////////////
// Comparison operators:

template< typename ST, int Prec, typename ACC_TYPE >
bool constexpr FxFor< ST, Prec, ACC_TYPE >::operator == ( FxType f ) const
{
	assert( DataValueAbs() != 0 || IsPositive() );
	assert( f.DataValueAbs() != 0 || f.IsPositive() );
	return fValue == f.fValue;
}

template< typename ST, int Prec, typename ACC_TYPE >
bool constexpr FxFor< ST, Prec, ACC_TYPE >::operator != ( FxType f ) const
{
	return ! operator == ( f );
}

template< typename ST, int Prec, typename ACC_TYPE >
bool constexpr FxFor< ST, Prec, ACC_TYPE >::operator < ( FxType f ) const
{
	assert( DataValueAbs() != 0 || IsPositive() );
	assert( f.DataValueAbs() != 0 || f.IsPositive() );
	if( IsNegative() == true )														// we compare ABS only if the same sign
		return f.IsNegative() == true ? DataValueAbs() > f.DataValueAbs() : true;	// an opposite condition if both negative
	else
		return f.IsNegative() == true ? false : DataValueAbs() < f.DataValueAbs();
}

template< typename ST, int Prec, typename ACC_TYPE >
bool constexpr FxFor< ST, Prec, ACC_TYPE >::operator <= ( FxType f ) const
{
	return operator < ( f ) || operator == ( f );
}

template< typename ST, int Prec, typename ACC_TYPE >
bool constexpr FxFor< ST, Prec, ACC_TYPE >::operator > ( FxType f ) const
{
	return ! operator <= ( f );
}

template< typename ST, int Prec, typename ACC_TYPE >
bool constexpr FxFor< ST, Prec, ACC_TYPE >::operator >= ( FxType f ) const
{
	return ! operator < ( f );
}

///////////////////////////////////////////////////////////

template< typename D, int P, typename A >
auto & operator << ( std::ostream & o, const FxFor< D, P, A > & f )
{
	o << f.GetInternalValue();
	return o;
}

template< typename D, int P, typename A >
auto & operator >> ( const std::istream & i, FxFor< D, P, A > & f )
{
	typename FxFor< D, P >::ST d;
	i >> d;
	f.SetInternalValue( d );
	return i;
}


///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// This function returns the difference in representations
// between double and FxFor<> 
///////////////////////////////////////////////////////////
//		
// INPUT:
//			d - an input double value
//			f - FxFor<> to be checked
//		
// OUTPUT:
//			difference (as a double value) between pure double
//			and fixed representation of this number
//		
// REMARKS:
//		
//		
template< typename D, int P, typename A >
constexpr auto ComputeRoundingError( const double d, const FxFor< D, P, A > f )
{
	auto diff( d - static_cast< double >( f ) );
	return diff < 0.0 ? - diff: diff;		// std::fabs failed to be constexpr friendly
}

template< typename D, int P, typename A >
constexpr auto ComputeRoundingError( const FxFor< D, P, A > f, const double d )
{
	auto diff( d - static_cast< double >( f ) );
	return diff < 0.0 ? - diff: diff;	
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// Here we define the specific data types. Be careful, however,
// to check the size of built-in types on your machine!

using FX_8_8	= FxFor< unsigned short, 8  >;
using FX_16_16	= FxFor< unsigned int,	16 >;
using FX_24_8	= FxFor< unsigned int,	8 >;
using FX_8_24	= FxFor< unsigned int,	24 >;

// The following types are for normalized numbers
// for which their magnitude is less than 1.0.
using FX_PURE_FRACT_15 = FxFor< unsigned short,	15 >;
using FX_PURE_FRACT_31 = FxFor< unsigned int,	31 >;





///////////////////////////////////////////////////////////







