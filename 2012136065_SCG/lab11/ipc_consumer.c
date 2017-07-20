#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

#define PROD "/tmp/prod"
#define CONS "/tmp/cons"

int main(void){
	int res, pipe_id;
	char pid[10], id[20], name[100];
	char p_pid[10], p_id[20];
	char s_msg[100];

	sprintf(pid, "%d", getpid());
	sprintf(id, "%s", "2012136065");
	sprintf(name, "%s", "consumer");

	if(access(CONS, F_OK) == -1){
		res = mkfifo(CONS, 0777);
		if(res != 0) exit(EXIT_FAILURE);
	}
	printf("Process %d opening FIFO\n", getpid());

	while(1){
		pipe_id = open(PROD, O_RDONLY);
		res = read(pipe_id, p_pid, 10);
		if(res <= 0){
			printf("READ ERROR!\n");
		}
		res = read(pipe_id, p_id, 20);
		if(res <= 0){
			printf("READ ERROR!\n");
		}

		close(pipe_id);

		printf("Producer id = %s, Producer pid = %s\n",
			p_id, p_pid);

		pipe_id = open(CONS, O_WRONLY);
		res = write(pipe_id, pid, 10);
		if(res <= 0){
			printf("WRITE ERROR!\n");
		}
		res = write(pipe_id, id, 20);
		if(res <= 0){
			printf("WRITE ERROR!\n");
		}
		res = write(pipe_id, name, 100);
		if(res <= 0){
			printf("WRITE ERROR!\n");
		}

		close(pipe_id);
	}
	exit(EXIT_SUCCESS);
}
