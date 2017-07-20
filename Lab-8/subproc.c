#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>

int count=1;

void test_funct(){
	time_t timer;
	char buffer[26];
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	fflush(stdout);
	printf("time : %s\n", buffer);
	printf("PROCESS PID : %d\n",getpid());
	printf("count : %d\n", count);
	count++; 
}

void main()
{
	int i, r=0;

	for(i=0;i<20;i++)
	{
		srand(time(NULL));
		r=rand()%10;
		test_funct();
		sleep(r);

	}
}
