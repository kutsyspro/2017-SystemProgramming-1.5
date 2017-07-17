#include<unistd.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>

void highCopy() {
	FILE *fp1, *fp2;
	char block[1024];
	int nread;
	//open file 1
	//if source file not exist, then error message print
	if((fp1 = fopen("test2.txt","r"))==NULL){
		fprintf(stderr, "input file error\n");
		exit(1);
	}
	//open file2
	fp2 = fopen("result2.txt","w");

	printf("file copy start\n");
	//copy file's contents every 0.5 seconds and print *
	while(fgets(block,sizeof(block),fp1)){
		printf("*");
		fputs(block,fp2);
		sleep(0.5);
	}
	printf("\nfile copy end\n");

	fclose(fp1);
	fclose(fp2);
}

int main(){
	highCopy();
	return 0;
}	
