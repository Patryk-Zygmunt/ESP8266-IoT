#include <ESP8266WebServer.h>
#include "routes.h"
#include "static_file_handlers.h"
#include "rest_handlers.h"
#include "server.h"

void addRoutes()
{
    server.on("/", handleRoot);
    server.on("/main.js", handleMainJs);
    server.on("/axios.min.js", handleAxiosJs);
    server.on("/moment.min.js", handleMomentJs);
    server.on("/jquery-3.3.1.slim.min.js", handleJqueryJs);
    server.on("/bootstrap.min.css", handleBootstrap);
    server.on("/init", handleInit);
    server.on("/doInit", HTTP_POST, handleDoInit);
    server.on("/scheduler", HTTP_POST, handlePostScheduler);
    server.on("/scheduler", HTTP_GET, handleGetScheduler);
    server.on("/loginPage", handleLoginPage);
    server.on("/doLogin", handleDoLogin);
    // server.on("/devices.html", handleJs);
}