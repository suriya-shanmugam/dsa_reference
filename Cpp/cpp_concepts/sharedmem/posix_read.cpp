#include<iostream>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>

int main(){
	
	const char* name = "/my_shm";
	const int SIZE = 4096;

	int shm_fd = shm_open(name,O_RDONLY, 0666);
	void *ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

	std::cout << "Message read from memory " << (char*)ptr << std::endl;

	munmap(ptr, SIZE);
	close(shm_fd);
	shm_unlink(name);

	return 0;
	

}
