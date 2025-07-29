#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


#define BUF_SIZE 1024
#define SHM_KEY 0x1234

struct shmseg {
	int cnt;
	int complete;
	char buf[BUF_SIZE];
};

int main(){
	int shmid;
	struct shmseg *shmp;
	shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644 | IPC_CREAT);
	
	shmp = (struct shmseg *)shmat(shmid, NULL, 0);

	while( shmp->complete != 1){
		
		
		std::cout << "Segment contains" << shmp->buf << std::endl;
		std::cout << "Read" << shmp->cnt << "\n";
		sleep(2);
	}
	

	std::cout << "Read Done" << std::endl ;

	if (shmdt(shmp)== -1){
		perror("shmdt");
		return 1;
	}
	return 0 ;
}
