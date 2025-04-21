#include<iostream>

int print(int val1, int val2){

	return val1 + val2;
}

void getPrint( int (*print) (int,int), int v1, int v2){
	std::cout << print(v1,v2) << std::endl;
}


int main(){
	
	
	getPrint(print,3,5);
	return 0;
}
