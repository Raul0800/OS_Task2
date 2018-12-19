#include <fcntl.h>
#include <stdio.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>
#include "interfaceConn.h"


int main(int argc, char **argv)
{
	char *nameOff = "/c_fname";
	sem_t* semaphore;
	int idFile;
	int pid;
	if ((idFile = shm_open(nameOff,O_CREAT|O_RDWR,0600)) == -1)
		printf("ERROR in shm_open\n");
	ftruncate(idFile,sizeof(sem_t*));
	semaphore = (sem_t*)mmap(NULL,sizeof(*semaphore),PROT_WRITE,MAP_SHARED,idFile,0);
	if (semaphore == MAP_FAILED)
		printf("MAP_FAILED\n");

	if (sem_init(semaphore,1,0) == -1)
		printf("Error in sem_init");

	constructor();
	
	pid = fork();
	if (pid < 0)
		printf("error pid");
	else if (pid > 0){//parent process
		writeToComonSpace();
		sem_post(semaphore);
	}
	else if(pid == 0)//child process
	{
		sem_wait(semaphore);
		readFromCommonSpace();
		sem_post(semaphore);
	}
	sem_close(semaphore);	
	munmap(semaphore,sizeof(semaphore));
	shm_unlink(nameOff);	
	destructor();
  	return 0;
}
