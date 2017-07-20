#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

//static int count = 1;

void *subproc(void *data){
	struct tm *t;
	time_t _t;
	pid_t pid = getpid();
	int r;
	int count = 1;

	while(count <= (int)data){
		time(&_t);
		t = localtime(&_t);
		printf("pid = %d, time = %4d.%02d.%02d %02dh%02dm%02ds, count = %d\n", 
				pid, t->tm_year+1900, t->tm_mon, t->tm_mday,
				t->tm_hour, t->tm_min, t->tm_sec, count);

		count++;
		r = rand() % 9 +1;
		sleep(r);
	}
	printf("thread completed!\n");
	pthread_exit((void *)0);
}

int main(void){
	pthread_t threads[10];
	int i, num = 20;
	void *thread_result;
	printf("2012136065 SonChangGwon\n");

	for(i = 0 ; i < 10 ; i++){
		pthread_create(&threads[i], NULL, &subproc, (void *)num);
	}
	for(i = 0 ; i < 10 ; i++){
		pthread_join(threads[i], &thread_result);
	}
	
	printf("Finished (thread)\n");
	exit(EXIT_SUCCESS);
}
