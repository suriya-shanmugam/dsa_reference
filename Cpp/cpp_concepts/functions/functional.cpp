#include<iostream>
#include<functional>
#include<queue>

class one_param_ret_bool {
	
	public :
		bool operator () (int a) const{
			return 1+a;
		}

};

void print2(){
	
	std::cout << "Hello I am regular method definition!!!" << std::endl;

}


int main(){
	
	
	std::function<void()> print = [] (){ std::cout << "Hello I am lambda!!!!"  << std::endl ; } ;
	
	std::function<void()> p2 = print2;

	std::queue<std::function<void()>> tasks;
	tasks.push(print);
	tasks.push(p2);
	

	auto task = tasks.front();
	tasks.pop();
	task();
	
	task = tasks.front();
	tasks.pop();
	task();

	// Functor 
	one_param_ret_bool oprb;

	std::cout << "Functional class " << oprb(1) << std::endl;
	

	return 0;
}
