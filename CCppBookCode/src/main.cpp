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
#include <cassert>
#include <filesystem>
#include <string>




using std::cout, std::cin, std::endl;
using std::string, std::wstring;
using std::vector;

namespace fs = std::filesystem;


#include "RevertEndianness.h"

#include "main_declarations.h"




// Raw text with some instructions.
const std::string msg {
	R"(

		Welcome to one of the projects containing code examples from the book:
		INTRODUCTION TO PROGRAMMING WITH C++ FOR ENGINEERS
		by Boguslaw Cyganek, Wiley 2020.

		To find a code to launch use a search tool
		to match a characteristic part of that code from
		the book with the code in this project.

		Many examples are just simple code snippets
		only to show a given method or a technique.
		Detailed explanations of their behavior is in the book.

		Many examples which are in the book are put 
		into separate projects.

	)"
};




// -------------
int main( void )
{

	cout << "===========================" << endl;
	cout << "CCppBookCode - let's begin!" << endl;
	cout << GetCurrentTime();
	cout << "===========================" << endl << endl;


	cout << msg << endl << endl;



	// Define some constants, starting form value 1, since our chapters also begin from 1
	enum EBCppBookChapters {	k_1_Intro = 1, k_2_IntroToProgramming, k_3_CppBasics, k_4_DelvingIntoOOP,
								k_5_Memory, k_6_AdvancingOOP, k_7_CompArithm, k_8_BasicsOfParallelProg,
								k_9_Appendix };


	

	cout << "To launch examples enter the chapter number [1-9]: ";
	
	if( auto my_chapter { 0 };	cin >> my_chapter && 
								my_chapter >= EBCppBookChapters::k_1_Intro && 
								my_chapter <= EBCppBookChapters::k_9_Appendix )
	

		switch( my_chapter )
		{
			// ----------------------------------------
			// Run examples of chapter 1 "Introduction"
			case EBCppBookChapters::k_1_Intro:
			{

				// Display a message in the terminal window 
				// Prefix std:: tells to use objects from the standard library (SL). 
				std::cout << "Good day to you!" << std::endl;  

			}
			break;

			// -------------------------------------------------------
			// Run examples of chapter 2 "Introduction to Programming"
			case EBCppBookChapters::k_2_IntroToProgramming:
			{
				{
					double x { 0.0 };			// Define and initialize a variable x 
					        
					std::cout << "Enter x=";	// Print a message 
					std::cin >> x;				// Enter value of x from the keyboard 
					
					if( x >= 0.0 )				// Check if x is positive 
						std::cout << "\nSqrt(" << x << ") = " << std::sqrt( x ) << std::endl; 
					else 
						std::cout << "\nWrong value - cannot compute Sqrt\n"; 	
				}

				letter_histogram();

				letter_histogram_stl();

			}
			break;

			// ----------------------------------------
			// Run examples of chapter 3 "C++ Basics"
			case EBCppBookChapters::k_3_CppBasics:
			{
				auto_test();


				BasicTypes_Examples();

				MoreOnBasicTypes();


				BCpp_Simple_Derivatives::deriv_test_fun();
				BCpp_Derivatives::deriv_test_fun_ex();

				String_Test_1();

				Vector_Test_1();
				Vector_Test_2();

				CppBook::LoopStatements();

				TransformTest();

				SimpleCalendar();

				ConstSizeArrayTest_1();	
				ConstSizeArrayTest_2();	
				ConstSizeArrayTest_3();
				ConstSizeArrayTest_4();

				iterators_ex();

				ios_manip_test();

				tuple_vs_struct();

				CRC_Test();


				FiboRecursive_Test();

				cout << endl << endl;

				SumOfSquaresTest();

				TestMakeTuple();

				multi_print_helper_test();


				LambdaTestFun_0();
				LambdaTestFun_1();
				LambdaTestFun_2();

				SCUBA_Course();


				bool d2r_chain_stat = Decimal_2_Roman_Chain_UnitTest();
				//assert( d2r_chain_stat == true );		not ready yet, to be solved in the exercise section

				bool d2r_test_stat = ConvertDecimal_2_Roman_UnitTest();
				assert( d2r_test_stat == true );

				Dec_2_Roman_Test();


				Switch_17_test();

				TinyCubeTest();

				MultiDimArray_Test();

				OperatorReview();


				// Run the prime numbers sieve
				cout << "Results of the sieve or Eratosthenes:\n";
				for( auto a : EratosthenesSieve( 100 ) )
					cout << a << ", ";

				cout << endl;

				// Run for Fibonacci numbers
				cout << "The Fibonacci numbers:\n";
				for( auto a : FibonacciNumbers( 100 ) )
					cout << a << ", ";

				cout << endl;

				// Run the bubble sort exercise
				cout << "\n\033[32mRun the bubble sort exercise:\033[0m\n";
				BubbleSortTest();

				cout << endl;

			}
			break;

			// ------------------------------------------------------------------------
			// Run examples of chapter 4 "Delving into the Object-Oriented Programming"
			case EBCppBookChapters::k_4_DelvingIntoOOP:
			{
				CircleTest();

				s_min_test();

				RevertEndianness_Test();

				CRTP_Test::StaticPolymorphism_Test();

				MixinTest();

				a_min_test();

				UniversalReference_Test();

				Right_ReferenceTest();

				ReferenceTest();

			}
			break;

			// ---------------------------------------------
			// Run examples of chapter 5 "Memory Management"
			case EBCppBookChapters::k_5_Memory:
			{


				unique_ptr_OrphanAcceptTest();


				var_test_fun();

				do_action_test();





				double_linked_list_test();

				weak_ptr_test();

				donator();

				shared_ptr_test();

				unique_ptr_tests();

				FactoryTest();

				a_p_test();

				double_linked_list_test();

			}
			break;

			// ---------------------------------------------------------------------
			// Run examples of chapter 6 "Advancing the Object-Oriented Programming"
			case EBCppBookChapters::k_6_AdvancingOOP:
			{

				EventSystem::EventHandlers_Test();

				RecursivelyTraverseDirectory( L"..\\..\\EmptyPro" );

				TestFunctionTimeMeasurement();


				DisplayPathParts( fs::current_path() );

				RangeTest();


				fun_perform_timer_test();


				CreateDirAndFiles( fs::current_path(), L"Playground" );


				regex_test();

			}
			break;

			// -----------------------------------------------
			// Run examples of chapter 7 "Computer Arithmetic"
			case EBCppBookChapters::k_7_CompArithm:
			{
				FxPt_Test_1();


				auto x { 1024 };
				cout << "FP_Sqrt_Approx( " << std::to_string( x ) << " ) = " << FP_Sqrt_Approx( x ) << endl;
				cout << "IntSqrt( " << std::to_string( x ) << " ) = " << IntSqrt( x ) << endl;
				cout << "IntSqrt( " << std::to_string( x ) << " ) = " << IntSqrt_Rec_FunObj( x ) << endl;
				cout << "IntSqrt( " << std::to_string( x ) << " ) = " << IntSqrt_Rec_Lambda( x ) << endl;


				Test_Float_1();				
				Test_Float_1b();				
				Test_Float_1c();				
				Test_Float_1d();				
			
				Test_Float_3();
				Test_Float_4();

				Float_Mult_Test();


				NewtonZero::NewtonZero_Test();
				NewtonZero::SquareRoot_Test();


				InnerProducts::InnerProduct_Test();

			}
			break;

			// ----------------------------------------------------------
			// Run examples of chapter 8 "Basics of Parallel Programming"
			case EBCppBookChapters::k_8_BasicsOfParallelProg:
			{

				ThreadTest();
			}
			break;

			// ------------------------------------
			// Run examples of chapter 9 "APPENDIX"
			case EBCppBookChapters::k_9_Appendix:
			{

				BuiltIn_ArrayTest_1();

				BuiltIn_ArrayTest_2();


			}
			break;


			default:
				assert( false );		// should not reach here
				break;

		}

	





	cout << endl << "That's it for now, exiting ..." << endl;


	return 0;
}








