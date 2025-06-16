#include<iostream>
#include<vector>
#include<unordered_map>

const int invalid_number =  -1000000001;

int main(){
	
	std::vector<int> numbers = {1,2,5,4,5,2,4,4,4,5,5,5,5,1,1,1,1,1,1,1,1,1};
	std::unordered_map<int,int> frequencies;
	int max_freq = 0;
	int frequent_num = invalid_number ; // This has to be constant
	for (const auto& num : numbers ){
		frequencies[num]++;
		if (max_freq < frequencies[num]){
			max_freq = frequencies[num];
			frequent_num = num;
		}
	}
	
	std::cout << "Max freq " << max_freq << "\nMax repeted number " << frequent_num << std::endl;
	
	max_freq = 0;
	frequent_num = invalid_number; 
	for (auto it = frequencies.begin(); it != frequencies.end(); it++){
		if (max_freq < it-> second){
			max_freq = it->second;
			frequent_num = it->first;
		}
	}
	std::cout << "Max freq " << max_freq << "\nMax repeted number " << frequent_num << std::endl;
	return 0;
}
