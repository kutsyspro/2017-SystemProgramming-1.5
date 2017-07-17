#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>

#define PRODUCER_FIFO "/tmp/prdc_fifo"
#define CONSUMER_FIFO "/tmp/csm_fifo"

int main(int argc, char* argv[]) {

	const char studentId[PIPE_BUF+1] = "2012136113";
	char myPid[PIPE_BUF+1], consumerPid[PIPE_BUF+1], studentName[PIPE_BUF+1];	

	sprintf(myPid, "%d", getpid());

	if(access(PRODUCER_FIFO, F_OK)==-1) {

		// mkfifo function make fifo and return 0 then sucess
		// 0777 is file acess mode rwx/rwx/rwx
		int res = mkfifo(PRODUCER_FIFO, 0777);
		if(res!=0) {

			printf("make fifo failed. exit program...\n");
			exit(EXIT_FAILURE);
		}
	}

	char cmdBuf[1024]; //comand
	int pipeId = -1;

	while(1) {

		scanf("%s", cmdBuf);
		// input 'start' then program start
		if(strcmp(cmdBuf, "start")==0) {

			// open producer fifo for write

			pipeId = open(PRODUCER_FIFO, O_WRONLY);

			if(pipeId==-1) {
				printf("producer fifo open failed.\n");

				continue;
			}

			// write ipc_producer pid, student number in pipe buffer and close pipe

			write(pipeId, myPid, PIPE_BUF);

			write(pipeId, studentId, PIPE_BUF);

			close(pipeId);


			// open consumer fifo for read

			pipeId = open(CONSUMER_FIFO, O_RDONLY);

			if(pipeId==-1) {

				printf("consumer fifo open failed.\n");

				continue;

			}

			// read ipc_consumer pid, student name in pipe buffer and close pipe

			read(pipeId, consumerPid, PIPE_BUF);

			read(pipeId, studentName, PIPE_BUF);

			close(pipeId);

			// print read data

			printf("producer_pid:%s, consumer_pid:%s, student_id:%s, student_name:%s\n", myPid, consumerPid, studentId, studentName);

		}

		if(strcmp(cmdBuf, "exit")==0) {

			printf("exit program...\n");

			exit(EXIT_SUCCESS);

		}

	}

	exit(EXIT_FAILURE);

}


