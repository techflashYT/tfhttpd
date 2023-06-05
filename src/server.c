#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <things.h>
#include <string.h>
#include <stdbool.h>

void serverLoop() {
	int serverSock, clientSock;
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t addrSize = sizeof(clientAddr);
	pthread_t thread;

	serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSock == -1) {
		perror("Socket creation failed");
		exit(1);
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(6969);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		perror("Binding failed");
		exit(1);
	}

	if (listen(serverSock, 10) == -1) {
		perror("Listening failed");
		exit(1);
	}

	while (1) {
		clientSock = accept(serverSock, (struct sockaddr*)&clientAddr, &addrSize);
		if (clientSock == -1) {
			perror("Accepting failed");
			continue;
		}

		if (pthread_create(&thread, NULL, handleRequest, (void*)&clientSock) != 0) {
			perror("Thread creation failed");
			close(clientSock);
		}
		pthread_detach(thread);
	}
}