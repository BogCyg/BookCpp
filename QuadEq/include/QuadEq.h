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



// Preprocessor idiom to include the header only once
#ifndef QuadEq_h
#define QuadEq_h


#include <iostream>
#include <cassert>



///////////////////////////////////////////////////////////
// This class implement the quadratic equation of the form:
//
//		a*x*x + b*x + c = 0
//
///////////////////////////////////////////////////////////
class TQuadEq
{
	private:

		double fa {}, fb {}, fc {};	// the coefficients of the equation

	public:

		// ===================================================
		
		// Class default constructor
		TQuadEq( void ) : fa( 0.0 ), fb( 0.0 ), fc( 0.0 )
		{}
		
		// Class parametric constructor
		TQuadEq( double a, double b, double c )
			: fa( a ), fb( b ), fc( c )
		{}
	

		// ===================================================


	public:

		// Getters & Setters
		double Get_a( void ) const { return fa; }
		double Get_b( void ) const { return fb; }
		double Get_c( void ) const { return fc; }


		void Set_a( double a ) { fa = a; }
		void Set_b( double b ) { fb = b; }
		void Set_c( double c ) { fc = c; }

	public:

		// Helper functions to compute the discriminant of the quadratic equation;
		// This is an inline function (definition of a function in the class)
		double ComputeDelta( void ) const { return fb * fb - 4.0 * fa * fc; }

		// Define some constants for the class - using the scoped enum type
		enum class EEqType { kNone, kOne, kTwo, kLinOne, kLinContra };


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
		//			Separation of a problem analysis from
		//			problem solution
		//		
		virtual EEqType GetNumOfRoots( const double delta ) const;


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
		EEqType GetRoots( double & theRoot_1, double & theRoot_2 ) const;

};



//////////////////////////////////////////////////////////
// Input/Output operations (external functions)
std::ostream & operator << ( std::ostream & o, const TQuadEq & equation );
std::istream & operator >> ( std::istream & i, TQuadEq & equation );





#endif // QuadEq_h










