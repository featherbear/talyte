#include <ESPmDNS.h>
#include <FS.h>
#include <M5StickC.h>
#include <Preferences.h>
#include <SPIFFS.h>
#include <WebServer.h>

#include "../device.hpp"
#include "configurator_data.h"
#include "wifi.hpp"

namespace Configurator {

static void loop();

static std::unique_ptr<WebServer> server = NULL;

static String getContentType(String filename);

void startConfigurator() {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP_STA);

    WiFi.softAP(WiFi.getHostname());
    IPAddress IP = WiFi.softAPIP();

    Serial.println("Starting configurator...");
    Serial.printf("SSID: %s\n", WiFi.getHostname());
    Serial.printf("IP address: %s\n", IP.toString().c_str());

    if (!MDNS.begin(WiFi.getHostname())) {
        Serial.println("Error setting up MDNS responder!");
    }

    server = std::unique_ptr<WebServer>(new WebServer(80));

    server->on(FPSTR(WWW_PATHS::DATA_NETWORKS), []() {
        if (server->method() != HTTP_GET) return server->close();

        server->send(200, FPSTR(CONTENT_TYPES::JSON), WifiUtils::discoverNetworks());
    });

    // TODO: Current values
    server->on(FPSTR(WWW_PATHS::DATA_CURRENT), []() {
        if (server->method() != HTTP_GET) return server->close();
        // server->send(200, FPSTR(CONTENT_TYPES::JSON), WifiUtils::discoverNetworks());
    });

    server->on(FPSTR(WWW_PATHS::SET_CONFIG), []() {
        if (server->method() != HTTP_POST) return server->close();

        WifiUtils::setWifiAuth(
            server->arg(F("ssid")).c_str(),
            server->arg(F("password")).c_str());

        WifiUtils::setWifiIPMode(server->arg(F("mode")).equals("dhcp"),
                                 server->arg(F("static_ip")).c_str(),
                                 server->arg(F("static_mask")).c_str());

        Preferences preferences;
        preferences.begin("talyte-config", false);
        preferences.putString("tally_host", server->arg(F("tally_host")).c_str());
        preferences.putShort("tally_port", server->arg(F("tally_port")).toInt());
        preferences.putString("tally_program", server->arg(F("tally_program")).c_str());
        preferences.end();

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