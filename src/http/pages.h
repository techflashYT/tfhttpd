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

static page_t pages[] = {
	{ "", "", NULL }
};
