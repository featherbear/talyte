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

    server = std::unique_ptr<WebServer>(new WebServer(80));

    server->on(String(FPSTR(PATH_ROOT)).c_str(), []() {
        server->send(200, FPSTR(HTTP_HEAD_CT), String(":)"));
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