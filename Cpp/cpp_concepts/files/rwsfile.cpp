#include<iostream>
#include<fstream>
#include<string>


int main(){

	std::ifstream inputFile("test");
	if (!inputFile){
		std::cerr << "Unable to open File" << std::endl;
		return 1;
	}

	std::string line;

	while(std::getline(inputFile,line)){
		std::cout << line << std::endl;
	}
	inputFile.close();


	std::ofstream outputFile("test",std::ios::app);

	if (!outputFile){
		std::cerr << "Unable to open File" << std::endl;
		return 1;
	}

 	outputFile << "I am writing to this file" << std:: endl;

	outputFile.close();


	return 0;

}


