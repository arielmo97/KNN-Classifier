#include "MenuCommand.h"

MenuCommand:: MenuCommand() {
    description = "Welcome to the KNN classifier server. Please choose an option:\n";
    dio = nullptr;
}

MenuCommand:: ~MenuCommand() {
    if (dio != nullptr) {
        delete dio;
    }
}


void MenuCommand:: execute() {
    
}