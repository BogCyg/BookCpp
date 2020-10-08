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
#include <string>
#include <vector>


#include "ExpressionTreeBuilderInterpreter.h"


using std::cout, std::endl;
using std::string;
using std::vector;



///////////////////////////////////////////////////////////////////////////////////////////////


// -------------------------------
void SimpleExpression_Test( void )
{

	TSimpleExpressionInterpreter		theInterpreter;

	const vector< std::string >	expr_vec	{
												"2+3*(7+3)",
												"2+3+4+5+6+",
												"(((5)))",
												"((2+3)*(4+5)+7)/9",
												"2++3*(7+3)"
											};

	// Check syntax of each expression string
	for( const auto & expr : expr_vec )
		cout << expr << " is " << ( theInterpreter( expr ) ? "OK\n" : "not OK\n" );

}



///////////////////////////////////////////////////////////////////////////////////////////////





// -------------------------
void SyntaxTree_Test( void )
{

	ExpressionTreeBuilderInterpreter		exprParser;

	//string good_expr( "2+3*4" );		// this string is hard coded - make it user entered
	//string good_expr( "2+3*7+3" );		// this string is hard coded - make it user entered
	//string good_expr( "2/3+(7+3)" );		// this string is hard coded - make it user entered
	//string good_expr( "5*(3+2*5)/(2/3+(7+3))" );		// this string is hard coded - make it user entered
	//string good_expr( "(2+3)*(4+5)*(6+7)" );		// this string is hard coded - make it user entered
	//string good_expr( "2*3*4" );		// this string is hard coded - make it user entered
	//string good_expr( "(1+2)*(3+4+5)/(6-7)" );		// this string is hard coded - make it user entered
	string good_expr( "(1+2)*(3+(4+5))/(6-7)" );		// this string is hard coded - make it user entered

	if( exprParser( good_expr ) == false )
	{
		cout << "Syntax error!\n" << good_expr << "\n";
		cout << std::string( exprParser.GetCurPos(), ' ' ) << '^' << "\nExiting ..." << endl;
		return;
	}



	// Here we can do something with the tree e.g. launch a visitor

	// Take a pointer to the root of the tree
	NodePtr		theRoot { exprParser.GetRoot() };
	assert( theRoot );


	// Print structure of the parsing tree
	theRoot->Accept( PrintVisitor() );	// Pass a temporary object as an argument



	// ------------------------------
	// How to copy the tree?
	PlusOperator	p1, p2;		// ok
	//PlusOperator	p3( p2 );	// error, no copy constructable
	//p1 = p2;					// error, no copy by assignment



	// Let's make a clone of the tree - e.g. we can run
	// it in a separate thread.
	Node_UP	theSecondTree { theRoot->Clone() };


	// Evaluate the expression
	EvalVisitor		evalVisitor;
	try
	{
		theSecondTree->Accept( evalVisitor );		// Can throw on zero division
		std::cout << "Val = " << evalVisitor.GetValue() << endl;
	}
	catch( std::exception & e )
	{
		std::cerr << e.what() << endl;
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////












