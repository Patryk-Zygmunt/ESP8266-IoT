#include <ESP8266WebServer.h>

#include "dynamic_file_handlers.h"
#include "login_service.h"
#include "utils.h"

ESP8266WebServer server(80);
const char *HTML_CONTENT = "text/html";
const char *JS_CONTENT = "application/javascript";
const char *CSS_CONTENT = "text/css";

void initializeWebServer()
{
    const char *headerkeys[] = {"User-Agent", "Cookie"};
    size_t headerkeyssize = sizeof(headerkeys) / sizeof(char *);
    server.collectHeaders(headerkeys, headerkeyssize);
}

bool checkIfAuthorized()
{
    if (server.hasHeader("Cookie"))
    {
        std::string token = toStdStr(server.header("Cookie"));
        Serial.printf("[ SERVER ] Trying to access page with token: %s\n", token.c_str());
        bool tokenValid = loginProvider.isTokenValid(token);
        if (tokenValid)
        {
            Serial.printf("[ SERVER ] Access granted.\n");
            return true;
        }
    }
    Serial.printf("[ SERVER ] Access denied!\n");
    sendAlert("Error", "Access denied!", "/loginPage", 3);
    return false;
}