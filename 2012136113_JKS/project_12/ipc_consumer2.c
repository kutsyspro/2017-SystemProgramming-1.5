#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define MYSHM_KEY 11423

#define MYSHM_SIZE 64
#define ANYONE_WRITED 0
#define PRODUCER_WRITED 1
#define CONSUMER_WRITED 2

char* shm = NULL;

void shm_free(int sig) {

	if(shm!=NULL)

		// shmdt fuction is deattach shared memory in process
		shmdt(shm);

}

int main(int argc, char* argv[]) {

	const char* studentName = "Jeong kyeong seok";

	char myPid[16];	

	sprintf(myPid, "%d", getpid());

	char producerPid[MYSHM_SIZE], studentId[MYSHM_SIZE];

	// shmget function is create shared memory

	// 0666 | IPC_CREATE is option, No shared memory depending on key create,

	// but exist then ignore and set file acess mode

	// return != -1 is success , -1 is fail

	int shmid = shmget(MYSHM_KEY, MYSHM_SIZE, 0666 | IPC_CREAT);

	if(shmid==-1) {

		perror("shmget failed\n");

		exit(EXIT_FAILURE);

	}

	// shmat function is attach shared memory in process

	shm = shmat(shmid, NULL, 0);

	if(shm == (char*)(-1)) {

		perror("shmat failed\n");

		exit(EXIT_FAILURE);

	}

	(void) signal(SIGTERM, shm_free); // reset(?)
	(void) signal(SIGKILL, shm_free); 
	(void) signal(SIGSTOP, shm_free); 

	while(1) {

		// read ipc_producer2 pid, student id in shared memory

		while(shm[0]!=PRODUCER_WRITED)

			sleep(0);

		strncpy(producerPid, shm+1, MYSHM_SIZE-1);

		shm[0] = ANYONE_WRITED;

		while(shm[0]!=PRODUCER_WRITED)

			sleep(0);

		strncpy(studentId, shm+1, MYSHM_SIZE-1);

		shm[0] = ANYONE_WRITED;

		printf("producer_pid:%s, student_id:%s\n",

				producerPid, studentId);



		// write ipc_consumer2 pid, student name in shared memory

		strcpy(shm+1, myPid);

		shm[0] = CONSUMER_WRITED;

		while(shm[0]!=ANYONE_WRITED)

			sleep(0);

		strcpy(shm+1, studentName);

		shm[0] = CONSUMER_WRITED;

	}

	exit(EXIT_FAILURE);

}


