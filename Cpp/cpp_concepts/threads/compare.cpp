#include<iostream>
#include<vector>
#include<chrono>
#include<omp.h>

int main(){

	omp_set_num_threads(12);
	int MAX = 100000000;
	
	std::vector<int> numbers(MAX);

	std::vector<int> results;

	std::vector<int> results1;

	for (int i=0 ; i < MAX ; i++){
		numbers[i] = i ;
	}
	
	auto start = std::chrono::high_resolution_clock::now();
	
	#pragma omp parallel 
	{
		
		std::vector<int> thread_local_results;

		#pragma omp for schedule(static)
		for (int i = 0 ; i < MAX; i++ ){
			thread_local_results.push_back(numbers[i]);
		}

                #pragma omp critical
		results.insert(results.begin(),thread_local_results.begin(),thread_local_results.end());
	}        
	
	/*for (int&num :numbers ){
		results.push_back(num);
	}*/

	
	std::cout << results.size() <<std::endl;
        auto end = std::chrono::high_resolution_clock::now();
        
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

	std::cout <<"Duration - " << duration.count() << std::endl ;
	
	       

       start = std::chrono::high_resolution_clock::now();
	for (auto&num :numbers ){
		results1.push_back(num);
	}
       

       end = std::chrono::high_resolution_clock::now();
        
       duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

	std::cout <<"Duration - " << duration.count() << std::endl ;
	
	

	return 0;
}

