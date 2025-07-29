int calculate_sum(int* arr, int size){
	int sum = 0;
	while(size > 0){
		//std::cout << "Value at arr" <<  *arr << std::endl;
		sum += *arr;
                //std::cout << "Sum is " <<  sum  << std::endl;
		++arr;
		--size;	
	}
	return sum;
}
