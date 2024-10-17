#include "ExitCommand.h"


ExitCommand:: ExitCommand() {
    description = "8. exit";
    dio = nullptr;
}


ExitCommand:: ~ExitCommand() {
    if (dio != nullptr) {
        delete dio;
    }
}


void ExitCommand:: collectAllocMem(Command* _command) {
    allocs.push_back(_command);
}


void ExitCommand:: execute() {
    for (Command* elem: allocs) {
        if (elem != nullptr) {
            delete elem;
        }
    }
}
