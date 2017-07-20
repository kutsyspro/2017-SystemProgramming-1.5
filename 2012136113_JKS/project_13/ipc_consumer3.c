#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>



#define MYMSG_KEY 12188
#define MYMSG_SIZE 64
#define PRODUCER_PUSHED 1
#define CONSUMER_PUSHED 2



typedef struct _MyMsg {

	long msgType;

	char msgBody[MYMSG_SIZE];

} MyMsg;



int main(int argc, char* argv[]) {

	const char* studentName = "Jeong Ho Yeob";

	char myPid[16];	

	sprintf(myPid, "%d", getpid());

	char producerPid[MYMSG_SIZE], studentId[MYMSG_SIZE];

	// create message queue using msgget() function
	// IPC_CREATE is option, then exist queue depending key return queue identifier, not exist creat
	// return -1 is failed create queue

	int msgKey = msgget(MYMSG_KEY, 0666 | IPC_CREAT);

	if(msgKey==-1) {

		perror("msgget failed\n");

		exit(EXIT_FAILURE);

	}

	MyMsg msgBuf; 

	while(1) {

		// msgrcv function is receive data 
		// 4th variable is option, read message queue data
		// 0 is fist data, + is producer_pushed type's first data
		// - is abs(-) small data_type's data
		// 5th variable is read option, not using then 0

		msgrcv(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long),PRODUCER_PUSHED, 0);

		strcpy(producerPid, msgBuf.msgBody);

		msgrcv(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long),PRODUCER_PUSHED, 0);

		strcpy(studentId, msgBuf.msgBody);

		printf("producer_pid:%s, student_id:%s\n",producerPid, studentId);



		// msgsnd function send data in message queue

		// retun 0 then success

		msgBuf.msgType = CONSUMER_PUSHED;

		strcpy(msgBuf.msgBody, myPid);

		msgsnd(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long), 0);

		msgBuf.msgType = CONSUMER_PUSHED;

		strcpy(msgBuf.msgBody, studentName);

		msgsnd(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long), 0);

	}

	exit(EXIT_FAILURE);

}
