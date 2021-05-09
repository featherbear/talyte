#ifndef TALYTECLIENT_H
#define TALYTECLIENT_H
#pragma once

#include <WebSockets.h>
#include <WebSocketsClient.h>

#include <string>

#include "TalyteState.hpp"

enum ChangeEventType {
    Program = 0b01,
    Preview = 0b10,
    ALL = 0b11
};

typedef std::function<void(std::string sceneName)> ChangeEventHandler;

class TalyteClient {
   private:
    WebSocketsClient webSocket;
    void webSocketEvent(WStype_t type, uint8_t* payload, size_t length);
    ChangeEventHandler _programChangeEventHandler;
    ChangeEventHandler _previewChangeEventHandler;

   public:
    TalyteClient();
    void loop();
    void connect(const char* host, int port);
    TalyteState State;
    void set_change_event_handler(enum ChangeEventType type, ChangeEventHandler handler);
};

#endif