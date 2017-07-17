#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

void lowCopy(){
	char block[1024];
	int in, out;
	int nread;
	//input file name = test.txt
	in = open("test.txt", O_RDONLY);
	//output file name = result.txt
	out = open("result.txt",O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	//if read deta byte > 0
	printf("file copy start \n");
	
	while((nread = read(in,block,sizeof(block))) > 0){
		//print . while file copy
		printf(".");
		write(out,block,nread);
		//every file copy work -.5seconds
		//sleep function delay work time
		sleep(0.5);
	}
	printf("\nfile copy end\n");
}
int main(){
	lowCopy();
	return 0;
}
