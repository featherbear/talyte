#ifndef TALYTECLIENT_H
#define TALYTECLIENT_H
#pragma once

#include <WebSockets.h>
#include <WebSocketsClient.h>

#include <string>

class TalyteClient {
   private:
    WebSocketsClient webSocket;
    void webSocketEvent(WStype_t type, uint8_t* payload, size_t length);

   public:
    TalyteClient();
    void loop();
    void setup(const char* host, int port);
};

#endif