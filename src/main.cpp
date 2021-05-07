#include <Arduino.h>

/* Headers? What that */
// #include "Client.cpp"
#include <ArduinoJson.h>  // Arduino JSON Library
#include <WebSockets.h>
#include <WebSocketsClient.h>

#include "WiFi.h"
// #include "standalone/utils/wifi.hpp"

//////////////
WebSocketsClient webSocket;

const char* ssid = "";
const char* password = "";

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("Disconnected from WiFi access point");
    Serial.print("WiFi lost connection. Reason: ");
    Serial.println(info.disconnected.reason);
    Serial.println("Trying to Reconnect");
    WiFi.begin(ssid, password);
}

String getMACPrefix() {
    String MAC = WiFi.macAddress();
    MAC.replace(":", "");
    return MAC.substring(0, 6);
}

void initWiFi(
    // const char* ssid, const char* password
) {
    WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);

    WiFi.mode(WIFI_STA);
    WiFi.setHostname(("Talyte-" + getMACPrefix()).c_str());
    WiFi.begin(ssid, password);
    Serial.begin(9600);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.printf("[WSc] Disconnected!\n");
            break;
        case WStype_CONNECTED:
            Serial.printf("[WSc] Connected to url: %s\n", payload);

            // send message to server when Connected
            webSocket.sendTXT("Connected");
            break;
        case WStype_TEXT:
            Serial.printf("[WSc] get text of length %u\n", length);
            {
                DynamicJsonDocument json = DynamicJsonDocument(length);
                DeserializationError err = deserializeJson(json, payload);

                if (err) {
                    Serial.println(err.c_str());
                    break;
                };

                String updateType = json["update-type"];

/*
    "from-scene": "FROM",
    "to-scene": "TO",
    "update-type": "TransitionBegin"

    "from-scene": "FROM",
    "to-scene": "TO",
    "update-type": "TransitionVideoEnd"

    "to-scene": "TO",
    "update-type": "TransitionEnd"




*/
                if (updateType == "PreviewSceneChanged") {
                    Serial.print("Preview ");
                    Serial.println((const char*)json["scene-name"]);
                    break;
                } else if (updateType == "SwitchScenes") {
                    Serial.print("Switch ");
                    Serial.println((const char*)json["scene-name"]);
                }

                json.clear();
            }
            break;

        case WStype_BIN:
        case WStype_ERROR:
        case WStype_FRAGMENT_TEXT_START:
        case WStype_FRAGMENT_BIN_START:
        case WStype_FRAGMENT:
        case WStype_FRAGMENT_FIN:
        case WStype_PING:
        case WStype_PONG:
            break;
    }
}

void setup() {
    // WiFiUtils::
    initWiFi();

    // server address, port and URL
    webSocket.begin("OBS_OR_TALYTE_ASSISTANT_IP", 4444, "/");

    // event handler
    webSocket.onEvent(webSocketEvent);

    webSocket.setReconnectInterval(5000);
    // put your setup code here, to run once:
    // TalyteClient C;
    // C.setup("OBS_OR_TALYTE_ASSISTANT_IP", 4444);
}

void loop() {
    webSocket.loop();
}