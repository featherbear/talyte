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
};

#endif