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
#include <vector>
#include <algorithm>
#include <iostream>

namespace InnerProducts
{
	void InnerProduct_Test_GeneralExperiment( void );
}


void OpenMP_Test( void );
void OpenMP_Pi_Test( void );
void OpenMP_MultMatrix_Test( void );
void OpenMP_MultMatrix_Test_1( void );

void Parallel_Tasks_Test(void);


void FindMin_Test( void );
void MSE_Test( void );



int main()
{
	std::cout << "Good day!" << std::endl;


	OpenMP_Test();

	OpenMP_MultMatrix_Test();
	OpenMP_MultMatrix_Test_1();

	OpenMP_Pi_Test();

	FindMin_Test();

	MSE_Test();

	Parallel_Tasks_Test();

	InnerProducts::InnerProduct_Test_GeneralExperiment();


	return 0;
}


