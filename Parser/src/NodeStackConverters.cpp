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
#include <vector>


#include "ExpressionTreeBuilderInterpreter.h"


using std::cout, std::endl;
using std::string;
using std::vector;



///////////////////////////////////////////////////////////////////////////////////////////////


using NodeVec = ExpressionTreeBuilderInterpreter::NodeStack::DataContainer;


using LeafValType = double;


// Computes value of the stack
LeafValType ComputeValueFrom( const NodeVec & node_vec )
{
	auto retVal { 0.0 };

	const auto kNumOfElems = node_vec.size();
	if( kNumOfElems == 0 )
		return retVal;		// Empty node_vec, return zero & exit


	// The algorithm is as follows:
	// - The node stack is traversed:
	// -	if a leaf is encountered, then push its value on auxStack
	// -	if a bin operator is encountered, take two topmost values,
	//		perform the operation, and push back the result on auxStack
	CppBook::TStackFor< LeafValType, 1000 >		auxStack;



	// Traverse all nodes, starting at index 0
	for( const auto & node : node_vec )
	{
		assert( node );

		if( typeid( * node ) == typeid( NumberLeafNode ) )
		{
			// A NumberLeafNode
			auxStack.Push( dynamic_cast< NumberLeafNode & >( * node ).GetValue() );
		}
		else
		{
			// A binary operator - but we don't know yet which one

			assert( auxStack.GetStackSize() >= 2 );	

			LeafValType leftNumVal {}, rightNumVal {};

			auxStack.Pop( rightNumVal );	// Get top values
			auxStack.Pop( leftNumVal );

			// Check what type of operation is in the node
			if( dynamic_cast< PlusOperator * >( node.get() ) )
				auxStack.Push( leftNumVal + rightNumVal );
			else
				if( dynamic_cast< MinusOperator * >( node.get() ) )
					auxStack.Push( leftNumVal - rightNumVal );
				else
					if( dynamic_cast< MultOperator * >( node.get() ) )
						auxStack.Push( leftNumVal * rightNumVal );
					else
						if( dynamic_cast< DivOperator * >( node.get() ) )
							if(	std::fabs( rightNumVal ) > 1e-32 ) 
								auxStack.Push( leftNumVal / rightNumVal ); 
							else 
								throw std::overflow_error( "Div by 0" );
						else
							assert( false ); // Must not happen - check in debug
		}


	}

	// Take over the last node from the stack or return empty.
	assert( auxStack.GetStackSize() == 1 );
	auxStack.Pop( retVal );

	return retVal;
}





// ------------------------------------------
// Evaluates the value from the node stack.
// This works when compiling with
// BUILD_THE_TREE set to 0
// (in ExpressionTreeBuilderInterpreter.h)
void RPN_Value_Test( void )
{
#if BUILD_THE_TREE == 1
	assert( false );		// A fuse to ensure we compiled with the proper parameter
#endif

	ExpressionTreeBuilderInterpreter		exprParser;

	string good_expr( "(1+2)*(3+(4+5))/(6-7)" );		// Expression string

	// Let's call only the base class operator ()
	//if( exprParser.BaseClass::operator()( good_expr ) )
	if( ( & exprParser )->BaseClass::operator()( good_expr ) )
	{
		try
		{
			std::cout << "Val = " << ComputeValueFrom(  exprParser.GetNodeStack().GetDataContainer()  ) << endl;
		}
		catch( std::exception & e )
		{
			std::cerr << e.what() << endl;
		}
	}
	else
	{
		cout << "Syntax error!\n" << good_expr << "\n";
		cout << std::string( exprParser.GetCurPos(), ' ' ) << '^' << "\nExiting ..." << endl;
	}


}



///////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////
// Converts a stack of nodes into a syntax tree.
///////////////////////////////////////////////////////////
//
// INPUT:	node_vec - a vector underlying a stack with 
//				nodes inserted by the parser	
//
// OUTPUT:	A smart pointer to the root of the built syntax tree
//
// REMARKS: Returned pointer will be empty if stack is empty.
//			The objects in the node_vec will be overtaken
//			to the built tree whose root node is returned.
//
Node_UP ConvertStack_2_SyntaxTree( NodeVec & node_vec )
{
	const auto kNumOfElems = node_vec.size();
	if( kNumOfElems == 0 )
		return Node_UP();		// return an empty object

	// Traverse all nodes, starting at index 0
	for( const auto i : CppBook::range( kNumOfElems ) )
	{

		if( auto bin_op = dynamic_cast< BinOperator * >( node_vec[ i ].get() ) )
		{
			// If bin op, then overtake its two preceeding nodes,
			// whatever it is, and join as its left and right child

			assert( i >= 2 );		// 

			Node_UP left, right;	// empty at the beginning

			// Go downward and find two nodes not yet overtaken
			// We have to use the signed type 'int' here to properly compare k >= 0
			for( int k = static_cast< int >( i - 1 ); k >= 0; -- k )
			{
				if( node_vec[ k ] != nullptr )
				{
					// First is right
					if( right == nullptr )
					{
						right = std::move( node_vec[ k ] );
					}
					else
					{
						if( left == nullptr )
						{
							left = std::move( node_vec[ k ] );
							break;		// we are done, exit the loop asap
						}
					}
				}
			}

			assert( left != nullptr );
			assert( right != nullptr );

			bin_op->AdoptLeftChild( std::move( left ) );		// connect the nodes
			bin_op->AdoptRightChild( std::move( right ) );

		}

	}

	// Overtake the last node from the stack or return empty.
	return node_vec.size() > 0 ? std::move( node_vec.back() ) : Node_UP();
}






void RPN_Tree_Test( void )
{
#if BUILD_THE_TREE == 1
	assert( false );		// A fuse to ensure we compiled with the proper parameter
#endif

	ExpressionTreeBuilderInterpreter		exprParser;

	string good_expr( "(1+2)*(3+(4+5))/(6-7)" );		// this string is hard coded - make it user entered

	// Let us call only the base class operator ()
	if( exprParser.BaseClass::operator()( good_expr ) == false )
	{
		cout << "Syntax error!\n" << good_expr << "\n";
		cout << std::string( exprParser.GetCurPos(), ' ' ) << '^' << "\nExiting ..." << endl;
		return;		// Exiting ...
	}


	// Build a syntax tree from the stack and take a pointer to the root of the tree
	Node_UP		theRoot { ConvertStack_2_SyntaxTree( exprParser.GetNodeStack().GetDataContainer() ) };
	assert( theRoot );


	// Print structure of the parsing tree
	theRoot->Accept( PrintVisitor() );


	// Evaluate the expression
	try
	{
		EvalVisitor		evalVisitor;
		theRoot->Accept( evalVisitor );		// Can throw on zero division
		std::cout << "Val = " << evalVisitor.GetValue() << endl;
	}
	catch( std::exception & e )
	{
		std::cerr << e.what() << endl;
	}

}





