#include <stdio.h>  

#include <unistd.h>  

#include <pthread.h>  

 

int ncount;    // 쓰레드간 공유되는 자원 

pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER; // 쓰레드 초기화 

 

void *pthread_funct(void *data) {

	time_t timer;
	int number;	
	number = *((int *)data);

	char buffer[26];
	struct tm* tm_info;


	srand(time(NULL));
	int r = rand()%10;


	while(ncount < number) {

		pthread_mutex_lock(&mutex); // 잠금을 생성한다. 
		ncount++;
		time(&timer);

		tm_info = localtime(&timer);

		strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info); 

		fflush(stdout); 
		printf("%d %s %d\n", (int)pthread_self() ,buffer, ncount); 

		pthread_mutex_unlock(&mutex); // 잠금을 해제한다.

		sleep(r);
	}

}



  

int main() { 

	printf("2012136113 Jeong kyeong seok\n");

   	int       thr_id; 

	pthread_t p_thread[10]; 

	int status; 

	int num = 20; 

	ncount = 0; 

	int thr_id1;
	int thr_id2;
	int thr_id3;
	int thr_id4;
	int thr_id5;
	int thr_id6;
	int thr_id7;
	int thr_id8;
	int thr_id9;
	int thr_id10;
	
	
	thr_id1 = pthread_create(&p_thread[0], NULL, pthread_funct, (void *)&num);

  	if (thr_id1 < 0) {

		perror("thread create error : ");

		exit(0);

    	} 



	thr_id2 = pthread_create(&p_thread[1], NULL, pthread_funct, (void *)&num);

  	if (thr_id2 < 0) {

		perror("thread create error : ");

		exit(0);

    	} 



	thr_id3 = pthread_create(&p_thread[2], NULL, pthread_funct, (void *)&num);

  	if (thr_id3 < 0) {

		perror("thread create error : ");

		exit(0);

    	} 



	thr_id4 = pthread_create(&p_thread[3], NULL, pthread_funct, (void *)&num);

  	if (thr_id4 < 0) {

		perror("thread create error : ");

		exit(0);

    	} 



	thr_id5 = pthread_create(&p_thread[4], NULL, pthread_funct, (void *)&num);

  	if (thr_id5 < 0) {

		perror("thread create error : ");

		exit(0);

    	} 



	thr_id6 = pthread_create(&p_thread[5], NULL, pthread_funct, (void *)&num);

  	if (thr_id6 < 0) {

		perror("thread create error : ");

		exit(0);

    	} 



	thr_id7 = pthread_create(&p_thread[6], NULL, pthread_funct, (void *)&num);

  	if (thr_id7 < 0) {

		perror("thread create error : ");

		exit(0);

    	} 



	thr_id8 = pthread_create(&p_thread[7], NULL, pthread_funct, (void *)&num);

  	if (thr_id8 < 0) {

		perror("thread create error : ");

		exit(0);

    	} 



	thr_id9 = pthread_create(&p_thread[8], NULL, pthread_funct, (void *)&num);

  	if (thr_id9 < 0) {

		perror("thread create error : ");

		exit(0);

    	} 



	thr_id10 = pthread_create(&p_thread[9], NULL, pthread_funct, (void *)&num);

  	if (thr_id10 < 0) {

		perror("thread create error : ");

		exit(0);

    	} 


 	pthread_join(p_thread[0], (void *) &status); 
	pthread_join(p_thread[1], (void *) &status); 
	pthread_join(p_thread[2], (void *) &status); 
	pthread_join(p_thread[3], (void *) &status); 
	pthread_join(p_thread[4], (void *) &status); 
	pthread_join(p_thread[5], (void *) &status); 
	pthread_join(p_thread[6], (void *) &status); 
	pthread_join(p_thread[7], (void *) &status); 
	pthread_join(p_thread[8], (void *) &status); 
	pthread_join(p_thread[9], (void *) &status); 

 	printf("finished\n"); 

	status = pthread_mutex_destroy(&mutex); 

	printf("code  =  %d", status); 

	return 0;
} 


