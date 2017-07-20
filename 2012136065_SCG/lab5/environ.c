#include <stdio.h>
#include <stdlib.h>

int main(void){
	printf("Environment variable value\n");
	printf("HOME = %s\n", getenv("HOME"));
	printf(" PS1 = %s\n", getenv("PS1"));
	printf("PATH = %s\n", getenv("PATH"));
	printf("LD_LIBRARY_PATH = %s\n", getenv("LD_LIBRARY_PATH"));

	printf("Environment variable setting\n");
	setenv("TEST_ENV", "1234", 0);
	printf("TEST_ENV = %s\n", getenv("TEST_ENV"));
	
	return 0;
}
