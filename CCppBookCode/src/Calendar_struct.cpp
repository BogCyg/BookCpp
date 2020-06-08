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



// Joins two different objects under one roof
struct MonthDays
{
	std::string		fName {};	// Always use {} to initialize data members.
	int				fDays {};	// Empty {} initialize to 0.
};


// Creates and displays a simple calendar
void SimpleCalendar( void )
{
	const std::vector< MonthDays >	calendar {	
												{ "January",		31 },
												{ "February",		28 },
												{ "March",			31 },
												{ "April",			30 },
												{ "May",			31 },
												{ "June",			30 },
												{ "July",			31 },
												{ "August",			31 },
												{ "September",		30 },
												{ "October",		31 },
												{ "November",		30 },
												{ "December",		31 }

										};

	// Print them on the screen
	auto sum_days { 0 };
	for( auto month : calendar )
	{
		sum_days += month.fDays;
		std::cout << month.fName << " has " << month.fDays << " days\n";
	}

	std::cout << "\nTotal days: " << sum_days << std::endl;
}





