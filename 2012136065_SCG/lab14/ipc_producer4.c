#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	char pid[10], id[20];
	char c_pid[10], c_id[20], c_name[100];
	char s_msg[100];

	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;

	sprintf(pid, "%d", getpid());
	sprintf(id, "%s", "2012136065");

	unlink("server_socket");
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	listen(server_sockfd, 5);
	while(1){
		printf("Please type \"start\" for start : ");
		scanf("%s", s_msg);

		if(strcmp(s_msg, "start") == 0){
			printf("server waiting\n");

			client_len = sizeof(client_address);
			client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

			write(client_sockfd, pid, 10);
			write(client_sockfd, id, 20);

			read(client_sockfd, c_pid, 10);
			read(client_sockfd, c_id, 20);
			read(client_sockfd, c_name, 100);

			printf("My pid = %s\nConsumer pid = %s, Consumer Name = %s, Consumer id = %s\n", pid, c_pid, c_name, c_id);
		}else if(strcmp(s_msg, "exit") == 0){
			close(client_sockfd);
			close(server_sockfd);
			exit(EXIT_SUCCESS);
		}
	}
}
