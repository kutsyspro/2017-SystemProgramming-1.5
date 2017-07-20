#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int count=0;

void main()
{
	pid_t pid;
	pid_t child;

	int i=0;
	int state;

	for(i=0;i<20;i++)
	{
		pid=fork();

		if(pid==0)
		{
			execl("./subproc","",(char *) 0);
		}

		else if(pid>0)
		{
			count++;
		}

	}

	printf("Finished(process)\n");

}















