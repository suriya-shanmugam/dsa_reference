#include<iostream>
#include<string>
#include<algorithm>

int main(){
	
	std::string first_name = "suriya";
	std::string last_name = "shanmugam";
	
	std::string full_name = first_name + last_name;

        //Unlike languages like python string in c++ are modifiable
	first_name[0] = 'S';
	last_name[0] = 'S';
 	
	// Concatantion creates new string
	std::cout << "Full name is " << full_name << std::endl;
	std::cout << "size of the full name " << full_name.length() << std::endl;

	//string is iterable
	for (char c : full_name){
		std::cout << static_cast<char> (c - 32) << " ";
	}
	std::cout << std::endl;
	
	// index, number of characters from that index
	// Returns the new string
	std::cout << "Last name is " << full_name.substr(6,full_name.length()-6) << std::endl;
	
	// Finding the index of the search text
	size_t t_index = full_name.find("shan");
	// string::npos is a largest constant to convey the index is not found
	std::cout << "what is std::string::npos " << std::string::npos << std::endl;
	
	if (t_index != std::string::npos){
		std::cout << "shan is found at " << t_index << std::endl;
	}
	
	//replace
	//index, noof charaters, characters
	full_name.replace(6, full_name.length()-6, "SHANMUGAM");
	std::cout << "After replace " << full_name << std::endl;

	//Erase
	// index and number of charaters after that
	full_name.erase(6,full_name.length()-6);
	std::cout << "After Erase last_name : " << full_name << std::endl;
	
	//Insert
	// index, append string
	full_name.insert(full_name.length(), " Shanmugam");
	std::cout << "after insert " << full_name << std::endl;

	//string reverse
	reverse(full_name.begin(), full_name.end());
	std::cout << "Reverse full_name " <<  full_name << std::endl;
	
		

	return 0;
}
