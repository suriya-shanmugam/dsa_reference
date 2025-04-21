#include<iostream>
#include<vector>
#include<algorithm>

int main(){
	
	
	std::vector<int> list(5);
	for (int i = 0 ; i < 5 ; i++){
		list[i] = i ;
	}
	list.push_back(5);
	std::cout << "---At 0 ----" << list[0] << std::endl;
	std::cout << "---At 1 ----" << list.at(1) << std::endl;
	std::cout << "---List front ---- " <<  list.front() << std::endl;
	std::cout << "---List back ---- "<< list.back() << std::endl;
	std::cout << " List Size ---" << list.size() << std::endl;
	
	list.insert(list.begin(),20);
	//list.erase(list.end());

	
	std::cout << "Actual list " << std::endl;
	
	
	std::vector<int> copylist(list);
	for (const auto &ele : copylist){
		std::cout << ele << " ";
	}
	
	std::cout << std::endl << " ----Reverse print list ------- " << std::endl ;
	for (auto it = copylist.rbegin() ; it != copylist.rend(); it++){
		std::cout << *it << " ";
	}
        
	std::cout << std::endl << " ---- Descending sorted list ------- " << std::endl ;

	std::sort(copylist.begin(), copylist.end(), [](int a, int b){
		return a > b;	
	});

	for (const auto &num : copylist){
		std::cout << num << " " ;
	}
	
	std::sort(copylist.begin(), copylist.end());

	std::cout << std::endl << "Asending list " << std::endl;
	for (const auto &num : copylist ){
		std::cout << num << " ";
	}
	std::cout << std::endl;

	
	auto it = std::find(list.begin(),list.end(),4);

	if ( it != list.end()){
		std::cout << "element found" << std::endl;
		it++;
		std::cout << " Next Element "<< *it << std::endl;
		
		std::cout << "Accesing beyond the limit " << std::endl; 
		it++;
		std::cout << " Next Element "<< *it << std::endl;
         	it++;
		std::cout << " Next Element "<< *it << std::endl;

	}




	return 0;
}
