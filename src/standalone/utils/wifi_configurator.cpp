#include <ESPmDNS.h>
#include <FS.h>
#include <M5StickC.h>
#include <SPIFFS.h>
#include <WebServer.h>

#include "../device.hpp"
#include "wifi.hpp"
#include "wifi_configurator_data.h"

namespace WifiUtils {
namespace Configurator {

static void loop();

static std::unique_ptr<WebServer> server = NULL;

static String getContentType(String filename);

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

    server->on(FPSTR(WWW_PATHS::DATA_NETWORKS), []() {
        if (server->method() != HTTP_GET) return server->close();

        server->send(200, FPSTR(CONTENT_TYPES::JSON), WifiUtils::discoverNetworks());
    });

    server->on(FPSTR(WWW_PATHS::SET_WIFI), []() {
        if (server->method() != HTTP_POST) return server->close();

        WifiUtils::setWifiAuth(
            server->arg(F("ssid")).c_str(),
            server->arg(F("password")).c_str());

        WifiUtils::setWifiIPMode(server->arg(F("mode")).equals("dhcp"),
                                 server->arg(F("static_ip")).c_str(),
                                 server->arg(F("static_mask")).c_str());

        server->send(200);
        ESP.restart();
    });

    SPIFFS.begin();
    // server->serveStatic("/", SPIFFS, "/");

    server->onNotFound([]() {
        String path = server->uri();

        Serial.println("handleFileRead: " + path);
        if (path.endsWith("/")) path += "index.html";

        if (!SPIFFS.exists(path)) {
            Serial.println("\tFile Not Found");
            server->send(404, FPSTR(CONTENT_TYPES::PLAIN), "404: Not Found");
            return;
        }

        File file = SPIFFS.open(path, "r");
        server->streamFile(file, getContentType(path));
        file.close();
    });

    server->begin();
    Serial.println("Web server listening");

    WifiUtils::discoverNetworks();
    Device::setView(View::SETUP);
    while (true) loop();
}

// Our very own event loop :)
void loop() {
    server->handleClient();
}

static String getContentType(String filename) {
    if (filename.endsWith(".html"))
        return FPSTR(CONTENT_TYPES::HTML);
    else if (filename.endsWith(".css"))
        return FPSTR(CONTENT_TYPES::CSS);
    else if (filename.endsWith(".js"))
        return FPSTR(CONTENT_TYPES::JS);
    else if (filename.endsWith(".ico"))
        return FPSTR(CONTENT_TYPES::ICO);

    // Unknown?
    return FPSTR(CONTENT_TYPES::PLAIN);
}

}  // namespace Configurator
}  // namespace WifiUtils