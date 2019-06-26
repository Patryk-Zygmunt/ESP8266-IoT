#include <FS.h>

#include "static_file_handlers.h"
#include "server.h"
#include "utils.h"
#include "dynamic_file_handlers.h"
#include "init.h"

const char *JS_PATH = "/main.js";
const char *AXIOS_PATH = "/axios.min.js";
const char *MOMENT_PATH = "/moment.min.js";
const char *JQUERY_PATH = "/jquery-3.3.1.slim.min.js";
const char *BOOTSTRAP_PATH = "/bootstrap.min.css";
const char *LOGIN_PATH = "/login.html";
const char *INDEX_PATH = "/index.html";

void handleMainJs()
{
    handleStaticFile(JS_PATH, JS_CONTENT);
}

void handleAxiosJs()
{
    handleStaticFile(AXIOS_PATH, JS_CONTENT);
}

void handleMomentJs()
{
    handleStaticFile(MOMENT_PATH, JS_CONTENT);
}

void handleJqueryJs()
{
    handleStaticFile(JQUERY_PATH, JS_CONTENT);
}

void handleBootstrap()
{
    handleStaticFile(BOOTSTRAP_PATH, CSS_CONTENT);
}

void handleLoginPage()
{
    handleStaticFile(LOGIN_PATH, HTML_CONTENT);
}


void handleRoot()
{
    if (configPresent())
    {
        handleInit();
        return;
    }

    if (!checkIfAuthorized())
    {
        return;
    }

    handleStaticFile(INDEX_PATH, HTML_CONTENT);
}

void handleStaticFile(const char *path, const char *contentType)
{
    if (SPIFFS.exists(path))
    {
        File file = SPIFFS.open(path, "r");
        size_t sent = server.streamFile(file, contentType);
        file.close();
        Serial.printf("[ SERVER ] File %s sent, %d bytes\n", path, sent);
    }
    else
    {
        Serial.printf("[ SERVER ] %s does not exist\n", path);
        sendAlert("Error", "Not Found!", "/", 3);
    }
}
