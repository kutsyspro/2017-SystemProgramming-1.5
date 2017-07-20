#include <stdio.h>
#include <time.h>

int main(void){
	struct tm *t;
	time_t _t;

	while(1){
		time(&_t);
		t = localtime(&_t);
		printf("\n%4d.%02d.%02d %02dh%02dm%02ds\n\n", 
			t->tm_year+1900, t->tm_mon, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec);
		sleep(2);	
	}
	return 0;
}
