#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "pages.h"
#include <stdbool.h>
HttpRequest  *req;
HttpResponse *res;

static bool pageMatches(int i) {
	if (strcmp(req->method, pages[i].method) != 0) {
		return false;
	}
	if (strcmp(req->url, pages[i].url) != 0) {
		return false;
	}
	return true;
}
void handleRequestLogic() {
	res->data = 0xDEADBEEF;
	for (uint_fast8_t i = 0; i != numPages; i++) {
		if (pageMatches(i)) {
			pages[i].handler();
		}
	}
	if (res->data == 0xDEADBEEF) {
		// no pages matched, 404
		res->status = RES_404;
		res->data = RES_404;
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
		"\r\n",

		res->status,
		servName
	);
	if (res->data != NULL) {
		strcat(responseStr, res->data);
	}
}