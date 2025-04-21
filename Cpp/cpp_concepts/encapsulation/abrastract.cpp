#include<iostream>

class Product{
	public:
		virtual int getId() const  = 0;
};


class ElectricProduct : public Product {
	public :
		int getId() const override {
			return 1;
		}

		~ElectricProduct(){
			std::cout << "Electric Product Destructor" << std::endl;
		}

};


int main(){
	
	ElectricProduct ep;
	std::cout << ep.getId() << std::endl;
	return 0;
}
