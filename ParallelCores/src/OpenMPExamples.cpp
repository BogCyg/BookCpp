///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2020
///////////////////////////////////////////////////////



#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include <random>
#include <limits>
#include <numeric>		// for inner product

#include <omp.h>		// Header for OpenMP





// -------------------------------------------
// Some examples to the tables


using elem_type = int;
using vec = std::vector< elem_type >;
using size_type = vec::size_type;


// ----------------------------------------------------------------


std::tuple< int, int > FindMin( const std::vector< int > & v )
{
	const auto data_num = v.size();
	if( data_num == 0 )
		return std::make_tuple( -1, -1 );

	const auto * src_data_ptr = & v[ 0 ];

	auto sh_val = * src_data_ptr;
	auto sh_offset { 0 };

	// Take an upper limit to find the lowest value
	auto loc_val { std::numeric_limits< int >::max() };		
	auto loc_offset { -1 };

	// Use firstprivate to convey the initial values of 
	// loc_val and loc_offset.
	// Shared objects are 
	#pragma omp parallel default( none ) \
			firstprivate( loc_val, loc_offset ) \
			shared( sh_val, sh_offset, src_data_ptr, data_num )
	{
		// Each thread will take its payload and determine 
		// its lowest local pixel (reduction for min)
		#pragma omp for nowait
		for( auto i = 0; i < data_num; ++ i )
		{
			auto elem { src_data_ptr[ i ] };
			if( elem < loc_val )
			{
				loc_val = elem;
				loc_offset = i;
			}
		}	// no barrier here due to the nowait clause

		// Enter a critical section here
		#pragma omp critical 
		if( loc_val < sh_val )
		{
			sh_val = loc_val;			// Save lowest value in this thread
			sh_offset = loc_offset;		// and its position
		}

	}	// a barrier here

	return std::make_tuple( sh_val, sh_offset );
}


void FindMin_Test( void )
{
	auto num_of_data { 100000000 };
	std::vector< int >		test_vec;

	test_vec.resize( num_of_data );
	std::mt19937		rand_gen{ std::random_device{}() };	// Random Mersenne twister
	std::uniform_int_distribution dist( 0, 255 );
	std::generate( test_vec.begin(), test_vec.end(), [ & ](){ return dist( rand_gen ); } );

	// Set a minimal value 'somewhere'
	test_vec[ test_vec.size() / 2 ] = -11;
	test_vec[ test_vec.size() / 4 ] = -13;


	auto start_time = omp_get_wtime();	// Get time start point

		std::tuple< int, int > res = FindMin( test_vec );

	auto exec_time = omp_get_wtime() - start_time;	// End time

	std::cout	<< "Min val: " << std::get< 0 >( res ) 
				<< " @ idx: " << std::get< 1 >( res ) 
				<< " Time: " << exec_time << std::endl;

}


// ----------------------------------------------------------------


// Computes the mean squared error (MSE) between two real vectors
double MSE( const std::vector< double > & u, const std::vector< double > & v )
{
	const auto data_num = std::min( u.size(), v.size() );

	if( data_num == 0 )
		return -1.0;	// Simple error checking

	const auto * u_data = & u[ 0 ];
	const auto * v_data = & v[ 0 ];

	auto sum { 0.0 };	// Shared due to the reduction clause

	#pragma omp parallel for default( none ) \
			shared( u_data, v_data, data_num ) \
			reduction( + : sum ) \
			schedule( static ) \
			if( data_num > 10000 )

	for( auto i = 0; i < data_num; ++ i )
	{
		auto diff = u_data[ i ] - v_data[ i ];
		sum += diff * diff;
	}	// Here we have a common barrier

	return sum / static_cast< double >( data_num );
}



void MSE_Test( void )
{
	auto num_of_data { 100000000 };
	std::vector< double >		u, v;

	std::mt19937		rand_gen{ std::random_device{}() };	// Random Mersenne twister
	std::uniform_real_distribution dist( -255.0, 255.0 );

	u.resize( num_of_data );
	std::generate( u.begin(), u.end(), [ & ](){ return dist( rand_gen ); } );

	v.resize( num_of_data );
	std::generate( v.begin(), v.end(), [ & ](){ return dist( rand_gen ); } );


	auto start_time = omp_get_wtime();	// Get time start point

	auto mse = MSE( u, v );

	auto exec_time = omp_get_wtime() - start_time;	// End time

	std::cout << "MSE = " << mse << " Time: " << exec_time << std::endl;
}



// ----------------------------------------------------------------

void ParSections( void )
{
	const auto N { 100000 };
	// ... init data

	omp_set_nested( 1 );	// Allow for nested parallelism

	// Sections allow for a pipeline organization.
	// Create a team of threads.
	// If sufficient threads, the sections execute simultaneously.
	#pragma omp parallel sections
	{
		// Executes simultaneously with the next secton
		#pragma omp section
		{
			// If sufficient threads, there will be nested parallelism
			#pragma omp parallel shared( N ) num_threads( 2 )
			for( auto i = 0; i < N; ++ i )
			{
				// ... compute something
			}
		
		}
	
		// Executes simultaneously with the previous secton
		#pragma omp section
		{
			#pragma omp parallel shared( N ) num_threads( 4 )
			for( auto i = 0; i < N; ++ i )
			{
				// ... compute something
			}

		}
	
	}

}





// ----------------------------------------------------------------




