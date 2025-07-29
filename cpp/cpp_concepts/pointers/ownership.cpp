#include<iostream>
#include<memory>

void deletemem(const int *ptr){
	std::cout << "in delete mem " << *ptr << std::endl;
	delete ptr;
}

std::shared_ptr<int> int_s_ptr = std::make_shared<int>(20);

std::shared_ptr<int> get_ref_ptr(){
	
	return int_s_ptr;
}

std::unique_ptr<int> int_u_ptr = std::make_unique<int>(40);
/* copy is prevented in unique_ptr */
/*std::unique_ptr<int> get_unique_ptr () {
	return int_u_ptr;
}*/


int main(){
	
	/* problems with ownership in terms of raw pointers */
	const int *ptr = nullptr; 
	{
		ptr = new int(10);
		std::cout << "With in scope " << *ptr << std::endl;
		deletemem(ptr);
		
	}
	std::cout << "Outside in scope " << *ptr << std::endl;
        
	
	/* How shared_ptr helps in solving the above issue */
	std::shared_ptr<int> newref1 = get_ref_ptr();

	{
		std::shared_ptr<int> newref2 = get_ref_ptr();
		// Defeat the whole point of shared_ptr
		// delete newref2.get();
	}	

	std::cout << "Shared Pointer value " << *newref1 << std::endl;
	
	
	
	std::shared_ptr<int> newref3 = nullptr;
	{
		{
			
			std::shared_ptr<int> newref4 = std::make_shared<int>(300);
			newref3 = newref4; 
		}
	}
	
	// Holds the memory though the life of all the pointer scope 	

	std::cout << "Shared Pointer value " << *newref3.get() << std::endl;


	/* How unique_ptr restricts copy */

	//std::unique_ptr<int> newu_ref1 = int_u_ptr;	

	std::cout << "Unique Pointer value " << *int_u_ptr << std::endl;

}
