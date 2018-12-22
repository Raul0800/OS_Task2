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
int sVal[1];
char *nameOff = "/c_fname";
sem_t* semaphore;
int idFile;
int pid;
static int i = 0;
static int count = 0;
printf ("Введите количество итераций:\n");
scanf ("%d", &count);

constructor();

pid = fork();	

if ((idFile = shm_open(nameOff,O_CREAT|O_RDWR,0600)) == -1)
		printf("ERROR in shm_open\n");
	ftruncate(idFile,sizeof(sem_t*));
	semaphore = (sem_t*)mmap(NULL,sizeof(*semaphore),PROT_WRITE,MAP_SHARED,idFile,0);
	if (semaphore == MAP_FAILED)
		printf("MAP_FAILED\n");
	if (sem_init(semaphore,1,0) == -1)
		printf("Error in sem_init");
	sem_getvalue(semaphore,sVal);


sem_post(semaphore);
while (i <= count){
	if (pid < 0)
		printf("error pid");	
	if(pid == 0)//child process
	{
		sem_wait(semaphore);		
		readFromCommonSpace();	
		if (i < count)		
			printListOfQuestions();		
			
	}
	
	if (pid > 0)//parent process
	{	
		sem_wait(semaphore);
		if (i < count)
			writeToComonSpace();
			
		sem_post(semaphore);
		sem_post(semaphore);		
	}
	i++;
}
sem_close(semaphore);	
munmap(semaphore,sizeof(semaphore));
shm_unlink(nameOff);
	destructor();
		
  	return 0;
}
