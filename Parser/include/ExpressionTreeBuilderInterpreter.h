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
#include <iostream>
#include <memory>
#include <algorithm>


#include "Nodes.h"
#include "Visitors.h"
#include "TheStack.h"
#include "range.h"


#include "SimpleExpressionInterpreter.h"




// The interpreter that builds the parsing tree
class ExpressionTreeBuilderInterpreter : public TSimpleExpressionInterpreter
{
	public:


		ExpressionTreeBuilderInterpreter( void ) = default;
		virtual ~ExpressionTreeBuilderInterpreter() = default;


		// No shallow copy allowed due to fRoot and other members
		ExpressionTreeBuilderInterpreter( const ExpressionTreeBuilderInterpreter & )	= delete;
		ExpressionTreeBuilderInterpreter( const ExpressionTreeBuilderInterpreter && )	= delete;

		ExpressionTreeBuilderInterpreter & operator = ( const ExpressionTreeBuilderInterpreter & )	= delete;
		ExpressionTreeBuilderInterpreter & operator = ( const ExpressionTreeBuilderInterpreter && ) = delete;

	public:

		///////////////////////////////////////////////////////////
		// Functional operator to match an expression to fulfill
		// the grammar.
		///////////////////////////////////////////////////////////
		//
		// INPUT:	in_str - a string with input expression 		
		//
		// OUTPUT:	true if expression fulfills the grammar, false otherwise
		//
		// REMARKS:
		//			If false returned, then fCurrPos points 
		//			at the last properly matched position.
		//
		virtual bool operator () ( const std::string & in_str )
		{
			if( BaseClass::operator()( in_str ) )	// Call the base parser
				return fNodeStack.Pop( fRoot );		// Take the node off from the stack

			return false;
		}

	public:	

		using BaseClass = TSimpleExpressionInterpreter;
	
		using NodeStack = CppBook::UP_Stack_1000< TNode >;		// useful stack alias

	private:		
		
		NodeStack	fNodeStack;			// the stack to store temporary branches of the tree

		Node_UP		fRoot;				// root node of the parsing tree

	public:

		NodePtr		GetRoot( void ) { return fRoot.get(); }
	
		NodeStack &	GetNodeStack( void ) { return fNodeStack; }	


	protected:

		//D -> 0 | 1 | 2 | ... | 9
		virtual bool Digit_Fun( void )
		{
			if( Match( '0' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 0.0 ) ); return true; } 			
			if( Match( '1' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 1.0 ) ); return true; } 
			if( Match( '2' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 2.0 ) ); return true; } 
			if( Match( '3' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 3.0 ) ); return true; } 
			if( Match( '4' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 4.0 ) ); return true; } 
			if( Match( '5' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 5.0 ) ); return true; } 
			if( Match( '6' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 6.0 ) ); return true; } 
			if( Match( '7' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 7.0 ) ); return true; } 
			if( Match( '8' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 8.0 ) ); return true; } 
			if( Match( '9' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 9.0 ) ); return true; } 

			return false;
		}


		// E' -> + T E' | - T E' | e
		virtual bool Expr_Prime_Fun( void )
		{
			if( Match( '+' ) == true )
			{
				if( Term_Fun() )		// production: + T E'
				{
					CreateSubTree( std::make_unique< PlusOperator >() );
					return Expr_Prime_Fun();
				}
				else
				{
					return false;
				}
			}
			else
			{
				if( Match( '-' ) == true )
				{
					if( Term_Fun() )		// production: - T E'
					{
						CreateSubTree( std::make_unique< MinusOperator >() );
						return Expr_Prime_Fun();
					}
					else
					{
						return false;
					}				
				}
			}

			return true;					// production: e
		}



		// T' -> * F T' | / F T' | e
		virtual bool Term_Prime_Fun( void )
		{
			if( Match( '*' ) == true )
			{
				if( Factor_Fun() )		// production: * F T
				{
					CreateSubTree( std::make_unique< MultOperator >() );
					return Term_Prime_Fun();
				}
				else
				{
					return false;
				}			
			}
			else
			{
				if( Match( '/' ) == true )
				{
					if( Factor_Fun() )		// production: / F T'
					{
						CreateSubTree( std::make_unique< DivOperator >() );
						return Term_Prime_Fun();
					}
					else
					{
						return false;
					}
				}
			}

			return true;					// production: e
		}




	protected:

		///////////////////////////////////////////////////////////
		// Builds a branch of the parsing tree
		///////////////////////////////////////////////////////////
		//
		// INPUT:	bin_op - smart pointer with the input binary operator 		
		//
		// OUTPUT:	node
		//
		// REMARKS: bin_op held object is overtaken and pushed onto the stack
		//
		void CreateSubTree( std::unique_ptr< BinOperator > bin_op )
		{
#define BUILD_THE_TREE 0
#if BUILD_THE_TREE == 1			
			
			assert( fNodeStack.GetStackSize() >= 2 );

			Node_UP left, right;

			fNodeStack.Pop( right );	// Pop the right sub-expression
			fNodeStack.Pop( left );		// Pop the left sub-expression

			bin_op->AdoptLeftChild( std::move( left ) );	// Connect left
			bin_op->AdoptRightChild( std::move( right ) );	// Connect right
#endif 

			fNodeStack.Push( std::move( bin_op ) ); // Push onto the stack
			assert( bin_op.get() == nullptr );		// The input bin_op has been orphaned
		}

};








