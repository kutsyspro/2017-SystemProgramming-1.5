#include<stdio.h>
#include<stdlib.h>
extern char **environ;


int main()
{
	setenv("TEST_ENV", "1234", 0);

	while(*environ)
	{
		printf("%s\n", *environ++);
	}

	return 0;
}
