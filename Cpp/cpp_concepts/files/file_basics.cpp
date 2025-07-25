#include<iostream>
#include<fstream>

using namespace std;
// ofstream, ifstream is also a object of ostream and istream 

int main(){
	
	// Example of writing to the file
	ofstream myfile;
	myfile.open("Example.txt");
	
	if (myfile.is_open()){
		myfile << "Writing to this file....\n";
		myfile << "This is Line 1" << std::endl;
		myfile << "This is line 2" << std::endl;
		myfile.close();
	}else {
		cout << "Something went wrong on wrinting!!!!" << endl;
	}

	// Example of Reading from the file // Similar to cin 
	string line;
	ifstream rfile("Example.txt");
	if(rfile.is_open()){
		while(getline(rfile, line)){
			cout << line << endl;
		}
		rfile.close();
	}else {
		cout << "Something went wrong on reading!!!!" << endl;
	}
	
	//tellg() - ofstream position 
	//tellp() - ifstream position
	//seekg() - ofstream position shift with offset
	//seekp() - ofstream position shift with offset
	//streampos - type of position
	
	// Example to find file size
	streampos begin, end;
	ifstream file3("Example.txt");
	begin = file3.tellg();
	file3.seekg(0, ios::end);
	end = file3.tellg();
	file3.close();
	cout << "size of the file is " << (end-begin) << " bytes " << std::endl;
	return 0;
}
