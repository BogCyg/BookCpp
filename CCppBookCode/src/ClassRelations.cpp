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
#include <iomanip>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;



#include <cstdint>


// Interface to on-board flash memory programming
class Am29_FlashProgrammer
{
public:
	enum EFlashBitMask { k_DQ7_Mask=0x01, k_DQ6_Mask=0x02 };
	
	using SystemAddress = uint32_t;		// 32-bit address bus
	using DataLen			= uint32_t;		// 32-bit address bus
	using DataWordType	= uint16_t;		// 16-bit data bus

private:
	// system flash base  address
	const SystemAddress fFlashBaseAddress;	

protected:

	// Checks whether a given bit toggles
	bool ToggleBit_PassControl( EFlashBitMask mask,
								SystemAddress  offsetAddress = 0 );
public:

	// Class constructor
	Am29_FlashProgrammer( SystemAddress flashBaseAddress );		

public:

	// This function ERASES the ENTIRE device
	bool ChipErase( void );

	// This function programs a block of the memory
	bool ProgramBlock( SystemAddress addressInFlash, 
				DataWordType * bufAddr, DataLen dataLen );
};





//////////////////////////////////////////////////
// "Knows" association

class PlotServer
{

	public:

		using DoubleVec = vector< double >;
		virtual void PlotData( const DoubleVec & x, const DoubleVec & y ) const
		{}

};

static const PlotServer	gPlotServer;	// common plotting server


class PartialEquationSolver
{

public:

	virtual void operator() ( void )
	{
		vector< double >	a, b;
		// ...
		gPlotServer.PlotData( a, b );	// action delegation to the server
	}

};


//////////////////////////////////////////////////
// Aggregation 

class Student			// Class_B (part)
{
	private:

		string	fName, fSurname;
		// ...

	public:
		// Student code here ...

};


class SchoolClassRegistry			// Class_A (whole)
{
	private:
	
		vector< Student >	fStudentGroup;	// registry aggregates students

	public:
		// FacultyRegistry code here

		// A student can be added to a class
		void AddStudent( const Student & );	

		// but also removed from a class
		void RemoveStudent( const Student & ); 

};



//////////////////////////////////////////////////
// Composition


class TEngine	// Class_B (part)
{
	private:

		double fEnginePower;	// common data for all engines

	public:
		// TEngine code here

		virtual void Run( void ) {}

};

class TCar	// Class_A (whole)
{

	private:

		unique_ptr< TEngine >	fEngine;	// composition association 
								// - fEngine is a part of TCar for all time

	public:
		// TCar code here

		// We can pass whatever engine we wish from the TEngine hierarchy
		TCar( unique_ptr< TEngine > engine ) : fEngine( move( engine ) )
		{}


};



//////////////////////////////////////////////////
// Inheritance



class GasEngine : public TEngine
{

};

class DieselEngine : public TEngine
{

};


class ElectricEngine : public TEngine
{

};


//////////////////////////////////////////////////

void CarTest( void )
{


	TCar	car( unique_ptr< TEngine > { new DieselEngine } );

}





