#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
void *thread_function();
int count=0;

int main() {
	int res;
	pthread_t a_thread[10];
	void *thread_result;
	int i=0;

	printf("2014136118 Cho Deun Sol\n");
	printf("-----------------------\n");

	for(i=0;i<10;i++)
	{
		res = pthread_create(&a_thread[i], NULL, thread_function, NULL);
		if (res != 0) {
			perror("Thread creation failed"); exit(EXIT_FAILURE);
		}

		res = pthread_join(a_thread[i], &thread_result);
		if (res != 0) {
			perror("Thread join failed"); exit(EXIT_FAILURE);
		}
	}  
	printf("Finished(thread)\n");
	exit(EXIT_SUCCESS);

}
void *thread_function() {
	int i=0;
	time_t timer;
	char buffer[26];
	struct tm* tm_info;

	for(i=0;i<20;i++){
		srand(time(NULL));
		int r=rand()%10;
		sleep(r);


		time(&timer);
		tm_info = localtime(&timer);
		strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
		fflush(stdout);

		printf("time : %s\n", buffer);
		printf("PROCESS PID : %d\n",getpid());
		printf("function() count : %d, thread count:%d\n",i, count);
	}
	count++;

	pthread_exit("");
}
