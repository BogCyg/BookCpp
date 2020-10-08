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



#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <limits>
#include <numeric>		// for inner product

#include <execution>
#include <thread>
#include <future>

#include <chrono>
#include <ctime>

#include <fstream>
#include <iterator>
#include <array>



using namespace std;



namespace InnerProducts
{

	using DVec = vector< double >;
	using DT = DVec::value_type;
	using ST = DVec::size_type;

	using std::inner_product;
	using std::transform;
	using std::accumulate;
	using std::sort;




	////////////////////////////////
	// Value generators
	namespace FP_Test_DataSet_Generator
	{


		void Fill_Numerical_Data_MersenneUniform( DVec & inVec, ST num_of_data, DT kDataMag )
		{
			inVec.resize( num_of_data );
			assert( inVec.size() == num_of_data );
			mt19937		rand_gen{ random_device{}() };	// Random Mersenne twister
			uniform_real_distribution< double > dist( - kDataMag, + kDataMag );
			std::generate( inVec.begin(), inVec.end(), [ & ](){ return dist( rand_gen ); } );
		}

		// 
		void Duplicate( DVec & inVec, DT multFactor = 1.0 )
		{
			ST kElems { inVec.size() };
			inVec.resize( 2 * kElems );
			std::generate( inVec.begin() + kElems, inVec.end(), 
				[ n = 0, & inVec, multFactor ] () mutable { return multFactor * inVec[ n ++ ]; } );
		}

		void DuplicateWithNegated( DVec & inVec )
		{
			Duplicate( inVec, -1.0 );
		}


	}
	////////////////////////////////



	auto InnerProduct_StdAlg( const DVec & v, const DVec & w )
	{
		// The last argument is an initial value
		return std::inner_product( v.begin(), v.end(), w.begin(), DT() );
	}



	auto InnerProduct_SortAlg( const DVec & v, const DVec & w )
	{
		//DVec z;		// Stores element-wise products
		DVec z( v.size() );		// Stores element-wise products

		// Elementwise multiplication: c = v .* w
		std::transform(	v.begin(), v.end(), w.begin(), 
						/*std::back_inserter( z )*/z.begin(), 
						[] ( const auto & v_el, const auto & w_el) { return v_el * w_el; } );

		// Serial sort
		std::sort( z.begin(), z.end(), [] ( const DT & p, const DT & q ) { return fabs( p ) < fabs( q ); } );		// Is it magic? ***

		// The last argument is an initial value
		return std::accumulate( z.begin(), z.end(), DT() );
	}

	// -----------------
	// PARALLEL VERSIONS

	// Parallel version of the inner product with transform-reduce 
	auto InnerProduct_TransformReduce_Par( const DVec & v, const DVec & w )
	{
		return std::transform_reduce(	std::execution::par,
										v.begin(), v.end(), w.begin(), DT(),
										[] ( const auto a, const auto b ) { return a + b; },
										[] ( const auto a, const auto b ) { return a * b; }
		);
	}

	// Parallel version of the inner product with sorting
	auto InnerProduct_SortAlg_Par( const DVec & v, const DVec & w )
	{
		DVec z( v.size() );		// Stores element-wise products

		// PARALLEL elementwise multiplication: c = v .* w
		std::transform(	std::execution::par,
						v.begin(), v.end(), w.begin(), 
						z.begin(), 
						[] ( const auto & v_el, const auto & w_el) { return v_el * w_el; } );

		// PARALLEL sort in ascending  order
		std::sort( std::execution::par, z.begin(), z.end(), [] ( const DT & p, const DT & q ) { return fabs( p ) < fabs( q ); } );		// Is it magic?

		// PARALLEL summation 
		return std::reduce( std::execution::par, z.begin(), z.end() );
	}







	
	// ACTUALLY IF WE NEED TO SORT, THEN WE DO NOT NEED THE KAHAN ALGORITHM
	// since the sort-and-accumulate is the best
	// In the Kahan algorithm each addition is corrected by a correction
	// factor. In this algorithm the non associativity of FP is used, i.e.:
	// ( a + b ) + c != a + ( b + c )
	// v will be changed
	auto Kahan_Sum( DVec & v )
	{
		DT theSum {};

		// volatile prevents a compiler from applying any optimization
		// on the object since it can be changed by someone else, etc.,
		// in a way that cannot be foreseen by the compiler.

		volatile DT c {};		// a "correction" coefficient

		for( ST i = 0; i < v.size(); ++ i )
		{
			DT y = v[ i ] - c;			// From the summand y subtract the correction factor

			DT t = theSum + y;			// Add corrected summand to the running sum, i.e. theSum
										// But theSum is big, y is small, so its lower bits will be lost

			c = ( t - theSum ) - y;		// Low order bits of y are lost in the summation. High order
										// bits of y are computed in ( t - theSum ). Then, when y
										// is subtracted from this, the low order bits of y are recovered (negative).
										// Algebraically, c should always be 0 (beware of compiler optimization).
			theSum = t;
		}

		return theSum;
	}




#if 0
	auto InnerProduct_Sort_KahanAlg(  const double * v, const double * w, const size_t kElems  )
	{
		DVec z;		// Stores element-wise products

					// Elementwise multiplication: c = a .* b
		transform(	v, v + kElems, w, 
			back_inserter( z ), 
			[] ( const auto & v_el, const auto & w_el) { return v_el * w_el; } );

		sort( /*std::execution::par, */z.begin(), z.end(), [] ( const DT & p, const DT & q ) { return ! ( p < q ); } );		// Is it magic?

																															// ------------------------



		DT theSum {};

		// volatile prevents a compiler from applying any optimization
		// on the object since it can be changed by someone else, etc.,
		// in a way that cannot be foreseen by the compiler.

		volatile DT c {};		// a "correction" factor


		for( ST i = 0; i < z.size(); ++ i )
		{
			DT y = z[ i ] - c;	// From the summand y subtract the correction factor

			DT t = theSum + y;			// Add corrected summand to the running sum, i.e. theSum
										// But theSum is bit, y is small, so its lower bits will be lost

			c = ( t - theSum ) - y;		// Low order bits of y are lost in the summation. High order
										// bits of y are computed in ( t - theSum ). Then, when y
										// is subtracted from this, the low order bits of y are recovered (negative).
										// Algebraically, c should always be 0 (beware of compiler optimization).
			theSum = t;
		}

		return theSum;
	}


#endif
	// ACTUALLY IF WE NEED TO SORT, THEN WE DO NOT NEED THE KAHAN ALGORITHM
	// since the sort-and-accumulate is the best
	// In the Kahan algorithm each addition is corrected by a correction
	// factor. In this algorithm the non associativity of FP is used, i.e.:
	// ( a + b ) + c != a + ( b + c )
	// v will be changed
	auto Kahan_Sort_And_Sum( DVec & v )
	{
		sort( std::execution::par, v.begin(), v.end(), [] ( const DT & p, const DT & q ) { return fabs( p ) < fabs( q ); } );	
		return Kahan_Sum( v );
	}



	// Other version of the Kahan algorithms
	auto InnerProduct_KahanAlg( const double * v, const double * w, const size_t kElems )
	{
		DT theSum {};

		// volatile prevents a compiler from applying any optimization
		// on the object since it can be changed by someone else, etc.,
		// in a way that cannot be foreseen by the compiler.

		volatile DT c {};		// a "correction" coefficient


		for( ST i = 0; i < kElems; ++ i )
		{
			DT y = v[ i ] * w[ i ] - c;	// From the summand y subtract the correction factor

			DT t = theSum + y;			// Add corrected summand to the running sum, i.e. theSum
										// But theSum is bit, y is small, so its lower bits will be lost

			c = ( t - theSum ) - y;		// Low order bits of y are lost in the summation. High order
										// bits of y are computed in ( t - theSum ). Then, when y
										// is subtracted from this, the low order bits of y are recovered (negative).
										// Algebraically, c should always be 0 (beware of compiler optimization).
			theSum = t;
		}

		return theSum;
	}

	


	// THE BEST PERFORMANCE
	// This is a simple data parallelizing of the Kahan algorithm.
	// The input vectors are divided into chunks that are 
	// then processed in parallel but by the serial Kahan algorithm.
	// The partial sums are then summed up with yet run of the
	// Kahan algorithm.
	auto InnerProduct_KahanAlg_Par( const DVec & v, const DVec & w, const ST kChunkSize = 10000 )
	{
		const auto kMinSize { std::min( v.size(), w.size() ) };

		const auto k_num_of_chunks { ( kMinSize / kChunkSize ) };
		const auto k_remainder { kMinSize % kChunkSize };

		const double * v_data_begin = & v[ 0 ];
		const double * w_data_begin = & w[ 0 ];

		vector< double >	par_sum( k_num_of_chunks + ( k_remainder > 0 ? 1 : 0 ), 0.0 );	

		// The thing is that we wish Kahan because it is much faster than the sort-accum
		auto fun_inter = [] ( const double * a, const double * b, int s ) { return InnerProduct_KahanAlg( a, b, s ); };

		vector< future< double > >		my_thread_pool;

		// Process all equal size chunks of data
		std::decay< decltype( k_num_of_chunks ) >::type i {}; 
		for( i = 0; i < k_num_of_chunks; ++ i )
			my_thread_pool.push_back( async( std::launch::async, fun_inter, v_data_begin + i * kChunkSize, w_data_begin + i * kChunkSize, kChunkSize ) );

		// Process the remainder, if present
		if( k_remainder > 0 )

			my_thread_pool.push_back( async( std::launch::async, fun_inter, v_data_begin + i * kChunkSize, w_data_begin + i * kChunkSize, k_remainder ) );

		assert( par_sum.size() == my_thread_pool.size() );
		for( i = 0; i < my_thread_pool.size(); ++ i )
			par_sum[ i ] = my_thread_pool[ i ].get();			// get() blocks until the async is done

		return Kahan_Sort_And_Sum( par_sum );			
		//return Kahan_Sum( par_sum );			
	}

#if 0
	auto InnerProduct_SortKahanAlg_Par( const DVec & v, const DVec & w, const size_t kChunkSize = 10000 )
	{
		const auto kMinSize { std::min( v.size(), w.size() ) };

		const auto k_num_of_chunks { ( kMinSize / kChunkSize ) };
		const auto k_remainder { kMinSize % kChunkSize };


		const double * v_data_begin = & v[ 0 ];
		const double * w_data_begin = & w[ 0 ];

		vector< double >	par_sum( k_num_of_chunks + ( k_remainder > 0 ? 1 : 0 ), 0.0 );

		// The thing is that we wish Kahan because it is much faster than the sort-accum
		auto fun_inter = [] ( const double * a, const double * b, int s ) { return InnerProduct_Sort_KahanAlg( a, b, s ); };

		vector< future< double > >		my_thread_poool;

		// Process all equal size chunks of data
		std::decay< decltype( k_num_of_chunks ) >::type i {};
		for( i = 0; i < k_num_of_chunks; ++ i )
			my_thread_poool.push_back( async( std::launch::async, fun_inter, v_data_begin + i * kChunkSize, w_data_begin + i * kChunkSize, kChunkSize ) );

		// Process the ramainder, if present
		if( k_remainder > 0 )
			my_thread_poool.push_back( async( std::launch::async, fun_inter, v_data_begin + i * kChunkSize, w_data_begin + i * kChunkSize, k_remainder ) );

		for( size_t i = 0; i < my_thread_poool.size(); ++ i )
			par_sum[ i ] = my_thread_poool[ i ].get();


		return Kahan_Sort_And_Sum( par_sum );		
	}
#endif



	
	auto InnerProduct_Test( DVec & v, DVec & w )
	{
		assert( v.size() == w.size() );

		// Both dimensions of v and w must be the same
		// and must be an integer multiplication of the kChunkSize
		const int kChunkSize { /*10000*/25000 /*(int) std::ceil( sqrt( (double) v.size() ) )*/ };


		// The inner product should be close to 0.0, 
		// so let us check the two algorithms.

		using timer = typename std::chrono::high_resolution_clock;
		auto get_duration = [] ( auto prev_time_stamp ) 
							{ return std::chrono::duration_cast< std::chrono::milliseconds >( 
													timer::now() - prev_time_stamp ).count(); };


		DVec	result_errors;
		DVec	result_timing;


		auto comp_error { 0.0 };



		auto ts = timer::now();
		comp_error = fabs( InnerProduct_StdAlg( v, w ) );
		auto tdur = get_duration( ts );
		cout << "Serial accumulate error = \t"	<< std::setprecision( 8 ) << comp_error << "\t\tT [ms] = " << tdur << endl;
		result_errors.push_back( comp_error );
		result_timing.push_back( tdur );


		ts = timer::now();
		comp_error = fabs( InnerProduct_TransformReduce_Par( v, w ) );
		tdur = get_duration( ts );
		cout << "Parallel Transform-Reduce alg error = \t"	<< std::setprecision( 8 ) << comp_error << "\t\tT [ms] = " << tdur << endl;
		result_errors.push_back( comp_error );
		result_timing.push_back( tdur );
		
		ts = timer::now();
		comp_error = fabs( InnerProduct_SortAlg( v, w ) );
		tdur = get_duration( ts );
		cout << "Serial sort alg error = \t"	<< std::setprecision( 8 ) << comp_error << "\t\tT [ms] = " << tdur << endl;
		result_errors.push_back( comp_error );
		result_timing.push_back( tdur );
		
		ts = timer::now();
		comp_error = fabs( InnerProduct_SortAlg_Par( v, w ) );
		tdur = get_duration( ts );
		cout << "Parallel sort alg error = \t"	<< std::setprecision( 8 ) << comp_error << "\t\tT [ms] = " << tdur << endl;
		result_errors.push_back( comp_error );
		result_timing.push_back( tdur );
		

		// - - - - - -

		ts = timer::now();
		comp_error = fabs( InnerProduct_KahanAlg( /*v, w*/& v[ 0 ], & w[ 0 ], std::min( v.size(), w.size() ) ) );
		tdur = get_duration( ts );
		cout << "Serial Kahan alg error = \t"	<< std::setprecision( 8 ) << comp_error << "\t\tT [ms] = " << tdur << endl;
		result_errors.push_back( comp_error );
		result_timing.push_back( tdur );
	
		ts = timer::now();
		comp_error = fabs( InnerProduct_KahanAlg_Par( v, w, kChunkSize ) );
		tdur = get_duration( ts );
		cout << "Parallel Kahan alg error = \t"	<< std::setprecision( 8 ) << comp_error << "\t\tT [ms] = " << tdur << endl;
		result_errors.push_back( comp_error );
		result_timing.push_back( tdur );		


		//ts = timer::now();
		//comp_error = fabs( InnerProduct_Sort_KahanAlg( /*v, w*/& v[ 0 ], & w[ 0 ], std::min( v.size(), w.size() ) ) );
		//tdur = get_duration( ts );
		//cout << "Serial Sort-Kahan alg error = \t"	<< std::setprecision( 8 ) << comp_error << "\t\tT [ms] = " << tdur << endl;
		//result_errors.push_back( comp_error );
		//result_timing.push_back( tdur );
		
		//ts = timer::now();
		//comp_error = fabs( InnerProduct_SortKahanAlg_Par( v, w, kChunkSize ) );
		//tdur = get_duration( ts );
		//cout << "Parallel Sort-Kahan alg error = \t"	<< std::setprecision( 8 ) << comp_error << "\t\tT [ms] = " << tdur << endl;
		//result_errors.push_back( comp_error );
		//result_timing.push_back( tdur );



		// -----------------------------------------------
		// Save results
		ofstream res_file( "inner_results.txt", ios::app );
		copy( result_errors.begin(), result_errors.end(), ostream_iterator< double >( res_file, "\t" ) );	res_file << endl;
		copy( result_timing.begin(), result_timing.end(), ostream_iterator< double >( res_file, "\t" ) );	res_file << endl << endl;
		// -----------------------------------------------


		//return make_tuple( result_errors, result_timing );
	}



	// Run the InnerProduct_Test a number of times
	// with different range of the generated data samples.
	void InnerProduct_Test_GeneralExperiment( void )
	{

		const int kElems = /*12*//*40000000*//*1000000*/20000000/*10000*/;

		vector< int >	deltaExpVec { 10, 30, 50, 100/*, 300, 500*/ };


		DVec	v, w;
	
		//const array< const string, 7 > alg_names { "Accum", "Tr-Red", "SortAcc", "Kahan", "SortKahan", "KahanPar", "SortKahanPar" };
		//copy( alg_names.begin(), alg_names.end(), ostream_iterator< string >( cout, "\t" ) );
		//cout << endl;

		for( auto dExp : deltaExpVec )
		{
			cout << "\n\nkMersenneRand_InnerZero" << endl;
			FP_Test_DataSet_Generator::Fill_Numerical_Data_MersenneUniform( v, kElems / 2, pow( 2.0, dExp ) );
			FP_Test_DataSet_Generator::Duplicate( v, + 1.0 );
			FP_Test_DataSet_Generator::Fill_Numerical_Data_MersenneUniform( w, kElems / 2, pow( 2.0, dExp ) );
			FP_Test_DataSet_Generator::Duplicate( w, - 1.0 );

			cout << "ExpDelta = " << dExp << "\tVecElems = " << v.size() << endl;
			InnerProduct_Test( v, w );
		}

	}



}



