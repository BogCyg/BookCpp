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



#include <memory>
#include <cassert>




// Forward class declarations
class TVisitor;



// A forward declaration of the base class for the node hierarchy.
class TNode;

// Owning relation - we can declare the std::unique_ptr
// with only declared class TNode. Its definition follows.
using Node_UP = std::unique_ptr< TNode >;

// Non-owning relation
using NodePtr = TNode *;




// This is an interface class representing a node
// in the tree - it serves only
// to be derived from, its objects cannot be created.
class TNode
{

protected:

	// Making the constructor protected is also
	// a way to indicate a class as a base since
	// only derived classes can be instantiated.
	TNode( void ) = default;


public:

	// To indicated the class is an abstract interface 
	// its destructor is a pure virtual function
	// what is indicated by adding = 0 to the declaration.
	virtual ~TNode() = 0; /*{}*/

public:

	// Pure virtual functions can have implementation 
	// but it is not absolutely required.
	// Derived types must provide their own implementation if they
	// are instantiated.
	// Accept allows operation of a visitor.
	virtual void Accept( TVisitor & v ) const = 0;

public:

	// Re-create yourself - No implementation
	// for Clone in the base class.
	virtual Node_UP Clone( void ) const = 0;

};



// A leaf (an object) with a value, such as
// a number, a string, etc.
template < typename V >
class ValueLeafNode : public TNode
{

private:

	V		fVal {};	// a held value

public:

	ValueLeafNode( void ) : fVal() {}
	explicit ValueLeafNode( const V & val ) : fVal( val ) {}
	
	virtual ~ValueLeafNode() = default;

	ValueLeafNode( const ValueLeafNode & ) = default;
	ValueLeafNode( ValueLeafNode && ) noexcept = default;

	ValueLeafNode & operator = ( const ValueLeafNode & ) = default;
	ValueLeafNode & operator = ( ValueLeafNode && ) noexcept = default;


public:


	V GetValue( void ) const { return fVal; }

	// Accept a visitor
	void Accept( TVisitor & v ) const override
	{
		v.Visit( * this );
	}

public:

	// Re-create yourself
	Node_UP Clone( void ) const override;

};


// A leaf with a floating-point value.
using NumberLeafNode = ValueLeafNode< double >;


// A class to represent any binary operator.
class BinOperator : public TNode
{

private:

	Node_UP		fLeftChild;		// Owning pointer to the left subtree
	Node_UP		fRightChild;	// Owning pointer to the right subtree

public:

	BinOperator( void ) = default;
	BinOperator( Node_UP left, Node_UP right ) : fLeftChild( std::move( left ) ), fRightChild( std::move( right ) ) {}

	virtual ~BinOperator () = default;

protected:

	// Disallow simple (shallows) copying.
	// To copy use Clone()
	BinOperator( const BinOperator & ) = delete;
	BinOperator( const BinOperator && ) = delete;

	BinOperator & operator = ( const BinOperator & ) = delete;
	BinOperator & operator = ( const BinOperator && ) = delete;

public:

	NodePtr		GetLeftChild( void ) const { assert( fLeftChild != nullptr ); return fLeftChild.get(); }
	NodePtr		GetRightChild( void ) const { assert( fRightChild != nullptr ); return fRightChild.get(); }

	// Passing up for ownership
	void		AdoptLeftChild( Node_UP up ) { fLeftChild = std::move( up ); }
	void		AdoptRightChild( Node_UP up ) { fRightChild = std::move( up ); }

public:

	void Accept( TVisitor & v ) const override = 0;

public:

	// Re-create yourself - this is a derived class but
	// again Clone is pure virtual and we don't have
	// its implementation.
	Node_UP Clone( void ) const override = 0;

};



// A concrete binary operator 
class PlusOperator : public BinOperator
{

public:

	PlusOperator( void ) = default;
	PlusOperator( Node_UP left, Node_UP right ) 
		: BinOperator( std::move( left ), std::move( right ) )	// init base class
	{}

	virtual ~PlusOperator() = default;

	// Object copying disallowed by the base class

public:

	void Accept( TVisitor & v ) const override;

public:

	// Re-create yourself
	Node_UP Clone( void ) const override;

};



class MinusOperator : public BinOperator
{

public:

	MinusOperator( void ) = default;
	MinusOperator( Node_UP left, Node_UP right ) 
		: BinOperator( std::move( left ), std::move( right ) )	// init base class 
	{}

	virtual ~MinusOperator() = default;

	// Object copying disallowed by the base class

public:

	void Accept( TVisitor & v ) const override;

public:

	// Re-create yourself
	Node_UP Clone( void ) const override;

};



class MultOperator : public BinOperator
{

public:

	MultOperator( void ) = default;
	MultOperator( Node_UP left, Node_UP right ) 
		: BinOperator( std::move( left ), std::move( right ) )	// init base class 
	{}

	virtual ~MultOperator() = default;

	// Object copying disallowed by the base class

public:

	void Accept( TVisitor & v ) const override;

public:

	// Re-create yourself
	Node_UP Clone( void ) const override;

};



class DivOperator : public BinOperator
{

public:

	DivOperator( void ) = default;
	DivOperator( Node_UP left, Node_UP right ) 
		: BinOperator( std::move( left ), std::move( right ) )	// init base class 
	{}

	virtual ~DivOperator() = default;

	// Object copying disallowed by the base class

public:

	void Accept( TVisitor & v ) const override;

public:

	// Re-create yourself
	Node_UP Clone( void ) const override;

};


