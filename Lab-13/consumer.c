#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/stat.h> 
struct msgbuf  //구조체도 헤더파일에서 선언된 것과 겹치는 현상이 일어나서 컴파일이 되질 않습니다. 구조체 이름도 바꾸어야합니다.
{
    long msgtype;
    char mtext[256];
    char myname[16];
    int  seq;
};

int main(int argc, char **argv)
{
    key_t key_id;
    struct msgbuf mybuf;
    int msgtype;//전역변수로 빼야 됩니다.

        msgtype = 3;

    key_id = msgget(1234, IPC_CREAT|0666);
    if (key_id < 0)
    {
        perror("msgget error : ");
        exit(0);
    }
    while(1)
    {
        if (msgrcv( key_id, (void *)&mybuf, sizeof(struct msgbuf), msgtype, 0) == -1)
        {
            perror("msgrcv error : ");
            exit(0);    
        }
        printf("num: %s PID : %d \n", mybuf.myname,mybuf.seq);
    }
    exit(0);
}
