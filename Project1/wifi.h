#include <ESP8266WiFi.h>
#include <DNSServer.h>

extern DNSServer dnsServer;

void initializeWiFi();

std::string getNetworksInHtml();