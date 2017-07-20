#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>


#define MYSOCK_PATH "/tmp/mysocket_path"
#define MYSOCK_BUF_SIZE 64

int main(int argc, char* argv[]) {

	const char* studentId = "2012136113";

	char myPid[16];	

	sprintf(myPid, "%d", getpid());

	char consumerPid[MYSOCK_BUF_SIZE], studentName[MYSOCK_BUF_SIZE];

	char buf[MYSOCK_BUF_SIZE];

	// delete link

	unlink(MYSOCK_PATH);

	// socket function is create socket ans retrun socket
	// 1st variable is trasmission setting, AF_UNIX is process transmission in same system 
	// 2nd variable is data transmassion type, SOCK_STREAM is using TCP/IP

	int mySocket = socket(AF_UNIX, SOCK_STREAM, 0);

	struct sockaddr_un serverAddress, clientAddress;

	serverAddress.sun_family = AF_UNIX;

	strcpy(serverAddress.sun_path, MYSOCK_PATH);

	// bind fucint setting IP addr, port number in socket
	bind(mySocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

	// listen fucntion setting client connect request using socket
	// 2nd variable is waiting massege queue's number

	listen(mySocket, 5);

	char cmdBuf[1024];

	while(1) {

		scanf("%s", cmdBuf);

		//input 'start' program start

		if(strcmp(cmdBuf, "start")==0) {

			socklen_t clientLen = sizeof(clientAddress);

			// accept function is allow connect request and create client socket

			int clientSocket = accept(mySocket,(struct sockaddr*)&clientAddress, &clientLen);

			// write function write ipc_producer pid,.student id  in socket

			strcpy(buf, myPid);

			write(clientSocket, buf, MYSOCK_BUF_SIZE);

			strcpy(buf, studentId);

			write(clientSocket, buf, MYSOCK_BUF_SIZE);



			// read function read ipc_consumer4, student name in socket

			read(clientSocket, consumerPid, MYSOCK_BUF_SIZE);

			read(clientSocket, studentName, MYSOCK_BUF_SIZE);

			// close cilient socket

			close(clientSocket);

			printf("producer4_pid:%s, consumer4_pid:%s, student_id:%s, student_name:%s\n", myPid, consumerPid, studentId, studentName);

		}

		if(strcmp(cmdBuf, "exit")==0) {

			printf("exit program...\n");

			exit(EXIT_SUCCESS);

		}

	}

	exit(EXIT_FAILURE);

}


