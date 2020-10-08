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




#include <string>


// Expression grammar

//E -> E + T | E – T | T			expression
//T -> T * F | T / F | F			term
//F -> D | ( E )					factor
//D -> 0 | 1 | 2 | ... | 9
//


// Such left-recursive production E -> E + T ... cannot be 
// directly implemented. (Why?)

//bool Expression_Fun( )
//{
//	if( Term_Fun() == true )
//	{
//		if( Match( '+' ) == true )
//		{
//			if( Expression_Fun() == true )
//			{
//				return true;		// ok we have a match of E + T
//			}
//		}
//		else
//		{
//			if( Match( '-' ) == true )
//			{
//				if( Expression_Fun() == true )
//				{
//					return true;		// ok we have a match of E - T
//				}
//			}
//		}

//		return true;
//	}

//	return false;
//}


// Therefore we have to exchange the grammar to get rid of
// the left recursion.
// 
// E -> T | E + T | E – T                       expression
//


// After left-recursion elimination we get:
// E  -> T E'
// E' -> + T E' | - T E' | e
// T  -> F T'
// T' -> * F T' | / F T' | e
// F  -> ( E )  | D




// Implements the simple expression grammar
// free of the left recursion.
class TSimpleExpressionInterpreter
{

	private:

		std::string				fExpressionString;
		std::string::size_type	fCurrPos {};		// indicates currently examined position in the expression string

	public:

		std::string::size_type	GetCurPos( void ) const { return fCurrPos; }

	public:


		TSimpleExpressionInterpreter( void ) : fCurrPos( 0 ) {}
		virtual ~TSimpleExpressionInterpreter() = default;

		TSimpleExpressionInterpreter( const TSimpleExpressionInterpreter & )		= default;
		// The argument to the move constructor must not be const
		TSimpleExpressionInterpreter( TSimpleExpressionInterpreter && ) noexcept	= default;

		TSimpleExpressionInterpreter & operator = ( const TSimpleExpressionInterpreter & )		= default;
		// The argument to the assignment operator must not be const
		TSimpleExpressionInterpreter & operator = ( TSimpleExpressionInterpreter && ) noexcept	= default;


	public:

		///////////////////////////////////////////////////////////
		// Functional operator to match an expression to fulfill
		// the grammar.
		///////////////////////////////////////////////////////////
		//
		// INPUT:
		//			in_str - a string with input expression 		
		//
		// OUTPUT:	true if expression fulfills the grammar, false otherwise
		//
		// REMARKS:
		//		If false returned, then fCurrPos points 
		//		at the last properly matched position.
		//
		virtual bool operator () ( const std::string & in_str )
		{
			fExpressionString = in_str;
			fCurrPos = 0;

			return Expr_Fun() && fCurrPos == fExpressionString.size();
		}

	protected:

		///////////////////////////////////////////////////////////
		// This is the simplest lexical analyzer.
		// It checks if a character matches 1:1 a character
		// in the fExpressionString at position fCurrPos.
		///////////////////////////////////////////////////////////
		//
		// INPUT:
		//		c - the character to match in fExpressionString at position fCurrPos 		
		//
		// OUTPUT:	true if c matched, false otherwise
		//
		// REMARKS:
		//		If a match, then fCurrPos is advanced to the next character.
		//
		virtual bool Match( char c )
		{
			if( fCurrPos >= fExpressionString.size() )
				return false;		// the pointer out of scope, exiting ...

			if( fExpressionString[ fCurrPos ] == c )
			{
				++ fCurrPos;		// advance the pointer to the next position
				return true;
			}
			else
			{
				return false;			// no match
			}
		}


	protected:


		// E  -> T E'
		virtual bool Expr_Fun( void )
		{
			return Term_Fun() && Expr_Prime_Fun();
		}


		// E' -> + T E' | - T E' | e
		virtual bool Expr_Prime_Fun( void )
		{
			if( Match( '+' ) )
			{
				return Term_Fun() && Expr_Prime_Fun();			// production: + T E'
			}
			else
			{
				if( Match( '-' ) )
				{
					return Term_Fun() && Expr_Prime_Fun();		// production: - T E'
				}
			}

			return true;										// production: e
		}



		// T  -> F T'
		virtual bool Term_Fun( void )
		{
			return Factor_Fun() && Term_Prime_Fun();
		}


		// T' -> * F T' | / F T' | e
		virtual bool Term_Prime_Fun( void )
		{
			if( Match( '*' ) )
			{
				return Factor_Fun() && Term_Prime_Fun();		// production: * F T'
			}
			else
			{
				if( Match( '/' ) )
				{
					return Factor_Fun() && Term_Prime_Fun();	// production: / F T'
				}
			}

			return true;										// production: e
		}


		//F -> D | ( E )                                      factor
		virtual bool Factor_Fun( void )
		{
			if( Digit_Fun() )
			{
				return true;			// ok we have matched D
			}
			else
			{
				if( Match( '(' ) && Expr_Fun() && Match( ')' ) )
				{
					return true;		// ok, this subexpression matches production ( E )
				}
			}

			return false;
		}



		//D -> 0 | 1 | 2 | ... | 9
		virtual bool Digit_Fun( void )
		{
			if( Match( '0' ) ) return true; 
			if( Match( '1' ) ) return true; 
			if( Match( '2' ) ) return true; 
			if( Match( '3' ) ) return true; 
			if( Match( '4' ) ) return true; 
			if( Match( '5' ) ) return true; 
			if( Match( '6' ) ) return true; 
			if( Match( '7' ) ) return true; 
			if( Match( '8' ) ) return true; 
			if( Match( '9' ) ) return true; 

			return false;
		}




};





