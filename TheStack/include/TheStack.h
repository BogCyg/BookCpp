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



#include <cassert>
#include <vector>



namespace CppBook
{





// ==============================================================================================

// Definition of the stack data structure
template < typename T, auto MaxElems = 1000 >
class TStackFor
{
	public:

		using value_type = T;

	private:

		using DataContainer = std::vector< value_type >;

		DataContainer		fData;

	public:

		// Here we need an additional typename
		using size_type = typename DataContainer::size_type;


	public:

		auto GetStackSize( void ) const { return fData.size(); }

	public:


		///////////////////////////////////////////////////////////
		// This function puts an element onto the stack
		///////////////////////////////////////////////////////////
		//		
		// INPUT:
		//			new_elem - a reference to the element to
		//				be put. Actually its copy is put onto
		//				the stack.
		//		
		// OUTPUT:
		//			true - if operation successful,
		//			false - failure, due to insufficient
		//				space on the stack (e.g. too many 
		//				elements)
		//		
		// REMARKS:
		//		
		//		
		bool Push( const value_type & new_elem );



		///////////////////////////////////////////////////////////
		// This function removes an element from the stack
		///////////////////////////////////////////////////////////
		//		
		// INPUT:
		//			ret_elem - a reference to the object which
		//				will be copied with the topmost element
		//				from the stack. Then the topmost element
		//				is removed from the stack.
		//		
		// OUTPUT:
		//			true - if operation successful,
		//			false - failure, due to empty stack
		//		
		// REMARKS:
		//		
		bool Pop( value_type & ret_elem );


};



///////////////////////////////////////////////////////////
// This functions puts an element onto the stack
///////////////////////////////////////////////////////////
//		
// INPUT:
//			new_elem - a reference to the element to
//				be put. Actually its copy is put onto
//				the stack.
//		
// OUTPUT:
//			true - if operation successful,
//			false - failure, due to insufficient
//				space on the stack (e.g. too many 
//				elements)
//		
// REMARKS:
//		
//		
template < typename T, auto MaxElems >
bool TStackFor< T, MaxElems >::Push( const value_type & new_elem )
{
	if( GetStackSize() == MaxElems )
		return false;

	fData.emplace_back( new_elem );

	return true;
}




///////////////////////////////////////////////////////////
// This functions takes and removes an element from the stack
///////////////////////////////////////////////////////////
//		
// INPUT:
//			ret_elem - a reference to the object which
//				will be copied with a topmost element
//				from the stack. Then the topmost element
//				is removed from the stack.
//		
// OUTPUT:
//			true - if operation successful,
//			false - failure, due to empty stack
//		
// REMARKS:
//	
template < typename T, auto MaxElems >
bool TStackFor< T, MaxElems >::Pop( value_type & ret_elem )
{
	if( GetStackSize() == 0 )
		return false;

	ret_elem = fData.back();	// Copy the top element
	fData.pop_back();			// Get rid of the last element

	return true;
}

}		// End of the CppBook namespace



// ----------------------------------------------------




namespace CppBook
{



// Stack specialization to operate with std::unique_ptr
template < typename T, auto MaxElems >
class TStackFor< std::unique_ptr< T >, MaxElems >
{
	public:

		using value_type = std::unique_ptr< T >;

	public:

		using DataContainer = std::vector< value_type >;
		
	private:

		DataContainer		fData;

	public:

		DataContainer &	GetDataContainer( void ) { return fData; }

	public:

		// Here we need an additional typename
		using size_type = typename DataContainer::size_type;

	public:

		auto GetStackSize( void ) const { return fData.size(); }

	public:


		///////////////////////////////////////////////////////////
		// This functions puts an element onto the stack
		///////////////////////////////////////////////////////////
		//		
		// INPUT:	new_elem - a reference to the element to
		//				be put. Actually its copy is put onto
		//				the stack.
		//		
		// OUTPUT:	true - if operation successful,
		//			false - failure, due to insufficient
		//				space on the stack (e.g. too many 
		//				elements)
		//		
		bool Push( value_type new_elem )
		{
			if( GetStackSize() == MaxElems )
				return false;

			fData.emplace_back( std::move( new_elem ) );
			// new_elem is empty now

			return true;
		}



		///////////////////////////////////////////////////////////
		// This functions takes and removes an element from the stack
		///////////////////////////////////////////////////////////
		//		
		// INPUT:	new_elem - a reference to the object which
		//				will be copied with a topmost element
		//				from the stack. Then the topmost element
		//				is removed from the stack.
		//		
		// OUTPUT:	true - if operation successful,
		//			false - failure, due to empty stack
		//		
		bool Pop( value_type & ret_elem )
		{
			if( GetStackSize() == 0 )
				return false;

			ret_elem.reset( fData.back().release() );	// re-connect pointers
			fData.pop_back();		// get rid of the last (empty) element

			return true;
		}



};


template < typename T >
using UP_Stack_1000 = TStackFor< std::unique_ptr< T >, 1000 >;


}		// End of the CppBook namespace





