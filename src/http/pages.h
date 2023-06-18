#include <things.h>
typedef struct {
	char url[64];
	char method[9];
	void (*handler)();
} page_t;

#define P "/v1/"
#include "../pages/common.h"


static void badReq() {
	res->status = RES_400;
	res->data = "400 Bad Request\nYour client issued a malformed request.";
}

#include "../pages/v1/auth/l.c"
#include "../pages/v1/auth/r.c"
#include "../pages/v1/msg/s.c"

static page_t pages[] = {
	{P"msg/s", "POST", sendMsg},
	{P"msg/s", "ANY",  badReq},
	{P"auth/l", "POST", login},
	{P"auth/l", "ANY",  badReq}
};
static uint_fast8_t numPages = 4;