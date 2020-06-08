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



// Template members within a template class example
template < typename T >
class TPointFor
{

private:

	T	fx {}, fy {};	// Two coordinates of T type


public:

	void Set_x( T x ) { fx = x; }
	void Set_y( T y ) { fy = y; }

	auto Get_x( void ) const { return fx; }
	auto Get_y( void ) const { return fy; }

public:


	// A template member copy constructor to initialize
	// from a point with different coordinate types.
	// To be general must call Get_x and Get_y
	// Direct access possible only if T == U
	template < typename U >
	TPointFor< T >( const TPointFor< U > & pt ) : fx( pt.Get_x() ), fy( pt.Get_y() ) {}

	// A template member assignment operator to to initialize
	// from a point with different coordinate types.
	template < typename U >
	TPointFor< T > & operator = ( const TPointFor< U > & pt )
	{
		//fx = pt.fx;		these two work only 
		//fy = pt.fy;		if T == U
		fx = pt.Get_x();		// allow conversion
		fy = pt.Get_y();
		return * this;
	}


	// A default constructor needs to be explicitly coded
	// since the copy constructor and the assignment were added
	// (otherwise could be skipped).
	TPointFor( void ) : fx( T() ), fy( T() ) {}

};



inline void PointTest( void )
{

	using RealPoint = TPointFor< double >;

	using IntPoint = TPointFor< int >;


	RealPoint rp1, rp2;		// Calls default constructor

	IntPoint ip1, ip2;		// Calls default constructor


	rp1 = rp2;		// Assignment within the same clas
					// - no special template assignment needed

	rp1 = ip2;		// Assignment across different classes
					// - special template assignment necessary

	RealPoint rp3( ip1 );	// Also copy construction across the different classes
}




