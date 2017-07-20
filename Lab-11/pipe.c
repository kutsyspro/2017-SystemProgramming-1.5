#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {

	int data_processed;

	int file_pipes[2];

	char some_data[20] = "2014136118 pid:";
	const char str[]="start";
	char insert[6]={0};
	char buffer[BUFSIZ + 1];
	char temp[10]={0};
	pid_t fork_result;
	memset(buffer, 0, sizeof(buffer));

	gets(insert);

	if(strcmp(insert,str)==0)
	{
		if (pipe(file_pipes) == 0) {
			fork_result = fork();
			if (fork_result == -1) {
				fprintf(stderr, "Fork failure"); exit(EXIT_FAILURE);
			}

			if (fork_result == 0) { //comsumer

				data_processed = read(file_pipes[0], buffer, BUFSIZ);

				printf(" Read %d bytes: %s\n", data_processed, buffer);

				exit(EXIT_SUCCESS);

			} else { //producer
				sprintf(temp,"%d",getpid());
				strcat(some_data, temp);
				data_processed = write(file_pipes[1], some_data,strlen(some_data));

				printf("Wrote %d bytes\n", data_processed);
			}
		}

		exit(EXIT_SUCCESS);
	}
	else{
		return 0;
	}
}
