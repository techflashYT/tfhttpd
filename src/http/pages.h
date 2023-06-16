#include <things.h>
#define P "/v1/"
static char *resCodes[] = {
	"200 OK",
	"204 No Content",
	"400 Bad Request",
	"404 Not Found"
};
#define RES_200 resCodes[0]
#define RES_204 resCodes[1]
#define RES_400 resCodes[2]
#define RES_404 resCodes[3]


static void badReq() {
	res->status = RES_400;
	res->data = "400 Bad Request\nYour client issued a malformed request.";
}
static void sendMsg() {
	// TODO: Store it somewhere
	res->status = RES_204;
	res->data = NULL;
}
page_t pages[] = {
	{P"msg/s", "GET",  badReq},
	{P"msg/s", "POST", sendMsg}
};
uint_fast8_t numPages = 2;