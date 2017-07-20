#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	char block[1024];
	FILE *in, *out;
	size_t nread;

	/*	
	if(argc != 3){
		printf("Argument must be three!\n");
		printf("Usage : ProgramName InFile OutFile\n");
		exit(0);
	}
	*/

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	while((nread = fread(block, 1, 1024, in)) > 0){
		printf(".");
		fwrite(block, 1, nread, out);
	}
	printf("\nFile HighCopy Finished!\n");

	fclose(in);
	fclose(out);
	
	return 0;
}
