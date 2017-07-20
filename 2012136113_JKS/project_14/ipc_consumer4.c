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

	const char* studentName = "Jeong kyeong seok";

	char myPid[16];	

	sprintf(myPid, "%d", getpid());

	char producerPid[MYSOCK_BUF_SIZE], studentId[MYSOCK_BUF_SIZE];

	char buf[MYSOCK_BUF_SIZE];

	// socket function is create socket ans retrun socket

	// 1st variable is trasmission setting, AF_UNIX is process transmission in same system 

	// 2nd variable is data transmassion type, SOCK_STREAM is using TCP/IP

	int mySocket = socket(AF_UNIX, SOCK_STREAM, 0);

	struct sockaddr_un serverAddress;

	serverAddress.sun_family = AF_UNIX;

	strcpy(serverAddress.sun_path, MYSOCK_PATH);

	socklen_t addressLen = sizeof(serverAddress);



	while(1) {

		// connect function is request connection to server

		// and succuss retrun 0;

		int result = connect(mySocket,(struct sockaddr*)&serverAddress, addressLen);

		if(result!=0) {

			sleep(0);

			continue;

		}

		// read function read ipc_producer4 pid, strudnet id in socket

		read(mySocket, producerPid, MYSOCK_BUF_SIZE);

		read(mySocket, studentId, MYSOCK_BUF_SIZE);

		printf("producer_pid:%s, student_id:%s\n",producerPid, studentId);


		// write function wirte ipc_consumer4 pid student name in socket

		strcpy(buf, myPid);

		write(mySocket, buf, MYSOCK_BUF_SIZE);

		strcpy(buf, studentName);

		write(mySocket, buf, MYSOCK_BUF_SIZE);

		// close socket

		close(mySocket);

		// create socket

		mySocket = socket(AF_UNIX, SOCK_STREAM, 0);

	}

	exit(EXIT_FAILURE);

}
