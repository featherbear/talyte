#ifndef TALYTESTATE_H
#define TALYTESTATE_H

#include <string>

struct TalyteState {
    TalyteState() {
        currentPreview = "";
        currentProgram = "";
        linkedProgram = "";
    }
    String currentProgram;
    String currentPreview;
    String linkedProgram;
    struct {
        String hostname;
        unsigned short port;
    } network;
};

#endif