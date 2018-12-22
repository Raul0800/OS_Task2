#include <semaphore.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include "interfaceConn.h"
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>

static const char nameOfFile[]="nameOffile";
static int fd_fifo;

void printListOfQuestions()
{
	printf("выберете возможный вопрос:\n");
	printf(question);
	printf("НЕОБХОДИМО ВВЕСТИ НОМЕР ВОПРОСА\n");
}
void constructor(void)
{
	if (mkfifo(nameOfFile, S_IRWXU) == -1)
		printf("\nERROR IN MKFIFO\n");
	fd_fifo = open(nameOfFile,O_RDWR|O_NONBLOCK);
	if (fd_fifo < 0)
		printf("ERROR OPEN cWrite\n");
}
void writeToComonSpace(void)
{
	int nQ; 
	scanf("%d",&nQ);
	write(fd_fifo,&nQ,sizeof(int));
}

void readFromCommonSpace(void)
{
	int q;
	read(fd_fifo,&q,sizeof(int));
	if (q == 1)
		printf(q1);
	if (q == 2)
		printf(q2);
	if (q == 3)
		printf(q3);
	if (q == 4)
		printf(q4);
	if (q == 5)
		printf(q5);
	if (q == 6)
		printf(q6);
	if (q == 7)
		printf(q7);
	if (q == 8)
		printf(q8);
	if (q == 9)
		printf(q9);
}

void destructor(void)
{	
	unlink(nameOfFile);
	close(fd_fifo);
}

