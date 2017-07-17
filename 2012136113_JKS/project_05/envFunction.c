#include<stdio.h>
#include<stdlib.h>

int main(){
	//print HOME,PS1,PATH,LD_LIBRARY_PATH values
	printf("$HOME =%s\n", getenv("HOME"));
	printf("$PS1 = %s\n",getenv("PS1"));
	printf("$PATH =%s\n",getenv("PATH"));
	printf("$LD_LIBRARY_PATH = %s\n", getenv("LD_LIBRARY_PATH"));
	//Test_ENV value set 1234 and print TEST_ENV
	setenv("TEST_ENV","1234",1);
	printf("$TEST_ENV = %s\n", getenv("TEST_ENV"));

	return 0;
}
