///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2020
///////////////////////////////////////////////////////



#include <iostream>
#include <iomanip>
#include <sstream>
#include <omp.h>		// Header for OpenMP



#include "EMUtility.h"
#include "MarsXorShift.h"




// ------------------------------------------------------------------------
// Parallel versions






void OpenMP_Test( void )
{
	// This is a shared objects - the same for all threads.
	// A problem might happen if many threads want to 
	// write it SIMULTANEOUSLY.
	std::ostringstream outStream;

	// We start with a serial code executed by one thread line-after-line
	outStream << "Beginning with " << omp_get_num_threads() << " thread(s).\n";
	outStream << "Let's enter the omp parallel ...\n";

	// Before the parallel section can set a number 
	// of threads in a thread-team (do not confuse with cores)
	//omp_set_num_threads( 36 );	

	// ------------------------
	// --- This is PARALLEL ---
	// Let's see the TEAM of threads in action
	// However, declaring an object as shared
	// does NOT automatically makes its access
	// thread safe.
	#pragma omp parallel shared( outStream )
	{
		// This is a local variable; each thread has 
		// its own copy of it.
		auto thisThreadNo = omp_get_thread_num();

		// This is also a local object.
		const auto kNumOfThreads = omp_get_num_threads();

		// Let's use 'critical' to allow execution of
		// only one thread at a time - otherwise there
		// will be a mess on the screen.
		// Do NOT forget the 'omp' keyword here
		#pragma omp critical ( critical_0 )
		{
			outStream << "I'm thread no. " << thisThreadNo << " / " << kNumOfThreads << "\n";
		}

	}
	// Here is the SYNCHRONIZATION BARRIER - after that, all threads have finished
	// only the master executes
	// --- End of PARALLEL ---
	// ------------------------

	// One (master) thread again, no synchronization necessary.
	outStream << "After crossing the parallel BARRIER we run " << omp_get_num_threads() << " thread(s).\n";

	// Let see what we gathered
	std::cout << outStream.str() << std::endl;

}



// Computes pi with arctan(1) series summation.
// N - the number of terms in the series.
double Compute_Pi( int N )
{
	const double dx = 1.0 / static_cast< double >( N );

	// This is a SHARED variable
	double sum {};

	// -------------------------------------
	#pragma omp parallel for reduction( + : sum )	if( N > 1000000 )
	for( auto i = 0; i < N; ++ i )
	{
		auto c_i = dx * ( static_cast< double >( i ) + 0.5 );	// This is a local variable
		
		// S is shared, but unique access is guaranteed by the reduction
		sum += 1.0 / ( 1.0 + c_i * c_i );	
	}
	// -------------------------------------

	return 4.0 * dx * sum;
}



void OpenMP_Pi_Test( void )
{

	auto N_list = { 100, 1000, 10000, 100000000 };

	for( const auto N : N_list )
	{
		// Returns the number of seconds since the OS start-up.
		auto start_time = omp_get_wtime();	// Get start point
			auto pi = Compute_Pi( N );		// Do computations
		auto exec_time = omp_get_wtime() - start_time;	// End time

		std::cout	<< "pi(" << N << ")=" << std::setprecision( 12 ) 
					<< pi << " in " << exec_time << std::endl;
	}

}






// Overloaded operators 

// It can be used as follows: c = a + b;
EMatrix		operator + ( const EMatrix & a, const EMatrix & b )
{
	const auto a_cols = a.GetCols();
	const auto a_rows = a.GetRows();

	const auto b_cols = b.GetCols();
	const auto b_rows = b.GetRows();	

	assert( a_rows == b_rows );	// dim must be the same
	assert( a_cols == b_cols );

	EMatrix	c { a };	// Make c the same as a

						// Split the outermost for loop and run each chunk in a separate thread
#pragma omp parallel for \
		shared( b, c, b_rows, b_cols ) \
		default( none ) \
		schedule( static )

	for( Dim row = 0; row < b_rows; ++ row )
		for( Dim col = 0; col < b_cols; ++ col )
			c[ row ][ col ] += b[ row ][ col ];

	return c;
}

// It can be used as follows: c = a * b;
EMatrix		operator * ( const EMatrix & a, const EMatrix & b )
{
	const auto a_cols = a.GetCols();
	const auto a_rows = a.GetRows();

	const auto b_cols = b.GetCols();
	const auto b_rows = b.GetRows();	

	assert( a_cols == b_rows );			// Dimensions must be the same

	EMatrix	c( a_rows, b_cols, 0.0 );	// Output matrix has these dimensions

	// Split the outer-most for loop and run each chunk in a separate thread
	#pragma omp parallel for \
			shared( a, b, c, a_rows, b_cols, a_cols ) \
			default( none ) \
			schedule( static )
	// Only the outermost loop will be made parallel 
	for( Dim ar = 0; ar < a_rows; ++ ar )	// Traverse rows of a
		for( Dim bc = 0; bc < b_cols; ++ bc )	// Traverse cols of b
			for( Dim ac = 0; ac < a_cols; ++ ac ) // Traverse cols of a == rows of b
				c[ ar ][ bc ] += a[ ar ][ ac ] * b[ ac ][ bc ];


	return c;
}




// Does random initialization of a matrix m
void RandInit( EMatrix & m )
{
	MarsXorShift	randMachine;
	for( auto & row : m )			// go row-by-row
		for( auto & data : row )	// go through data in a single row
			data = randMachine.GetNext() & 0xFFFF;	// cast, type promotion
}




void OpenMP_MultMatrix_Test( void )
{
	const auto kCols { 1024 }, kRows { 1024 };
	EMatrix		a( kCols, kRows ), b( kRows, kCols );

	RandInit( a );
	RandInit( b );

	auto start_time = omp_get_wtime();	// Get time start point

	EMatrix		c( a * b );				

	auto exec_time = omp_get_wtime() - start_time;	// End time


	std::cout << "Middle elem val: " << c[ kCols / 2 ][ kCols / 2 ] << std::endl;
	std::cout << "Computation time: " << exec_time << std::endl;
}


void OpenMP_MultMatrix_Test_1( void )
{
	const auto kCols { 1024 }, kRows { 1024 };

	const auto N = { 1024, 2048, 4096 };

	std::cout << "Matrix multiplication test ..." << std::endl;

	for( const auto dim : N )
	{


		EMatrix		a( dim, dim ), b( dim, dim );

		RandInit( a );
		RandInit( b );

		auto start_time = omp_get_wtime();	// Get time start point

		EMatrix		c( a * b );				

		auto exec_time = omp_get_wtime() - start_time;	// End time measurement


		std::cout << "Elems: " << dim << std::endl;
		std::cout << "Middle elem val: " << c[ kCols / 2 ][ kCols / 2 ] << std::endl;
		std::cout << "Computation time: " << exec_time << std::endl << std::endl;

	}

}



// ------------------------------------
// An example of hazards due to 
// an unprotected shared object

int x;		// A global shared variable

void Task_0( void )
{
	auto loc { x };	// Local object
	
	// Non-protected access to shared
	x += 5;
	
	std::cout << loc << ", " << x << "\n";
}

void Task_1( void )
{
	#pragma omp critical ( section )
	{
		auto loc { x };	// Copy whatever value of x

		x += 5;	// ok

		std::cout << loc << ", " << x << "\n";
	}
}

void Parallel_Tasks_Test( void )
{
	// There is nothing wrong with Task_0 
	// when executed sequentially.
	for( auto i : { 1, 2, 3, 4, 5 } )
		Task_0();

	std::cout << "\n\n";

	// Run unprotected
	#pragma omp parallel num_threads( 5 )
	{		
		Task_0();
	}

	// Run with critical section
	#pragma omp parallel num_threads( 5 )
	{
		Task_1();
	}

}






