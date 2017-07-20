#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	char block[1024];
	int in, out;
	int nread;
	
	/*
	if(argc != 3){
		printf("Argument must be three!\n");
		printf("Usage : ProgramName InFile OutFile\n");
		exit(0);
	}
	*/

	in = open(argv[1], O_RDONLY);
	out = open(argv[2], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

	while((nread = read(in, block, sizeof(block))) > 0){
		printf(".");
		write(out, block, nread);
	}
	printf("\nFile LowCopy Finished!\n");

	exit(0);
}
