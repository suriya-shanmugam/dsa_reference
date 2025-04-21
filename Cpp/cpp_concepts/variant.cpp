#include<iostream>
#include<variant>

int main(){
	
	std::variant<int, float> v1 = 72;
	std::cout << "v1 value is " << std::get<int>(v1) << std::endl;
	
	std::visit([](auto&& value){
		std::cout << "v1 value in callable " << value << std::endl;
	},v1);
	
	int a = 20;
	decltype(a)& b = a;

	std::cout << "decltype test " << b << std::endl;
	
	// type trait check using std::is_same_v
	using T = std::decay_t<decltype(b)>;
	std::cout << "is same test " << std::is_same_v<T,int> << std::endl;
	
	return 0;
}

