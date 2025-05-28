#include<iostream>
#include<unordered_map>
#include<string>

int main(){
	
	std::unordered_map<std::string, int> phone_book = {{"Nandha",54321}};
	phone_book.emplace("suriya",987); // create in place - no copies // behaves like insert
	phone_book["tharun"] = 123; // [] updates if key exists else inserts
	phone_book["jesu"] = 568;
	phone_book.insert(std::make_pair("Ram", 189)); // insert only if key doesnot exists
	
	// for finer controls use iterator // can use to delete while iterating
	
	// phone_book.begin() returns the rvalue of the iterator object hence store its copy 
	for (auto it = phone_book.begin(); it != phone_book.end(); it++ ){
		 std::cout << it->first << "'s number is "<< it->second << std::endl;
	}
	
	// to check key exist via iterator
	if(phone_book.find("jesu") != phone_book.end()){
		std::cout << "Jesu number is " << phone_book["jesu"] << std::endl;
	}

	
	std::cout << "To check the key exists boolean " << phone_book.count("jesu") << std::endl ;

	std::cout << "Is empty " << phone_book.empty() << std::endl ;
	
	std::cout << "Phone book size " << phone_book.size() << std::endl;
	
	// return 1 if key found else return 0 
	auto it = phone_book.erase("suriya");
	std::cout << "What does the it holds ??? " << it << std::endl;

	// useful for simple iteration
	for (auto &kv : phone_book){
		kv.second +=1;
		std::cout << kv.first << kv.second << std::endl;
	}
	
	try{
           	// thorw exception if key doesnot exists
		std::cout << phone_book.at("Tharu");
	}catch (const std::exception& e){
	   std::cout << "Exceptions caught : " << e.what() << std::endl;
	}

	return 0;
}

