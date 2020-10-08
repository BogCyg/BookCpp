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


#include <cassert>
#include <string>
#include <vector>
#include <iostream>



using std::cout, std::endl;
using std::unique_ptr, std::make_unique;



// --------------------------------------------------------


class TCircle
{

private:

	double	fRadius {};	// private data to hold circle radius

public:

	// this is declared "const" since it does not change anything
	double GetRadius( void ) const { return fRadius; }

	// Thanks to having fRadius private we can check its initialization
	void SetRadius( double v ) { assert( v >= 0.0 ); fRadius = v; }

public:	

	// Default and parametric constructor in one
	TCircle( double r = 0.0 ) : fRadius( r )
	{
		cout << "Constr TCircle called (@" << this << ")" << endl;
	}

	virtual ~TCircle()
	{
		cout << "Destr TCircle called (@" << this << ")" << endl;	
	}

private:

	// Basic version of GetPi (not too precise)
	virtual double GetPi( void ) const 
	{
		cout << "TCircle::pi" << endl;
		return 3.14;
	}

public:

	// There is only one version of ComputeArea
	double ComputeArea( void ) const 
	{
		return GetPi() * fRadius * fRadius;
	}
};


// Slightly more precise for computations
class PrecCircle : public TCircle
{

public:	

	PrecCircle( double r = 0.0 ) : TCircle( r )
	{
		cout << "Constr PrecCircle called (@" << this << ")" << endl;
	}

	virtual ~PrecCircle()
	{
		cout << "Destr PrecCircle called (@" << this << ")" << endl;	
	}

private:

	// In this class we wish to improve GetPi (increase precision).
	// Place override at the end, skip virtual in front.
	double GetPi( void ) const override
	{
		cout << "PrecCircle::pi" << endl;
		return 3.14159265358979;
	}

};


// This function uses C++ polymorphism to print the radius and area of TCircle object
// and ANY other object derived from TCircle.
void PrintInfoFor( const TCircle & circ )
{
	double radius	{ circ.GetRadius() };
	double area		{ circ.ComputeArea() };
	cout << "r=" << radius << " ==> A=" << area << endl;
}

void CircleTest( void )
{

	// ---------------------------------------------------------
	cout << "\nExplicitly define two different objects" << endl;
	cout << "----------------------------------------" << endl;

	{
		TCircle		c1( 1.23 );
		PrintInfoFor( c1 );

		PrecCircle	pc1( 1.23 );
		PrintInfoFor( pc1 );

		// Here, delete all objects
	}

	// --------------------------------------------------------------------
	cout << "\nLet's access only through a pointer to the base class" << endl;
	cout << "----------------------------------------------------" << endl;

	{
		using TC_UP = unique_ptr< TCircle >;	// TC_UP is a smart pointer

		TC_UP	c1_ptr( make_unique< TCircle >( 1.23 ) );	// create TCircle on heap
		PrintInfoFor( * c1_ptr );

		TC_UP	pc1_ptr( make_unique< PrecCircle >( 1.23 ) );	// create TCircle on heap
		PrintInfoFor( * pc1_ptr );

		// Here, delete all objects
	}




}




// --------------------------------------------------------




namespace CRTP_Test
{

	// ----------------------

	template < typename D >
	class TBaseFor
	{

	public:

		// No virtual
		void DAction( void )
		{
			D & deriv_part = static_cast< D & >( * this );

			// Do action on a derived class whatever it is ...
			deriv_part.Work();
		}


	};


	class Derived : public TBaseFor< Derived >
	{
	public:

		// No virtual
		void Work( void )
		{
			// Do something specific to Derived ...
		}

	};


	void DerivedTest( void )
	{
		Derived d;
		d.DAction();
	}


	// ----------------------

	template < typename D >
	class TBaseCircle
	{
	private:

		double	fRadius {};

	public:

		double GetArea( void ) const
		{
			return fRadius * fRadius * static_cast< D const & >( * this ).GetPi();
		}

	public:

		TBaseCircle( double r = 0.0 ) : fRadius( r ) {}

	};


	class SimpleCircle : public TBaseCircle< SimpleCircle >
	{
	public:	

		double GetPi( void ) const
		{
			return 3.14;
		}

	public:

		SimpleCircle( double r = 0.0 ) : TBaseCircle< SimpleCircle >( r ) {}


	};

	// Don't confuse
	// class PrecCircle : TBaseCircle< SimpleCircle >
	class PrecCircle : public TBaseCircle< PrecCircle >
	{
	public:	

		double GetPi( void ) const
		{
			return 3.1415926535;
		}

	public:

		PrecCircle( double r = 0.0 ) : TBaseCircle< PrecCircle >( r ) {}
	};



	void StaticPolymorphism_Test( void )
	{

		SimpleCircle sc( 13.13 );

		cout << "A1 = " << sc.GetArea() << endl;
		cout << "sizeof( SimpleCircle ) = " << sizeof( SimpleCircle ) << endl;

		PrecCircle pc( 13.13 );

		cout << "A2 = " << pc.GetArea() << endl;
		cout << "sizeof( PrecCircle ) = " << sizeof( PrecCircle ) << endl;


	}


}



// --------------------------------------------------------


class B
{};

class C : public virtual B
{};

class D : public virtual B
{};

class E : public C, public D	// multiple inheritance - diamond structure
{};




// --------------------------------------------------------


// Area of mixins ...


template < typename Base >
class MMixin : public Base 
{
	// Can use members of Base ...
};



struct TDate
{
	int			fDay	{};
	std::string	fMonth	{};
	int			fYear	{};
};


template < typename B >
struct MPrint_Date_US : public B
{
	// US date print format
	void Print( void )
	{
		std::cout << fMonth << "/" << fDay << '/' << fYear << '\n';
	}
};

template < typename B >
struct MPrint_Date_Eu : public B
{
	// European date print format
	void Print( void )
	{
		std::cout << fDay << "/" << fMonth << '/' << fYear << '\n';
	}
};


void MixinTest( void )
{
	// Alias is useful with mixins
	using Date_US = MPrint_Date_US< TDate >;
	using Date_Eu = MPrint_Date_Eu< TDate >;

	Date_US		dus { 9, "Nov", 2019 };
	dus.Print();

	Date_Eu		deu { 9, "Nov", 2019 };
	deu.Print();
}

// --------------------------------------------------------





