#include <stdbool.h>
#include <stdint.h>
#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 1024
typedef struct {
    char method[9];
    char url[64];
    char protocol[10];
    char headers[4096];
    char data[4096];
} HttpRequest;

typedef struct {
    char *status;
    char *data;
} HttpResponse;

typedef struct {
    char url[64];
    char method[9];
    void (*handler)();
} page_t;

extern HttpRequest  *req;
extern HttpResponse *res;
extern page_t        pages[];
extern uint_fast8_t  numPages;

void *handleRequest     (void       *arg        );
void  parseRequest      (const char *requestStr );
char *getHeaderValue    (char       *header     );
void  handleRequestLogic(                       );
void  generateResponse  (char       *responseStr);
void  serverLoop        (                       );
extern char *servName;