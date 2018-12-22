#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdlib.h>
#include "interfaceConn.h"

static const char nameOfFile[]="/qm";
static mqd_t mq;
void constructor(void){ 
	struct mq_attr attr;
	attr.mq_maxmsg = 1;
	attr.mq_msgsize = sizeof(char);
	mq = mq_open(nameOfFile,O_CREAT|O_RDWR|O_NONBLOCK,S_IRWXU,&attr);
	if (mq == -1){
		printf("ERROR mq\n");	
	}
}
void printListOfQuestions()
{
	printf("выберете возможный вопрос:\n");
	printf(question);
	printf("НЕОБХОДИМО ВВЕСТИ ТОЛЬКО НОМЕР ВОПРОСА\n");
}

void writeToComonSpace(void){
	static char buf[1];
	printListOfQuestions();
	scanf("%s",buf);
	if (mq_send(mq, buf, 1,0) == -1){
		printf("ERROR mq_send\n");
	}
}

void readFromCommonSpace(void){
	char ans[1];
	if (mq_receive(mq,ans,sizeof(char),NULL) == -1){
		printf("ERROR mq_receive\n");
	}
	 
	if (ans[0] == '1')
		printf(q1);
	if (ans[0] == '2')
		printf(q2);
	if (ans[0] == '3')
		printf(q3);
	if (ans[0] == '4')
		printf(q4);
	if (ans[0] == '5')
		printf(q5);
	if (ans[0] == '6')
		printf(q6);
	if (ans[0] == '7')
		printf(q7);
	if (ans[0] == '8')
		printf(q8);
	if (ans[0] == '9')
		printf(q9);
	
}

void destructor(void){
mq_close(mq);
mq_unlink(nameOfFile);
}

