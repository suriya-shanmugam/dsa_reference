#include<vector>
#include<iostream>

using namespace std;

int main(){
	
	// Basic
	vector<int> num0;
	vector<int> num1(2); // Number of elements // int default value - 0
	vector<int> num2(3,1);  // Number of elements and its number
	
	// initializer list
	vector<int> num4 = {1,2,3,4}; 
	vector<int> num5 {5,6,7,8};
	
	//from other containers
	
	int arr[] = {10,11,12,13};
	vector<int> num6 (arr, arr+4);

	vector<int> source = {15,16,17};
	vector<int> num7(source.begin(), source.end());

	for (const auto num : num7){
		cout << num << "\t" ;
	}
	cout << endl;


	vector<vector<int>> numbers;
	numbers.push_back({100,200,300,400,500});
	for (const auto num : numbers[0]){
		cout << num << "\t";
	}
	cout << endl;
}
