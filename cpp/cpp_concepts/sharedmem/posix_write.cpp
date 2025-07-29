#include<iostream>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<cstring>

int main(){
	
	const char* name = "/my_shm";
	const int SIZE = 4096;

	int shm_fd = shm_open(name,O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);

	void* ptr = mmap(0,SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	const char* msg = "Hello from writer";
	memcpy(ptr, msg, strlen(msg)+1);

	std::cout << "Message written to shared memory" << msg << std::endl;

	munmap(ptr,SIZE);
	close(shm_fd);

	return 0;
}


