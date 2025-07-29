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

int fill_buffer(char *bufptr, int size);

int main(){
	
	int shmid, numtimes;
	struct shmseg *shmp;
	char *bufptr;
	int available_space;

	shmid = shmget(SHM_KEY,sizeof(struct shmseg), 0644|IPC_CREAT);

	if (shmid == -1){
		perror("Shared memory");
		return 1;
	}

	shmp = (struct shmseg *) shmat(shmid, NULL, 0);

	if (shmp == (void *) -1){
		perror("Shared Memory Attach");
		return 1;
	}

	bufptr = shmp->buf;
	available_space = BUF_SIZE;

	for (numtimes = 0; numtimes < 5 ; numtimes++ ){
		shmp->cnt = fill_buffer(bufptr, available_space);
		shmp->complete = 0 ;
		printf("Writing %d bytes into shmem\n", shmp->cnt);
		bufptr = shmp->buf;
		available_space = BUF_SIZE;
		sleep(3);
	}

	std::cout << "Writing done " << numtimes  << "times \n" ;
	
	shmp->complete = 1 ;

	if (shmdt(shmp) == -1){
		perror("Detach");
		return 1 ;
	}

	if (shmctl(shmid, IPC_RMID, 0 ) == -1 ){
		perror("shmcontrol");
		return 1 ;
	}

	std::cout << "Writing Done!!!" << std::endl;
	return 0;

}

int fill_buffer(char *bufptr, int size){
	
	static char ch = 'A';
	int filled_count;

	memset(bufptr, ch , size-1);
	
	bufptr[size-1] = '\0';
	
	filled_count = strlen(bufptr);
	ch++;
	return filled_count;

}
