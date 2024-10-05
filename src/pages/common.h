#pragma once
#include <stdint.h>
#include <stddef.h>
#include <things.h>

/*
 * some included predefined stuff for use in
 * your pages.
 */

static char *resCodes[] = {
	"200 OK",
	"204 No Content",
	"400 Bad Request",
	"401 Unauthorized",
	"404 Not Found",
	"500 Internal Server Error"
};
#define RES_200 resCodes[0]
#define RES_204 resCodes[1]
#define RES_400 resCodes[2]
#define RES_401 resCodes[3]
#define RES_404 resCodes[4]
#define RES_500 resCodes[5]
