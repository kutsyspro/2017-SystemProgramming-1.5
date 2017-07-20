#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	char pid[10], id[20], name[100];
	char p_pid[10], p_id[20];

	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;

	sprintf(pid, "%d", getpid());
	sprintf(id, "%s", "2012136065");
	sprintf(name, "%s", "consumer");

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "server_socket");
	len = sizeof(address);

	result = connect(sockfd, (struct sockaddr *)&address, len);

	if(result == -1){
		perror("oops : client1");
		exit(1);
	}

	read(sockfd, p_pid, 10);
	read(sockfd, p_id, 20);

	printf("\nMy id = %s, Producer pid = %s\n\n", id, p_pid);

	write(sockfd, pid, 10);
	write(sockfd, id, 20);
	write(sockfd, name, 100);

	close(sockfd);
	exit(0);
}
