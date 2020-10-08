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



#include <vector>			// A header to use std::vector
#include <iostream>			// Headers for input and output
#include <iomanip>			// and output formatting
#include <cmath>			// For math functions


// Introduce these, to write vector instead of std::vector
using std::cout, std::cin, std::endl, std::vector; 


int main()
{

	cout << "Enter your grades" << endl;

	vector< double >		studentGradeVec;	// An empty vector of doubles

	// Collect student's grades
	for( ;; )
	{
		double grade {};

		cin >> grade;

		// If ok, push new grade at the end of the vector
		if( grade >= 2.0 && grade <= 5.0 )
			studentGradeVec.push_back( grade );

	
		cout << "Enter more? [y/n] "; 
		char ans {};
		cin >> ans;

		if( ans == 'n' || ans == 'N' )
			break;		// the way to exit the loop
	}

	
	// Ok, if there are any grades compute the average
	if( studentGradeVec.size() > 0 )
	{
		double sum { 0.0 };
		// Add all the grades
		for( auto g : studentGradeVec )
			sum += g;

		double av = sum / studentGradeVec.size();

		double finalGrade {};

		// Let it adjust
		if( av < 3.0 )
		{
			finalGrade = 2.0;
		}
		else
		{
			double near_int = std::floor( av );	// get integer part
			double frac		= av - near_int;	// get only the fraction

			double adjust { 0.5 };	// new adjustment value

			if( frac < 0.25 )
				adjust = 0.0;
			else if( frac > 0.75 )
				adjust = 1.0;

			finalGrade = near_int + adjust;
		}

		cout	<< "Final grade: " 
				<< std::fixed << std::setw( 3 ) << std::setprecision( 1 ) 
				<< finalGrade << endl;

	}


	return 0;
}


