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



#include <string>
#include <vector>
#include <iostream>
#include <tuple>






using std::tuple, std::get, std::tie, std::tuple_size, std::make_tuple, std::ignore;
using std::cout, std::endl;
using std::string;





void tuple_vs_struct( void )
{
	// -----------------------------
	{
		// Let's store a date in a tuple
		//     day   month  year
		tuple< int, string, int >	t_date( 27, "June", 2019 );

		// It can be easier with make_tuple
		auto t_date_2 = make_tuple( 27, "June", 2019 );

		// tuple_size<>::value returns the number of elements
		cout << "t_date has " << tuple_size< decltype(t_date) >::value 
			<< " elems" << endl;

		// Print the elements 
		cout << "D/M/Y:" << get< 0 >( t_date ) << "/" << 
			get< 1 >( t_date ) << "/" << 
			get< 2 >( t_date ) << endl;

		// Retrieve the elements to separate objects
		// with the structured binding
		const auto [ d, m, y ] = t_date;	

		// Print the elements 
		cout << "D/M/Y:" << d << "/" << 
			m << "/" << y << endl;

		// Use tie with ingore to retrieve a few elements
		int dd {};
		string mm {};

		// Retrieve only day and month, ignore the year
		tie( dd, mm, ignore ) = t_date;

		// Print the elements 
		cout << "D/M:" << dd << "/" << mm << endl;

	}

	// ------------------------------
	{
		// The same with struct with no name
		struct 
		{
			// Each field has its name
			int		fDay	{ 27 };
			string	fMonth	{ "June" };
			int		fYear	{ 2019 };
		} s_date;

		// We cannot enumerate a struct, 
		// just provide its field names.

		// Print the elements 
		cout << "D/M/Y:" << s_date.fDay << "/" << 
			s_date.fMonth << "/" << 
			s_date.fYear << endl;


		// Retrieve the elements to separate objects
		// with the structured binding
		const auto [ d, m, y ] = s_date;

		// Print the elements 
		cout << "D/M/Y:" << d << "/" << 
			m << "/" << y << endl;

	}

}



