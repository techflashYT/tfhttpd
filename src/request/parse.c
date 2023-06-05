#include <stdint.h>
#include <string.h>
#include <things.h>
#include <stdlib.h>

void parseRequest(const char *requestStr) {
    char *methodStart   = requestStr;
    char *methodEnd     = strchr(requestStr, ' ');
    char *urlStart      = methodEnd + 1;
    char *urlEnd        = strchr(urlStart, ' ');
    char *protocolStart = urlEnd + 1;
    char *protocolEnd   = strchr(protocolStart, '\r');
    char *headersStart  = protocolEnd + 2;
    char *headersEnd    = strstr(headersStart, "\r\n\r\n");
    char *dataStart     = headersStart + 4;
    char *dataEnd       = NULL; // will be filled in later

    // Extract method
    if (methodEnd != NULL) {
        size_t methodLength = methodEnd - methodStart;
        if (methodLength < sizeof(req->method)) {
            char methodBuf[sizeof(req->method)];
            memcpy(methodBuf, methodStart, methodLength);
            methodBuf[methodLength] = '\0';
            strcpy(req->method, methodBuf);
        } else {
            memcpy(req->method, methodStart, sizeof(req->method) - 1);
            req->method[sizeof(req->method) - 1] = '\0';
        }
    } else {
        req->method[0] = '\0';
    }

    // Extract URL
    if (urlEnd != NULL) {
        size_t urlLength = urlEnd - urlStart;
        if (urlLength < sizeof(req->url)) {
            char urlBuf[sizeof(req->url)];
            memcpy(urlBuf, urlStart, urlLength);
            urlBuf[urlLength] = '\0';
            strcpy(req->url, urlBuf);
        } else {
            memcpy(req->url, urlStart, sizeof(req->url) - 1);
            req->url[sizeof(req->url) - 1] = '\0';
        }
    } else {
        req->url[0] = '\0';
    }

    // Extract protocol
    if (protocolEnd != NULL) {
        size_t protocolLength = protocolEnd - protocolStart;
        if (protocolLength < sizeof(req->protocol)) {
            char protocolBuf[sizeof(req->protocol)];
            memcpy(protocolBuf, protocolStart, protocolLength);
            protocolBuf[protocolLength] = '\0';
            strcpy(req->protocol, protocolBuf);
        } else {
            memcpy(req->protocol, protocolStart, sizeof(req->protocol) - 1);
            req->protocol[sizeof(req->protocol) - 1] = '\0';
        }
    } else {
        req->protocol[0] = '\0';
    }

    // Extract headers
    if (headersEnd != NULL) {
        size_t headersLength = headersEnd - headersStart;
        if (headersLength < sizeof(req->headers)) {
            char headersBuf[sizeof(req->headers)];
            memcpy(headersBuf, headersStart, headersLength);
            headersBuf[headersLength] = '\0';
            strcpy(req->headers, headersBuf);
        } else {
            memcpy(req->headers, headersStart, sizeof(req->headers) - 1);
            req->headers[sizeof(req->headers) - 1] = '\0';
        }
    } else {
        req->headers[0] = '\0';
    }
}
