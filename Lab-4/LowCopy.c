#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	char block[1024];
	int in, out;
	int nread;
	if(argc==1)
	{
		in = open("file.in", O_RDONLY);
		out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

		while((nread = read(in,block,sizeof(block))) > 0)
			write(out,block,nread);
		exit(0);
	}
	else if(argc==2)
	{
		in = open(argv[1], O_RDONLY);
		out = open("parameter copy.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

		while((nread = read(in,block,sizeof(block))) > 0)
			write(out,block,nread);
		exit(0);

	}
	else if(argc==3)
	{ 
		in = open(argv[1], O_RDONLY);
		out = open(argv[2], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

		while((nread = read(in,block,sizeof(block))) > 0)
			write(out,block,nread);
		exit(0);
	}
}

