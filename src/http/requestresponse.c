#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pages.h"
HttpRequest  *req;
HttpResponse *res;


// FIXME: This fixes a weird bug in my editor, as you can see stdbool.h is already present, so idk
#ifndef bool
#define bool _Bool
#define true 1
#define false 0
#endif
static bool pageMatches(int i) {
	// Does the URL match?
	if (strcmp(req->url, pages[i].url) != 0) {
		// Nope, go to the next.
		return false;
	}
	// Yes the URL does match, does this handler apply to any request method?
	if (strcmp(pages[i].method, "ANY") == 0) {
		// Yes, the URL matches, and this handler applies to any request method.
		// Return true to signify that we found a match
		return true;
	}
	// The URL does match, and this handler has a specific method tied to it.  Do the request and this method match?
	if (strcmp(req->method, pages[i].method) != 0) {
		// Nope, this doesn't match.  Go to the next handler.
		return false;
	}
	// Yes, the URL and method match.
	return true;
}
void handleRequestLogic() {
	res->status = RES_404;
	res->data = (void *)0xDEADBEEF;
	res->callback = NULL;
	for (uint_fast8_t i = 0; ; i++) {
		if (pages[i].url[0] == '\0' && pages[i].handler == NULL) {
			// reached the end of the array
			break;
		}

		else if (pageMatches(i)) {
			pages[i].handler();
			return;
		}
	}
	if (res->data == (void *)0xDEADBEEF) {
		// no pages matched, 404
		do404();
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
		"\r\n",

		res->status,
		servName
	);
	if (res->data != NULL) {
		strcat(responseStr, res->data);
	}
	if (res->callback != NULL) {
		res->callback();
	}
}
