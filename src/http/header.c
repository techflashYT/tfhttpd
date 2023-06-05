#include <string.h>
#include <things.h>
char *getHeaderValue(char *header) {
    char *value = NULL;
    char *headerLine = strstr(req->headers, header);
    if (headerLine != NULL) {
        value = strtok(headerLine, "\r\n");
        value += strlen(header) + 2;
        value = strdup(value);
    }
    return value;
}
