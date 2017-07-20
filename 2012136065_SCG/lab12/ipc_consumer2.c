#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(void){
	int res, pipe_id;
	char pid[10], id[20], name[100];

	int shmid_c_pid, shmid_c_id, shmid_c_name;
	int shmid_p_pid, shmid_p_id;
	int p_flag, c_flag;

	void *c_pid, *c_id, *c_name;
	void *p_pid, *p_id;
	int *p_f, *c_f;

	int key[5] = { 1234, 12345, 123456, 1234567, 12345678 };
	int flag[2] = { 11116, 11103 };	

	int i;

	sprintf(pid, "%d", getpid());
	sprintf(id, "%s", "2012136065");
	sprintf(name, "%s", "consumer");

	shmid_c_pid = shmget((key_t)key[2], sizeof(char), 0666); 
	shmid_c_id = shmget((key_t)key[3], sizeof(char), 0666);
	shmid_c_name = shmget((key_t)key[4], sizeof(char), 0666);
        if((shmid_c_pid == -1) || (shmid_c_id == -1) || (shmid_c_name == -1)){
                perror("shmget failed : ");
                exit(0);
        }

	shmid_p_pid = shmget((key_t)key[0], sizeof(char), 0666);
	shmid_p_id = shmget((key_t)key[1], sizeof(char), 0666);
	if((shmid_p_pid == -1) || (shmid_p_id == -1)){
		perror("shmget failed : ");
		exit(0);
	}

	p_flag = shmget((key_t)flag[0], sizeof(int), 0666);
	c_flag = shmget((key_t)flag[1], sizeof(int), 0666);
	if((p_flag == -1) || (c_flag == -1)){
		perror("shmget failed : ");
		exit(0);
	}

	c_pid = shmat(shmid_c_pid, (void *)0, 0);
	c_id = shmat(shmid_c_id, (void *)0, 0);
	c_name = shmat(shmid_c_name, (void *)0, 0);
	if((!c_pid) || (!c_id) || (!c_name)){
		perror("shmat failed : ");
		exit(0);
	}

	p_pid = shmat(shmid_p_pid, (void *)0, 0);
	p_id = shmat(shmid_p_id, (void *)0, 0);
	if((!p_pid) || (!p_id)){
		perror("shmat failed : ");
		exit(0);
	}

	p_f = shmat(p_flag, (void *)0, 0);
	c_f = shmat(c_flag, (void *)0, 0);
	if((!p_f) || (!c_f)){
		perror("shmat failed : ");
		exit(0);
	}

	while(1){
		while(*p_f == 0)continue;

		printf("My id = %s, Producer pid = %s\n", pid, p_pid);

		strcpy(c_pid, pid);
		strcpy(c_id, id);
		strcpy(c_name, name);
		*c_f = 1;
		usleep(10000);
	}
	exit(EXIT_SUCCESS);
}
