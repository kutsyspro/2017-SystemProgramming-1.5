#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

int main(void){
	int res, pipe_id;
	char pid[10], id[20];
	char s_msg[100];

	int shmid_p_pid, shmid_p_id;
	int shmid_c_pid, shmid_c_id, shmid_c_name;
	int p_flag, c_flag;

	void *p_pid, *p_id;
        void *c_pid, *c_id, *c_name;
	int *p_f, *c_f;

	int key[5] = { 1234, 12345, 123456, 1234567, 12345678 };
	int flag[2] = { 11116, 11103 };

	int i;
	pid_t kill_c_pid;

	sprintf(pid, "%d", getpid());
	sprintf(id, "%s", "2012136065");

	shmid_p_pid = shmget((key_t)key[0], sizeof(char), 0666|IPC_CREAT);
	shmid_p_id = shmget((key_t)key[1], sizeof(char), 0666|IPC_CREAT);
	if((shmid_p_pid == -1) || (shmid_p_id == -1)){
		perror("shmget failed : ");
		exit(0);
	}

	shmid_c_pid = shmget((key_t)key[2], sizeof(char), 0666|IPC_CREAT);
	shmid_c_id = shmget((key_t)key[3], sizeof(char), 0666|IPC_CREAT);
	shmid_c_name = shmget((key_t)key[4], sizeof(char), 0666|IPC_CREAT);

        if((shmid_c_pid == -1) || (shmid_c_id == -1) || (shmid_c_name == -1)){
                perror("shmget failed : ");
                exit(0);
        }

	p_flag = shmget((key_t)flag[0], sizeof(int), 0666|IPC_CREAT);
	c_flag = shmget((key_t)flag[1], sizeof(int), 0666|IPC_CREAT);
	if((p_flag == -1) || (c_flag == -1)){
		perror("shmget failed : ");
		exit(0);
	}

	for(i = 0 ; i < 5 ; i++){
		printf("Key[%d] %x\n", i, key[i]);
	}

	p_pid = shmat(shmid_p_pid, (void *)0, 0);
	p_id = shmat(shmid_p_id, (void *)0, 0);
	if((!p_pid) || (!p_id)){
		perror("shmat failed : ");
		exit(0);
	}

	c_pid = shmat(shmid_c_pid, (void *)0, 0);
	c_id = shmat(shmid_c_id, (void *)0, 0);
	c_name = shmat(shmid_c_name, (void *)0, 0);
	if((!c_pid) || (!c_id) || (!c_name)){
		perror("shmat failed : ");
		exit(0);
	}

	p_f = shmat(p_flag, (void *)0, 0);
	c_f = shmat(c_flag, (void *)0, 0);
	if((!p_f) || (!c_f)){
		perror("shmat failed : ");
		exit(0);
	}

	*p_f = 0; *c_f = 0;

	while(1){
		printf("Please type \"start\" for start : ");
		scanf("%s", s_msg);

		if(strcmp(s_msg, "start") == 0){
			
			strcpy(p_pid, pid);
			strcpy(p_id, id);
			*p_f = 1;

			while(*c_f == 0);

			printf("My pid = %s\nConsumer pid = %s, Consumer Name = %s, Consumer id = %s\n", p_pid, c_pid, c_name, c_id);

			kill_c_pid = (pid_t)atoi(c_pid);

			strcpy(p_pid, "");
			strcpy(p_id, "");
			strcpy(c_pid, "");
			strcpy(c_id, "");
			strcpy(c_name, "");
			*p_f = 0; *c_f = 0;
		}else if(strcmp(s_msg, "exit") == 0){
			kill(kill_c_pid, SIGKILL);
			if((shmctl(shmid_p_pid, IPC_RMID, 0) == -1) || (shmctl(shmid_p_id, IPC_RMID, 0) == -1) ||\
				(shmctl(shmid_c_pid, IPC_RMID, 0) == -1) || (shmctl(shmid_c_id, IPC_RMID, 0) == -1) ||\
				(shmctl(shmid_c_name, IPC_RMID, 0) == -1)){
				 perror("shared memory remove fail : ");
				 exit(0);
			}
			if((shmctl(p_flag, IPC_RMID, 0) == -1) || (shmctl(c_flag, IPC_RMID, 0) == -1)){
				perror("shared memory remove fail : ");
				exit(0);
			}
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_SUCCESS);
}
