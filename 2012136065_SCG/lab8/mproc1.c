#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void exec_prog(int pid) {
	if(pid == -1){
		printf("fork() failed");
	}else if(pid == 0){
		execl("/home/cgson/Desktop/2012136065/lab8/subproc", "subproc",NULL);
	}else{ 
		wait((int*)0);
		printf("process completed\n");
	}
}


void main() {
	printf("2012136065 SonChangGwon\n");
	int i = 0;
	pid_t pid[10];
	

	for(i = 0 ; i < 10 ; i++){
		pid[i] = fork();
		exec_prog(pid[i]);
	}

	printf("Finished (process)\n");
}
