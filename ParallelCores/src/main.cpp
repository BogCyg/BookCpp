///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2020
///////////////////////////////////////////////////////


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

	//InnerProducts::InnerProduct_Test_GeneralExperiment();

	//FindMin_Test();
	MSE_Test();
	return 0;

	OpenMP_Test();

	//OpenMP_MultMatrix_Test();
	//OpenMP_MultMatrix_Test_1();

	//OpenMP_Pi_Test();

	//Parallel_Tasks_Test();

	return 0;
}


