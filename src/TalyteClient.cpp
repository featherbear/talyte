#define TALYTE_VERSION "0.1"

#include "TalyteClient.hpp"

#include <ArduinoJson.h>

#include <string>

void TalyteClient::webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
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
            Serial.printf("[WSc] get text of length %s, %u\n", payload, length);
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
                    State.currentPreview = (String)(const char*)json["scene-name"];

                    if (_previewChangeEventHandler) {
                        _previewChangeEventHandler(State.currentPreview);
                    }
                    break;
                } else if (updateType == "SwitchScenes") {
                    State.currentProgram = (String)(const char*)json["scene-name"];
                    if (_programChangeEventHandler) {
                        _programChangeEventHandler(State.currentProgram);
                    }
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

TalyteClient::TalyteClient() {
    // We can't override the arduino-WebSocket-Client user agent,
    // but we can add a second user agent and cause the sent UA
    // to be turned into a comma separated list???
    webSocket.setExtraHeaders("User-Agent: Talyte " TALYTE_VERSION);  // Hehe macros go brr
    webSocket.onEvent(std::bind(&TalyteClient::webSocketEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    webSocket.setReconnectInterval(5000);
}

void TalyteClient::loop() {
    webSocket.loop();
}

void TalyteClient::connect(String host, int port) {
    // TODO: Password support? But will need to add in base64 and SHA256 library... ceebs

    webSocket.begin(host, port, "/");
}

void TalyteClient::set_change_event_handler(enum ChangeEventType type, ChangeEventHandler handler) {
    if (type & ChangeEventType::Program) _programChangeEventHandler = handler;
    if (type & ChangeEventType::Preview) _previewChangeEventHandler = handler;
}
