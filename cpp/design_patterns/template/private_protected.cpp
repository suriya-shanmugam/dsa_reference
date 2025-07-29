#include<iostream>


// Template pattern uses inheritance to defer the behaviour by maintaining the fixed flow

class FrameWork{
	
public:
	void run(){
		init();
		execute();
		clean_up();

	}

protected :   // Procted to convey its intention (overiden by subclasses)
	void init(){
		std::cout << "Initializing....";
	} 

	void clean_up(){
		std::cout << "Cleaning up...";
	}		

	virtual void execute() = 0;
	
};

class ClientFrameWork : public FrameWork {
	
	void execute() override  {
		std::cout << "Executing...";
	}

};


int main(){
	
	FrameWork* client_framework = new ClientFrameWork();
	client_framework->run();
	return 0;
}
