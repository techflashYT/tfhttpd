#include "../../common.h"

// Login routine
static void login() {
	res->status = RES_200;
	res->data = "{\r\n\t\"token\": 1234}";
}