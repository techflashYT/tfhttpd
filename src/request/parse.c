#include <stdint.h>
#include <string.h>
#include <things.h>
#include <stdlib.h>

void parseRequest(const char *requestStr) {
	char *methodStart   = requestStr;
	char *methodEnd     = strchr(requestStr, ' ');
	char *urlStart      = methodEnd + 1;
	char *urlEnd        = strchr(urlStart, ' ');
	char *protocolStart = urlEnd + 1;
	char *protocolEnd   = strchr(protocolStart, '\r');
	char *headersStart  = protocolEnd + 2;
	char *headersEnd    = strstr(headersStart, "\r\n\r\n");
	char *dataStart     = headersStart + 4;
	char *dataEnd       = NULL; // will be filled in later

	// Extract method
	if (methodEnd != NULL) {
		memcpy(req->method, methodStart, methodEnd - methodStart);
		req->method[methodEnd - methodStart] = '\0';
	}
	else {
		req->method[0] = '\0';
	}

	// Extract URL
	if (urlEnd != NULL) {
		memcpy(req->url, urlStart, urlEnd - urlStart);
		req->url[urlEnd - urlStart] = '\0';
	}
	else {
		req->url[0] = '\0';
	}

	// Extract protocol
	if (protocolEnd != NULL) {
		memcpy(req->protocol, protocolStart, protocolEnd - protocolStart);
		req->protocol[protocolEnd - protocolStart] = '\0';
	}
	else {
		req->protocol[0] = '\0';
	}

	// Extract headers
	if (headersEnd != NULL) {
		memcpy(req->headers, headersStart, headersEnd - headersStart);
		req->headers[headersEnd - headersStart] = '\0';
	}
	else {
		req->headers[0] = '\0';
	}
}
