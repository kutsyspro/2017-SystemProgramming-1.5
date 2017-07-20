#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

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
		if(msgrcv(msqid_p, &pro, sizeof(PRODUCER)-sizeof(long), 1, 0) == -1){
			perror("msgrcv fail : ");
			exit(1);
		}

		con.data_type = 2;
		sprintf(con.pid, "%d", getpid());
		sprintf(con.id, "%s", "2012136065");
		sprintf(con.name, "%s", "consumer");

		printf("My id = %s, Producer pid = %s\n", con.id, pro.pid);

		if(msgsnd(msqid_c, &con, sizeof(CONSUMER)-sizeof(long),0) == -1){
			perror("msgsnd fail : ");
			exit(0);
		}
	}
	exit(EXIT_SUCCESS);
}
