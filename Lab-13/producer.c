#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/stat.h> 

struct msgbuf
{
	long msgtype;
	char mtext[256];
	char myname[16];
	int  seq;
};

int main()
{
	key_t key_id;
	int i;
	struct msgbuf mybuf, rcvbuf;

	key_id = msgget((key_t)1234, IPC_CREAT|0666);
	if (key_id == -1)
	{
		perror("msgget error : ");
		exit(0);
	}


	memset(mybuf.mtext, 0x00, 256); 
	memset(mybuf.myname, 0x00, 16); 
	memcpy(mybuf.mtext, "hello world 4", 13);
	memcpy(mybuf.myname, "yundream", 8);
	mybuf.seq = 0;
	i = 0;

	while(1)
	{
		mybuf.msgtype = 3;
		strcpy(mybuf.myname,"2014136118");
		mybuf.seq=getpid();
		// 메시지를 전송한다. 
		if (msgsnd( key_id, (void *)&mybuf, sizeof(struct msgbuf), IPC_NOWAIT) == -1)
		{
			perror("msgsnd error : ");
			exit(0);
		} 
		printf("send  num : %s, PID : %d\n", mybuf.myname,mybuf.seq);
		i++;
		sleep(1);
	}

	printf("%d \n", rcvbuf.msgtype);
	printf("%s \n", rcvbuf.mtext);
	printf("%s \n", rcvbuf.myname);
	exit(0);
}
