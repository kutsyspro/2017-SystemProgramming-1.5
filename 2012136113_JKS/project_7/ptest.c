#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char *argv[]){
	time_t timer;
	char buffer[26];
	struct tm* tm_info;

	while(1){
		time(&timer);
		tm_info = localtime(&timer);
	
		strftime(buffer, 26, "%Y-%m-%d %H:%M:%S",tm_info);
		fflush(stdout);
		printf("%s\n",buffer);

		sleep(2);
	}
	exit(EXIT_SUCCESS);
}
