#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

#define MYSHM_KEY 11423
#define MYSHM_SIZE 64
#define ANYONE_WRITED 0
#define PRODUCER_WRITED 1
#define CONSUMER_WRITED 2

char* shm = NULL;

int main(int argc, char* argv[]) {

	const char* studentId = "2012136113";

	char myPid[16];	

	sprintf(myPid, "%d", getpid());

	char consumerPid[MYSHM_SIZE], studentName[MYSHM_SIZE];

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
	// 2nd variable is adrress, nomarlly NULL
	// 3rd variable is oprtion , SHM_RDONLY is  read only
	// SHM_RND is 2nd variable is not NULL, set shmaddr is memory page end

	shm = shmat(shmid, NULL, 0);

	if(shm == (char*)(-1)) {

		perror("shmat failed\n");

		exit(EXIT_FAILURE);

	}

	char cmdBuf[1024];

	while(1) {

		scanf("%s", cmdBuf);

		// input 'start' program start

		if(strcmp(cmdBuf, "start")==0) {

			// write ipc_producer2 pid, student id in shared memory

			strcpy(shm+1, myPid);

			shm[0] = PRODUCER_WRITED;

			while(shm[0]!=ANYONE_WRITED)

				sleep(0);

			strcpy(shm+1, studentId);

			shm[0] = PRODUCER_WRITED;

			// read ipc_consumer2 pid, student name in shared memor

			while(shm[0]!=CONSUMER_WRITED)

				sleep(0);

			strncpy(consumerPid, shm+1, MYSHM_SIZE-1);

			shm[0] = ANYONE_WRITED;

			while(shm[0]!=CONSUMER_WRITED)

				sleep(0);

			strncpy(studentName, shm+1, MYSHM_SIZE-1);

			shm[0] = ANYONE_WRITED;

			printf("producer2_pid:%s, consumer2_pid:%s, student_id:%s, student_name:%s\n", myPid, consumerPid, studentId, studentName);

		}

		if(strcmp(cmdBuf, "exit")==0) {

			printf("exit program...\n");
			exit(EXIT_SUCCESS);

		}

	}

	exit(EXIT_FAILURE);

}
