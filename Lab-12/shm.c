#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <string.h> 
#include <unistd.h> 


int main()
{
	int shmid;
	int pid;

	int *cal_num;
	void *shared_memory = (void *)0;


	// 공유메모리 공간을 만든다.
	shmid = shmget((key_t)1234, sizeof(char *), 0666|IPC_CREAT);

	if (shmid == -1)
	{
		perror("shmget failed : ");
		exit(0);
	}

	// 공유메모리를 사용하기 위해 프로세스메모리에 붙인다. 
	shared_memory = shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *)-1)
	{
		perror("shmat failed : ");
		exit(0);
	}

	cal_num = (int *)shared_memory;
	pid = fork();
	if (pid == 0)
	{
		shmid = shmget((key_t)1234, sizeof(int), 0);
		if (shmid == -1)
		{
			perror("shmget failed : ");
			exit(0);
		}
		shared_memory = shmat(shmid, (void *)0, 0666|IPC_CREAT);
		if (shared_memory == (void *)-1)
		{
			perror("shmat failed : ");
			exit(0);
		}
		//  cal_num = (int *)shared_memory;
		// *cal_num = 1;

		while(1)
		{
			//      *cal_num = *cal_num + 1;
			strcpy(shared_memory, "2014136118");
			printf("num : %s, PID :%d\n", shared_memory, getpid());             
			sleep(1);
		}
	}

	// 부모 프로세스로 공유메모리의 내용을 보여준다. 
	else if(pid > 0)
	{
		while(1)
		{
			sleep(1);
			printf("num : %s, PID :%d\n", shared_memory, getpid());
		}
	}
}
