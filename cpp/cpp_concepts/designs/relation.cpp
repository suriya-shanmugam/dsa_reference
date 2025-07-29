#include<iostream>


class Element {
	public:
		Element(int n1, int n2):x(n1),y(n2){

		}

		int getX(){
			return x;
		}
		int getY(){
			return y;
		}
	        virtual void print(){
			std::cout << "X is " << x << "Y is "<< y << std::endl;
		}
		
			
	private:
		int x;
		int y;
		virtual int privateoverride() = 0;
};

class WindowElement : public Element {
		
	public :
		
		WindowElement(int n1, int n2):Element(n1,n2){}

		void print () override {
			std::cout << "I am window element" << std::endl;

		}
	
	private:
		int privateoverride() override{
			return 1;
		}

};

int main(){
	
	Element *ele = new WindowElement(1,2);
	ele->print();
	
	std::cout << "Get X "<< ele->getX() << std::endl;
	
	//Throws Error
	//std::cout << "Get X "<<ele->privateoverride() << std::endl;
	return 0;
}
