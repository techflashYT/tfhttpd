#include <things.h>
typedef struct {
	char url[64];
	char method[9];
	void (*handler)();
} page_t;

#include "../pages/common.h"


static void badReq() {
	res->status = RES_400;
	res->data = "400 Bad Request\nYour client issued a malformed request.";
}

static void do404() {
	res->status = RES_404;
	res->data = "404 Not Found\nThe requested page was not found in the server.";
}

static page_t pages[] = {
	{ "", "", NULL }
};
