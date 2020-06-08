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



// Paths are relative to the position of 
// the project files
#include "../../Complex/include/Complex.h"
#include "../../QuadEq/include/QuadEq.h"


using	CppBook::TComplex;


class TComplexQuadEq : public TQuadEq
{
	public:

		// Introduce the EEqType from the base class
		using TQuadEq::EEqType;

	public:

		// ===================================================
		
		// class default constructor
		TComplexQuadEq( void )
		{}
		
		// class parametric constructor
		TComplexQuadEq( double a, double b, double c )
			: TQuadEq( a, b, c )		// call the base class constructor
		{}

		// Class default copy constructor
		TComplexQuadEq( const TComplexQuadEq & ) = default;

		// Class default destructor
		~TComplexQuadEq() = default;
													
		// ===================================================

	public:

		///////////////////////////////////////////////////////////
		// This function checks type of the equation 
		///////////////////////////////////////////////////////////
		//		
		// INPUT: 		delta
		// OUTPUT:		An exact type of the equation 
		//				represented by the parameters f_a, f_b, f_c
		//		
		EEqType GetNumOfRoots( const double delta ) const;


		///////////////////////////////////////////////////////////
		// This function computes the roots of the equation, if possible.
		///////////////////////////////////////////////////////////
		//		
		//	INPUT:	theRoot_1 - a reference to an object that
		//				contains root 1 if returned kLinOne, kOne or kTwo
		//				theRoot_2 - a reference to an object that
		//				contains root 2 if returned kOne or kTwo
		//				(in the first case root_1 == root_2)
		//		
		// OUTPUT: status of the equation (number of roots)
		//		
		//	REMARKS:	The values referenced to by theRoot_1 and theRoot_2
		//				are undefined in all other cases than stated above.
		//		
		EEqType GetRoots( TComplex & theRoot_1, TComplex & theRoot_2 ) const;

};


