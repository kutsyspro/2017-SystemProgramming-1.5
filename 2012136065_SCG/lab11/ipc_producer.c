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
	char pid[10], id[20];
	char c_pid[10], c_id[20], c_name[100];
	char s_msg[100];

	sprintf(pid, "%d", getpid());
	sprintf(id, "%s", "2012136065");

	if(access(PROD, F_OK) == -1){
		res = mkfifo(PROD, 0777);
		if(res != 0) exit(EXIT_FAILURE);
	}
	printf("Process %d opening FIFO\n", getpid());

	while(1){
		printf("Please type \"start\" for start : ");
		scanf("%s", s_msg);

		if(strcmp(s_msg, "start") == 0){
			pipe_id = open(PROD, O_WRONLY);
			res = write(pipe_id, pid, 10);
			if(res <= 0){
				printf("WRITE ERROR!\n");
			}
			res = write(pipe_id, id, 20);
			if(res <= 0){
				printf("WRITE ERROE!\n");
			}

			close(pipe_id);

			pipe_id = open(CONS, O_RDONLY);
			res = read(pipe_id, c_pid, 10);
			if(res <= 0){
				printf("READ ERROR!\n");
			}
			res = read(pipe_id, c_id, 20);
			if(res <= 0){
				printf("READ ERROR!\n");
			}
			res = read(pipe_id, c_name, 100);
			if(res <= 0){
				printf("READ ERROR!\n");
			}

			close(pipe_id);

			printf("My pid = %s\nConsumer pid = %s, Consumer Name = %s, Consumer id = %s\n", pid, c_pid, c_name, c_id);
		}
	}
	exit(EXIT_SUCCESS);
}
