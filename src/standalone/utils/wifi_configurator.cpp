#include <ESPmDNS.h>
#include <WebServer.h>

#include "wifi.hpp"
#include "wifi_configurator_data.h"

namespace WifiUtils {
namespace Configurator {

static void loop();

static std::unique_ptr<WebServer> server = NULL;

void startConfigurator() {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP_STA);

    WiFi.softAP(WiFi.getHostname());
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    if (MDNS.begin(WiFi.getHostname())) {
        Serial.println("mDNS responder started");
    } else {
        Serial.println("Error setting up MDNS responder!");
    }

    server = std::unique_ptr<WebServer>(new WebServer(80));

    server->on(String(FPSTR(WWW_PATHS::ROOT)).c_str(), []() {
        server->send(200, FPSTR(CONTENT_TYPES::HTML), String(":)"));
    });
    server->on(String(FPSTR(WWW_PATHS::DATA_NETWORKS)).c_str(), []() {
        server->send(200, FPSTR(CONTENT_TYPES::JSON), WifiUtils::discoverNetworks());
    });

    server->begin();  // Web server start
    Serial.println("Web server listening");

    Serial.println(WifiUtils::discoverNetworks());
    while (true) loop();
}

// Our very own event loop :)
void loop() {
    server->handleClient();
}
}  // namespace Configurator
}  // namespace WifiUtils