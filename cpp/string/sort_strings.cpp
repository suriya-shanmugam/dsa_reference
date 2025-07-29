#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;
int main(){
	
	vector<string> strs = {"suriya","mohan","Amannn"};
	sort(strs.begin(), strs.end());

	for(auto const str : strs){
		cout << str << "\t";
	}

	cout << "what is back ????" << strs.back() << std::endl;

}
