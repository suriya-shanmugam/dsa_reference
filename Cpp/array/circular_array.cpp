#include<iostream>
#include<vector>
using namespace std;
	
int main(){	
	vector<int> code = {10,5,7,7,3,2,10,3,6,9,1,6};
	int k = -4;
	vector<int> result(code.size(),0);
        
	// Counter_intutive but works
	for (int index = 0 ; index < code.size(); index++){
            int counter = k;
            int sum = 0;
            while(counter != 0){
		
		// Carefull with the arithmetic operation on size() return by containers as it *unsigned*
		int size = static_cast<int>(code.size());
		int target_index = (((index + counter) % size) + size) % size;

                //cout << target_index << "\t";
                sum += code[target_index];
                if(k > 0){
                    counter--;
                }else{
                    counter++;
                }          
            }
            //cout << sum << "\t";
            result[index] = sum;
        }
        
	//To-Do solve with better intuitive / efficient approach


	for (const int &num : result){
		std::cout << num << "\t";
	}
	return 0;
}	
