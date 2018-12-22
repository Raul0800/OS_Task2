#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include "interfaceConn.h"

static int* sharedMemoryForQuestion;

void printListOfQuestions()
{
	printf("выберете возможный вопрос:\n");
	printf(question);
	printf("НЕОБХОДИМО ВВЕСТИ НОМЕР ВОПРОСА\n");
}

void constructor(void){
	sharedMemoryForQuestion = (int*)mmap(0,sizeof(*sharedMemoryForQuestion),PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);
}

void writeToComonSpace(void){
	scanf("%d",sharedMemoryForQuestion);
}

void readFromCommonSpace(void){
	int q = *sharedMemoryForQuestion; 
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

void destructor(void){
	munmap(sharedMemoryForQuestion,1);
}

