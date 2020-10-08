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




#include <cmath>
#include "QuadEq.h"



///////////////////////////////////////////////////////////
// This function checks the type of the equation 
///////////////////////////////////////////////////////////
//		
// INPUT:
//			delta
//		
// OUTPUT:
//			The exact type of the equation 
//				represented by the parameters f_a, f_b, f_c
//		
// REMARKS:
//			Separation of the problem analysis from
//			problem solution
//	
TQuadEq::EEqType TQuadEq::GetNumOfRoots( const double delta ) const
{
	if( fa == 0.0 )
	{
		return fb == 0.0 ? EEqType::kLinContra : EEqType::kLinOne;
	}
	else
	{
		if( delta < 0.0 )
			return EEqType::kNone;
		else
			return delta == 0.0 ? EEqType::kOne : EEqType::kTwo;
	}
}


///////////////////////////////////////////////////////////
// This function computes the roots of the equation,
// if possible.
///////////////////////////////////////////////////////////
//		
// INPUT:
//			theRoot_1 - a reference to an object which
//				contains root 1 if returned kLinOne, kOne or kTwo
//			theRoot_2 - a reference to an object which
//				contains root 2 if returned kOne or kTwo
//				(in the first case root_1 == root_2)
//		
// OUTPUT:
//			status of the equation (number of roots)
//		
// REMARKS:
//			The values referenced to by theRoot_1 and theRoot_2
//			are undefined in all other cases than stated above.
//
//	
	
TQuadEq::EEqType TQuadEq::GetRoots( double & root_1, double & root_2 ) const
{
	auto delta( ComputeDelta() );		// call a constructor for the built-in type

	EEqType equationTypeFlag = GetNumOfRoots( delta );

	const double kDivThresh { 1e-36 };		// Used in assert to verify divisions

	// It is a good idea to explicitly place ALL the cases here (to be sure)
	switch( equationTypeFlag )
	{
		case EEqType::kLinContra:
		case EEqType::kNone:

			break;					// if none, then do nothing

		case EEqType::kLinOne:

			assert( fa == 0.0 );
			assert( std::fabs( fb ) > kDivThresh );

			if( std::fabs( fb ) < kDivThresh )
				throw std::overflow_error( "Too low fb" );

			root_1 = root_2 = - fc / fb;

			break;					// return with one root
		
		case EEqType::kOne:
									// no break here - for these two cases, one solution
		case EEqType::kTwo:

			{	// We need a block {} here for local variables

				assert( delta >= 0.0 );	// just in case, who knows?

				double delta_root = std::sqrt( delta );
				
				double denominator = 2.0 * fa;
				assert( std::fabs( denominator ) > kDivThresh );

				if( std::fabs( denominator ) < kDivThresh )
					throw std::overflow_error( "Too low fa" );

				root_1 = ( - fb - delta_root ) / denominator;
				root_2 = ( - fb + delta_root ) / denominator;
			}

			break;

		default :

			assert( false );		// this should not happen - an error in programming?
			break;
	}

	return equationTypeFlag;
}


//////////////////////////////////////////////////////////
// Input/Output operations (usually as external functions)
std::ostream & operator << ( std::ostream & o, const TQuadEq & eq )
{
	o << eq.Get_a() << " " << eq.Get_b() << " " << eq.Get_c() << std::endl;
	return o;
}

std::istream & operator >> ( std::istream & i, TQuadEq & eq )
{
	double tmp { 0.0 };
	i >> tmp; eq.Set_a( tmp );
	i >> tmp; eq.Set_b( tmp );
	i >> tmp; eq.Set_c( tmp );
	return i;
}







