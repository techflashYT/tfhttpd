#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <things.h>
#include <stdio.h>
void *handleRequest(void *arg) {
	puts("Got request");
	int clientSock = *((int *)arg);
	char requestStr[MAX_REQUEST_SIZE];
	char responseStr[MAX_RESPONSE_SIZE];

	ssize_t requestSize = recv(clientSock, requestStr, sizeof(requestStr) - 1, 0);
	if (requestSize <= 0) {
		close(clientSock);
		pthread_exit(NULL);
	}
	requestStr[requestSize] = '\0';

	parseRequest(requestStr);
	printf(
		"Request info:\n"
		"	==> Method: %s\n"
		"	==> URL: %s\n"
		"	==> Protocol: %s\n"
		"	==> Headers: \n"
		"==============\n"
		"%s\n"
		"==============\n",
		req->method,
		req->url,
		req->protocol,
		req->headers
	);
	handleRequestLogic();

	generateResponse(responseStr);

	send(clientSock, responseStr, strlen(responseStr), 0);
	close(clientSock);
	pthread_exit(NULL);
}