#include "SettingsCommand.h"

SettingsCommand:: SettingsCommand() {
    description = "2. algorithm settings\n";
    dio = nullptr;
    dataSize = -1;
}


SettingsCommand:: ~SettingsCommand() {
    if (dio != nullptr) {
        delete dio;
    }
}


void SettingsCommand:: setDataSize(int _dataSize) {
    dataSize = _dataSize;
}


void SettingsCommand:: validParams(list<string>  _userInput) {
    string badK = "invalid value for K";
    string badMetric = "invalid value for metric";
    if ( _userInput.size() != 2) {
        dio->write(badK);
        dio->write(badMetric);
        return;
    }
    if (isValidK(_userInput.front(), dataSize)) {
        setNewK(stoi(_userInput.front()));
    } else {
        dio->write(badK);
    }
    if (isValidMetric(_userInput.back())) {
        setNewMetric(_userInput.back());
    } else {
        dio->write(badMetric);
    }  
    return;
}


void SettingsCommand:: execute() {
    string chunk1 = "The current KNN parameters are: K = ";
    string chunk2 = ", distance = ";
    string settings = chunk1 + to_string(K) + chunk2 + distanceMetric;
    dio->write(settings);
    string userInput = dio->read();
    if (userInput.length() != 0) {
        list<string> ls = seperateElements(userInput, ' ');
        validParams(ls);
    }
    dio->write("__EOS__");
}
