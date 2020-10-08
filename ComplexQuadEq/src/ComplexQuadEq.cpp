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




#include "ComplexQuadEq.h"



///////////////////////////////////////////////////////////
// This function checks type of the equation 
///////////////////////////////////////////////////////////
//		
// INPUT: 		delta
// OUTPUT:		An exact type of the equation 
//				represented by the parameters f_a, f_b, f_c
//			
TComplexQuadEq::EEqType TComplexQuadEq::GetNumOfRoots( const double delta ) const
{
	if( Get_a() == 0.0 )
	{
		return Get_b() == 0.0 ? EEqType::kLinContra : EEqType::kLinOne;
	}
	else
	{
		return delta == 0.0 ? EEqType::kOne : EEqType::kTwo;	// In this class the sign of delta is not important
	}
}


///////////////////////////////////////////////////////////
// This function computes the roots of the equation, if possible.
///////////////////////////////////////////////////////////
//		
//	INPUT:	theRoot_1 - a reference to an object which
//				contains root 1 if returned kLinOne, kOne or kTwo
//				theRoot_2 - a reference to an object which
//				contains root 2 if returned kOne or kTwo
//				(in the first case root_1 == root_2)
//		
// OUTPUT: status of the equation (number of roots)
//		
//	REMARKS:	The values referenced to by theRoot_1 and theRoot_2
//				are undefined in all other cases than stated above.
//	
TQuadEq::EEqType TComplexQuadEq::GetRoots( TComplex & root_1, TComplex & root_2 ) const
{
	auto delta( ComputeDelta() );		// call a constructor for the built-in type

	const auto kDivThresh { 1e-36 };		// Used in assert to verify divisions

	EEqType equationTypeFlag = GetNumOfRoots( delta );

	// It is a good idea to explicitly place ALL the cases here (to be sure)
	switch( equationTypeFlag )
	{
		case EEqType::kNone:

			assert( false );		// should not happen
			break;					

		case EEqType::kLinContra:

			break;					// if none, then do nothing

		case EEqType::kLinOne:

			assert( Get_a() == 0.0 );
			assert( std::fabs( Get_b() ) > kDivThresh );

			if( std::fabs( Get_b() ) < kDivThresh )
				throw std::overflow_error( "Too low Get_b()" );

			root_1 = root_2 = - Get_c() / Get_b();

			break;					// return with one root
		
		case EEqType::kOne:			// no break here - for these two cases, one solution
		case EEqType::kTwo:

			{	// We need a block {} here for local variables

				bool negative_delta = delta < 0.0 ? true : false;

				double delta_root = sqrt( negative_delta ? - delta : delta );
				
				double denominator = 2.0 * Get_a();
				assert( std::fabs( denominator ) > kDivThresh );

				if( std::fabs( denominator ) < kDivThresh )
					throw std::overflow_error( "Too low Get_a()" );


				if( negative_delta )
				{
					// Negative delta requires a complex domain
					root_1.SetRe( - Get_b() / denominator );
					root_1.SetIm( - delta_root / denominator );

					root_2.SetRe( - Get_b() / denominator );
					root_2.SetIm(   delta_root / denominator );
				}
				else
				{
					// Positive delta means only real roots
					root_1.SetRe( ( - Get_b() - delta_root ) / denominator );
					root_1.SetIm( 0.0 );

					root_2.SetRe( ( - Get_b() + delta_root ) / denominator );
					root_2.SetIm( 0.0 );
				}

			}

			break;

		default :

			assert( false );		// this should not happen - an error in programming?
			break;
	}

	return equationTypeFlag;
}


