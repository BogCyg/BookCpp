///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////



#include <vector>
#include <string>



#include "XML_CurrencyExchanger.h"
#include "CurrencyCalcPlayGround.h"



// Forward declarations
class Fl_Choice;		
class Fl_Float_Input;
class Fl_Value_Output;	
class Fl_Window;		
class Fl_Widget;



namespace OL_CE = CurrExchanger::OnLine_CurrExchanger;



// CC - Currency Calculator
class CC_GUI
{
	private:

		// Pointers to the FLTK widgets
		Fl_Choice *			fChoiceWidget {};
		Fl_Float_Input *	fEditWidget {};
		Fl_Value_Output	*	fStaticEditWidget {};
		Fl_Window *			fMainWindow {};				



	private:

		// An interface to our currency calculator component

		using XCE = OL_CE::XML_CurrencyExchanger;


		XCE &		fXML_CurrencyExchanger;

		// Initial code of the reference currency
		std::wstring		fFromCurrencyCode;


	public:

		CC_GUI( XCE & xce, const std::wstring & fromCurrency = L"PLN" );
	
		virtual ~CC_GUI();

	private:

		///////////////////////////////////////////////////////////
		// CALLBACK FUNCTION - do NOT modify !!!
		///////////////////////////////////////////////////////////
		//		
		// INPUT:
		//			widgetPtr - a pointer to the button widget
		//			obj - a pointer "this" to CC_GUI object
		//		
		// OUTPUT:
		//			none
		//		
		// REMARKS:
		//			A static function to be put as the FLTK button callback 
		//			Delegates an action to the Action_On_Button().
		//	
		static void theButtonCallback( Fl_Widget * widgetPtr, void * obj );

	protected:

		///////////////////////////////////////////////////////////
		// Local function to process button requests
		///////////////////////////////////////////////////////////
		//		
		// INPUT:
		//			none
		//		
		// OUTPUT:
		//			true if ok
		//		
		// REMARKS:
		//		
		//	
		virtual bool Action_On_Button( void );

	private:

		///////////////////////////////////////////////////////////
		// Converter of a three-letter code to one word with bytes
		// set with code characters.
		///////////////////////////////////////////////////////////
		//		
		// INPUT:
		//			wstr - a wide-string object with 3 letters code
		//		
		// OUTPUT:
		//			the code in one word
		//		
		// REMARKS:
		//		
		//	
		unsigned long	CurrencyKey_2_Code( const std::wstring & wstr );

		///////////////////////////////////////////////////////////
		// Converts one word currency code to the wide string code
		///////////////////////////////////////////////////////////
		//		
		// INPUT:
		//			code - a word with letters in each byte, starting
		//				from the LSB
		//		
		// OUTPUT:
		//			wstring with the letters from the input word
		//		
		// REMARKS:
		//		
		//	
		std::wstring			Code_2_CurrencyKey( const unsigned long & code );



	public:


		///////////////////////////////////////////////////////////
		// This function creates the Graphical User Interface
		// and runs the application.
		///////////////////////////////////////////////////////////
		//		
		// INPUT:
		//			none
		//		
		// OUTPUT:
		//			FLTK status code
		//		
		// REMARKS:
		//			This function does not exit, only upon
		//			exit from the application
		//	
		virtual int Create_GUI( void );



};			// end of CC_GUI

