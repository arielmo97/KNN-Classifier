#include "DisplayCommand.h"


DisplayCommand:: DisplayCommand() {
    description = "4. display results\n";
    dio = nullptr;
    isLnkd = false;
    wasClsfd = false;
}


DisplayCommand:: ~DisplayCommand() {
    if (dio != nullptr) {
        delete dio;
    } 
}


void DisplayCommand:: fetchResultsDisplay(vector<tuple<int, string>>* _res) {
    results = _res; 
}


void DisplayCommand:: notifyLink() {
    isLnkd = true;
}


void DisplayCommand:: notifyClsfd() {
    wasClsfd = true;
}


void DisplayCommand:: detachFromData() {
    results = nullptr;
    isLnkd = false;
    wasClsfd = false;
}


void DisplayCommand:: execute() {
    if (!wasClsfd) {
        if (!isLnkd) {
            dio->write("please upload data");
            dio->write("__EOS__");
            return;
        }
        dio->write("please classify the data");
        dio->write("__EOS__");
        return;
    }
    string msg;
    vector<tuple<int, string>> data = (*results);
    vector<tuple<int, string>>::iterator it;
    for (it = data.begin(); it != data.end(); ++it) {
        msg = to_string(get<0>(*it)) + "\t" + get<1>(*it);
        dio->write(msg);
    }
    dio->write("Done.");
    dio->write("__EOS__");
}