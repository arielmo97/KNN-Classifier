#include "UploadCommand.h"


UploadCommand:: UploadCommand() {
    description = "1. upload unclassified csv data file\n";
    dio = nullptr;
    hasData = false;
}


UploadCommand:: ~UploadCommand() {
    if (dio != nullptr) {
        delete dio;
    }
}


bool UploadCommand:: recievedData() {
    return hasData;
}


bool UploadCommand:: uploadTrainData() {
    string record, vecName;
    list<string> tmp;
    record = dio->read();
    while (record != "__EOS__") {    
        tmp = seperateElements(record, ',');
        if (!nameFound(tmp)) {
            dio->write("Invalid input");
            return false;
        }
        vecName = tmp.back();
        tmp.pop_back();
        tmp = appendZero(tmp);
        if (!isDouble(tmp)) {
            dio->write("Invalid input");
            return false;
        }
        Vector v(makeVector(tmp));
        trainData.push_back(make_tuple(v, vecName));
        dio->write("__ACK__");
        record = dio->read();
    }
    if (!trainData.size()) {
        return false;
    }
    if (!checkLength(trainData)) {
        dio->write("Invalid input");
        return false;
    }
    dio->write("__ACK__");
    return true;
}


bool UploadCommand:: uploadTestData() {
    string record;
    list<string> tmp;
    record = dio->read();
    while (record != "__EOS__") {
        if (!authenticateInput(record, ',')) {
            dio->write("Invalid input");
            return false;
        }
        tmp = seperateElements(record, ',');
        tmp = appendZero(tmp);
        Vector v(makeVector(tmp));
        testData.push_back(v);
        dio->write("__ACK__");
        record = dio->read();
    }
    if (!testData.size()) {
        return false;
    }
    if (!checkLengthUnclssfd(testData)) {
        dio->write("Invalid input");
        return false;
    }
    dio->write("__ACK__");
    return true;
}


void UploadCommand:: execute() {
    if (hasData) {
        trainData.clear();
        testData.clear();
        hasData = false;
    }
   dio->write("Please upload your local train CSV file.");
   if (!uploadTrainData()) {
        trainData.clear();
        return;
   }
   dio->write("Please upload your local test CSV file.");
   if (!uploadTestData()) {
        testData.clear();
        return;
   }
   hasData = true;
   dio->write("Upload complete");
  
}


vector<tuple<Vector, string>>* UploadCommand:: gnrtLnkTRN() {
    return &trainData;
}


vector<Vector>* UploadCommand:: gnrtLnkTST() {
    return &testData;
}