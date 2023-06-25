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

#include "../pages/v1/auth/r.c"
#include "../pages/v1/auth/l.c"
#include "../pages/v1/msg/s.c"

#define P "/v1/"
static page_t pages[] = {
	{P"msg/s", "POST", sendMsg},
	{P"msg/s", "ANY",  badReq},
	{P"auth/l", "POST", login},
	{P"auth/l", "ANY",  badReq},
	{P"auth/r", "POST", registerUser},
	{P"auth/r", "ANY", badReq}
};
static uint_fast8_t numPages = 6;