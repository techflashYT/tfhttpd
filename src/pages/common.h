#pragma once
#include <stdint.h>
#include <stddef.h>
#include <things.h>
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