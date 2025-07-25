#include<iostream>
#include<vector>

using namespace std;

void swap(int left, int right, vector<int>& nums){
        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;
}
    
int partition(int start, int end, vector<int>& nums){
	int pivot = nums[end];
	int left = start-1;

	for (int right = start ; right < end ; right++){
	    if(nums[right] < pivot){
		left++;
		swap(left, right, nums);
	    }
	}
	//place pivot at right spot
	swap(left+1, end, nums);
	return left+1;
}

void quick_sort(int start, int end, vector<int>& nums){
	if (start < end){
	    int pivot = partition(start, end, nums);
	    quick_sort(start, pivot-1, nums);
	    quick_sort(pivot+1, end, nums);
	}
}

int main(){
	
	vector<int> nums = {10,9,1,1,1,2,3,1};
	quick_sort(0, nums.size()-1, nums);

	for (const int& num : nums){
		cout << num << "\t";
	}
	return 0;
}
