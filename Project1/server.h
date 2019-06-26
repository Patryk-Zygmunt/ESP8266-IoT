#include <ESP8266WebServer.h>

extern ESP8266WebServer server;
extern const char *HTML_CONTENT;
extern const char *JS_CONTENT;
extern const char *CSS_CONTENT;

void initializeWebServer();

bool checkIfAuthorized();
