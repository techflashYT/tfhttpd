#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <things.h>
HttpRequest  *req;
HttpResponse *res;
void handleRequestLogic() {
	// Modify this function to implement your desired logic
	// This is a sample implementation that returns a fixed response
	if (strcmp(req->url, "/v1/msg/s") == 0) {
		res->status = "200 OK";
		res->data = "Hello from TFHTTPd-0.0.1";
	} else {
		res->status = "404 Not Found";
		res->data = "404 Not Found";
	}
}

void generateResponse(char *responseStr) {
	if (responseStr == NULL) {
		fputs("Bad responseStr", stderr);
		exit(1);
	}
	sprintf(responseStr, 
		"HTTP/1.1 %s\r\n"
		"Server: %s\r\n"
		"\r\n"
		"\r\n"
		"%s",

		res->status,
		servName,
		res->data
	);
}