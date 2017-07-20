#include <stdio.h>
#include <time.h>

static int count = 1;

void test_func(){
	struct tm *t;
	time_t _t;
	pid_t pid = getpid();

	time(&_t);
	t = localtime(&_t);
	printf("pid = %d, time = %4d.%02d.%02d %02dh%02dm%02ds, count = %d\n", 
		pid, t->tm_year+1900, t->tm_mon, t->tm_mday,
		t->tm_hour, t->tm_min, t->tm_sec, count);

	count++;
}

int main(void){
	int i = 0;
	int r;

	srand(time(NULL));

	while(count <= 20){
		test_func();
	}

	return 0;
}

