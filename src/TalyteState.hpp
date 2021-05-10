#ifndef TALYTESTATE_H
#define TALYTESTATE_H

#include <string>

struct TalyteState {
    TalyteState() {
        currentPreview = "";
        currentProgram = "";
    }
    String currentProgram;
    String currentPreview;
    struct {
        String hostname;
        unsigned short port;
    } network;
};

#endif