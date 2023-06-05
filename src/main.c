#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <things.h>

char *servName = "TFHTTPd-0.0.1";

void cleanup() {
    free(req);
    free(res);
}

int main() {
    req  = malloc(sizeof(HttpRequest));
    res = malloc(sizeof(HttpResponse));
    atexit(cleanup);
    serverLoop();
    return 0;
}
