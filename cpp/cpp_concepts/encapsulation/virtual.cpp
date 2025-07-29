#include<iostream>



class Product {
	
	
	public :
		Product(int n){
			
			id = n;
			std::cout << "Product with Id - " << id << "is created" << std::endl;
		}
		virtual int getId() const {
			return 1000 + id;
		};
	private :
		int id;
		
};


class ElectricalProduct : public Product {
	
	public :
		
		ElectricalProduct(int n): Product(n){
		
		}
		int getId() const override {
			return 7 ;
		}

};

/*class EPC : public ElectricalProduct {
	
	public :
		int getId(){
			return ElectricalProduct::getId();
		}

};*/

int main(){
	
	Product p(1) ;
	std::cout << p.getId() << std::endl;

	

	ElectricalProduct ep(2);
	
	Product *p_ptr = &ep;
	
	std::cout << "Electrical Product "<< p_ptr->getId() << std::endl;
	
	/* EPC epc;
        std::cout << "Electrical Product "<< epc.getId() << std::endl; */

	return 0;
}
