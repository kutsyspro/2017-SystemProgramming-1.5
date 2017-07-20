#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

void *subproc(void *data){
	struct tm *t;
	time_t _t;
	pid_t pid = getpid();
	int r;

	r = rand() % 9 + 1;

	while(count < (int)data){
		pthread_mutex_lock(&mymutex);
		count++;
		time(&_t);
		t = localtime(&_t);
		printf("pid = %d, time = %4d.%02d.%02d %02dh%02dm%02ds, count = %d\n", 
				pthread_self(), t->tm_year+1900, t->tm_mon+1, t->tm_mday,
				t->tm_hour, t->tm_min, t->tm_sec, count);
		pthread_mutex_unlock(&mymutex);
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

	srand(time(NULL));

	for(i = 0 ; i < 10 ; i++){
		pthread_create(&threads[i], NULL, &subproc, (void *)num);
	}
	for(i = 0 ; i < 10 ; i++){
		pthread_join(threads[i], &thread_result);
	}
	
	printf("Finished Successfully\n");

	pthread_mutex_destroy(&mymutex);

	return 0;
}
