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
#include <array>
#include <list>
#include <iostream>
#include <cassert>




namespace EventSystem
{


	// Base class defining an ACTION
	// Also can be chained in a list
	class THandler
	{

	public:

		virtual ~THandler() = 0					// virtual for proper inheritance
		{ std::cout << "~H()" << std::endl; }	// Pure virtual but can have a diagnostic body

												// Main action function ==> functional object
		virtual void operator () ( void ) = 0;	// Pure virtual to define INTERFACE for derived classes

	};




	class TEventHandlers
	{
	public:

		enum class EEvent { kReset, kDivByZero, kExternal, kSpurious, kSentinel };


		using TH_UP = std::unique_ptr< THandler >;
		using HandlerList = std::list< TH_UP >;

		// An array that contains lists of THandler like objects
		using EventVector = std::array< HandlerList, static_cast< int >( EEvent::kSentinel ) >;

	private:

		EventVector		fEventVector;

	public:

		void AttachHandler_4_Event( EEvent event_to_attach, TH_UP new_handler )
		{
			assert( static_cast< int >( event_to_attach ) < static_cast< int >( EEvent::kSentinel ) );
			fEventVector[ static_cast< int >( event_to_attach ) ].emplace_back( std::move( new_handler ) );	// or emplace_front
		}

		// Run handlers attached to the event
		virtual void operator () ( const HandlerList & list_of_handlers )
		{

			for( const auto & handler : list_of_handlers )
				( * handler )();
		}

		virtual void operator () ( EEvent event )
		{
			// One way to call a functional operator 
			operator () ( fEventVector[ static_cast< int >( event ) ] );
		}

		// Run all
		virtual void operator () ( void )
		{
			for( const auto & list : fEventVector )
				( * this ) ( list );	// Call operator () ( EEvent event )
										//operator() ( list );
		}


	};



	void EventHandlers_Test( void )
	{

		TEventHandlers		theHandlerBoard;


		// -------------------
		// Create a few handlers

		class HA : public THandler
		{
			std::string	fStr;

		public:

			HA( std::string s = "" ) : fStr( s ) {}
			virtual ~HA() { std::cout << "~HA()" << std::endl; }

			void operator () ( void ) override	// it is also virtual but override is enough to express this
			{
				std::cout << "I'm HA with text: " << fStr << std::endl;
			}
		};

		class HB : public THandler
		{
			int	fVal;

		public:

			HB( int v = 0 ) : fVal( v ) {}
			virtual ~HB() { std::cout << "~HB()" << std::endl; }

			void operator () ( void ) override 
			{
				std::cout << "I'm HB: " << std::dec << fVal << " = " << std::hex << fVal << std::endl;
			}
		};
		// -------------------

		HA ha( "Standalone HA" );
		ha();						// Call the function operator on object ha

		( HB( 789 ) )();			// Call the function operator on a temporary object HB

		std::cout << std::endl;

		// Now attach no matter how many handlers to the available event slots

		theHandlerBoard.AttachHandler_4_Event( TEventHandlers::EEvent::kReset, std::make_unique< HA >( "Reset 0" ) );
		theHandlerBoard.AttachHandler_4_Event( TEventHandlers::EEvent::kReset, std::make_unique< HB >( 123 ) );
		theHandlerBoard.AttachHandler_4_Event( TEventHandlers::EEvent::kReset, std::make_unique< HA >( "Reset 1" ) );


		theHandlerBoard.AttachHandler_4_Event( TEventHandlers::EEvent::kExternal, std::make_unique< HB >( 100 ) );
		theHandlerBoard.AttachHandler_4_Event( TEventHandlers::EEvent::kExternal, std::make_unique< HB >( 200 ) );


		theHandlerBoard();		// Run all

	}







}


// --------------------------------------------------------
