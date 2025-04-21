#include<iostream>

class Dev{
	public :
		void write_code(){
			std::cout << "Write code" << std::endl;
		}
	protected :
		void write_code_protected(){
			std::cout << "Write code protected" << std::endl;
		}
};

class Ops{
	public :
		void deploy(){
			std::cout << "Deploy code" << std::endl;
		}
};

class DevOps :  public Dev, public Ops{
	
	public :
		void doBoth(){
			deploy();
			write_code();
			write_code_protected();
		}
};


class JDevOps: virtual public DevOps {

	public :
		void doSomething(){
			write_code();
		}

		void doBoth(){
			std::cout << "Child do both" << std::endl;
			DevOps::doBoth();
		}

};


int main(){
	
	
	JDevOps instance;
	//instance.doSomething();
	instance.doBoth();


	DevOps *ins2 = new DevOps(); 
	ins2->write_code();

	return 0;
}
