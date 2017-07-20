#include<stdio.h>
#include<stdlib.h>

int main()
{

	printf("HOME: %s\n", getenv("HOME"));
	printf("PS1: %s\n", getenv("PS1"));
	printf("PATH: %s\n", getenv("PATH"));
	printf("LD_LIBRARY_PATH: %s\n", getenv("LD_LIBRARY_PATH"));
	return 0;
}
