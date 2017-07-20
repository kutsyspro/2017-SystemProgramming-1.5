#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>

typedef struct{
        long data_type;
        char pid[10];
        char id[20];
}PRODUCER;

typedef struct{
        long data_type;
        char pid[10];
        char id[20];
        char name[100];
}CONSUMER;

int main(void){
	char s_msg[100];
	PRODUCER pro;
	CONSUMER con;
	int msqid_p, msqid_c;
	int key[2] = { 1234, 12345 };

	if((msqid_p = msgget((key_t)key[0], 0666|IPC_CREAT)) == -1){
		perror("msgget fail : ");
		exit(0);
	}
	
	if((msqid_c = msgget((key_t)key[1], 0666|IPC_CREAT)) == -1){
		perror("msgget fail : ");
		exit(0);
	}

	while(1){
		printf("Please type \"start\" for start : ");
		scanf("%s", s_msg);

		if(strcmp(s_msg, "start") == 0){	
			pro.data_type = 1;
			sprintf(pro.pid, "%d", getpid());
			sprintf(pro.id, "%s", "2012136065");
			
			if(msgsnd(msqid_p, &pro, sizeof(PRODUCER)-sizeof(long), 0) == -1){
				perror("msgsnd fail : ");
				exit(0);
			}

			if(msgrcv(msqid_c, &con, sizeof(CONSUMER)-sizeof(long), 2, 0) == -1){
				perror("msgrcv fail : ");
				exit(0);
			}

			printf("My pid = %s\nConsumer pid = %s, Consumer Name = %s, Consumer id = %s\n", pro.pid, con.pid, con.name, con.id);
		}else if(strcmp(s_msg, "exit") == 0){
			kill((pid_t)atoi(con.pid), SIGKILL);
			if((msgctl(msqid_p, IPC_RMID, 0) == -1) || (msgctl(msqid_c, IPC_RMID, 0) == -1)){
				perror("message queue remove fail : ");
				exit(0);
			}
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_SUCCESS);
}
