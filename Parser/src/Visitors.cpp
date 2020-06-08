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




#include <iostream>
#include <string>


#include "Nodes.h"
#include "Visitors.h"


// ===================================================================


void EvalVisitor::Visit( const NumberLeafNode & n )
{
	fValue = n.GetValue();
}

void EvalVisitor::Visit( const PlusOperator & n )
{
	auto [ l, r ] = LeftRightValues( n );
	fValue = l + r;	// current value is the sum of left and right
}


void EvalVisitor::Visit( const MinusOperator & n )
{
	auto [ l, r ] = LeftRightValues( n );
	fValue = l - r;	// current value is the diff of left and right
}


void EvalVisitor::Visit( const MultOperator & n )
{
	auto [ l, r ] = LeftRightValues( n );
	fValue = l * r;	// current value is the product of left and right
}


void EvalVisitor::Visit( const DivOperator & n )
{
	auto [ l, r ] = LeftRightValues( n );

	if( std::fabs( r ) < kDivThresh )
		throw std::overflow_error( "Div by 0" );

	fValue = l / r;	// current value is the div of left and right
}


///////////////////////////////////////////////////////////
// Auxiliary function to process the left and right nodes.
///////////////////////////////////////////////////////////
//
// INPUT:	n - a reference to a binary node 		
//
// OUTPUT:	a pair of values of the left and right node
//
EvalVisitor::LR_Pair EvalVisitor::LeftRightValues( const BinOperator & n )
{
	n.GetLeftChild()->Accept( * this );
	auto left_val { fValue };		// store the left value

	n.GetRightChild()->Accept( * this );
	auto right_val { fValue };	// store the right value

	return std::make_tuple( left_val, right_val );
}



// ===================================================================



void PrintVisitor::Visit( const NumberLeafNode & n )
{
	std::cout << std::string( fDepthLevel, ' ' ) << ' ';
	std::cout << std::string( fDL_Step - 1, '-' ) << n.GetValue() << std::endl;
}

void PrintVisitor::Visit( const PlusOperator & n )
{
	LeftRightProcess( n, '+' );
}


void PrintVisitor::Visit( const MinusOperator & n )
{
	LeftRightProcess( n, '-' );
}


void PrintVisitor::Visit( const MultOperator & n )
{
	LeftRightProcess( n, '*' );
}


void PrintVisitor::Visit( const DivOperator & n )
{
	LeftRightProcess( n, '/' );
}


// Here we have an infix operation: left-this-right
void PrintVisitor::LeftRightProcess( const BinOperator & n, char op )
{
	auto prev_dl = fDepthLevel;	// get current indentation level

	fDepthLevel += fDL_Step;	// increase indentation 

	n.GetRightChild()->Accept( * this );

	std::string sepa( fDepthLevel, ' ' );
	std::cout << sepa << '|' << std::endl;
	std::cout << sepa << op << std::endl;
	std::cout << sepa << '|' << std::endl;

	n.GetLeftChild()->Accept( * this );

	fDepthLevel = prev_dl;		// restore previous indent level
}






