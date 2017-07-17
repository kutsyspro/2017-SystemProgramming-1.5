#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


int count = 0;

void exec_proc(pid_t pid) {

	switch(pid) {
		case -1 :
			printf("fork failed");
			break;
		case 0 :
			execl( "/home/koreatech/subproc", "subproc",NULL);
			break;
		default : 
			wait((int*)0);
			printf("process completed\n");
	}

}


void main() {

	printf("2012136113 Jeong kyeong seok\n");

	int i = 0;


	pid_t newPid1;	
	newPid1 = fork();
	exec_proc(newPid1);


	pid_t newPid2;
	newPid2 = fork();
	exec_proc(newPid2);

	pid_t newPid3;	
	newPid3 = fork();
	exec_proc(newPid3);


	pid_t newPid4;	
	newPid4 = fork();
	exec_proc(newPid4);


	pid_t newPid5;	
	newPid5 = fork();
	exec_proc(newPid5);


	pid_t newPid6;	
	newPid6 = fork();
	exec_proc(newPid6);


	pid_t newPid7;	
	newPid7 = fork();
	exec_proc(newPid7);


	pid_t newPid8;	
	newPid8 = fork();
	exec_proc(newPid8);


	pid_t newPid9;	
	newPid9 = fork();
	exec_proc(newPid9);


	pid_t newPid10;	
	newPid10 = fork();
	exec_proc(newPid10);


	printf("finished\n");

}


