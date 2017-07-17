#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>
#include<unistd.h>

int count = 0;
void test_funct(){
	pid_t pid = getpid();
	time_t timer;
	char buffer[26];
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	fflush(stdout);

	count++;
	printf("%d %s %d\n", pid, buffer, count);
}
void main(){
	srand(time(NULL));
	int r = rand()%10;

	while(count<20){
		test_funct();
		sleep(r);
	}
}
