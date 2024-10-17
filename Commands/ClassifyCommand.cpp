#include "ClassifyCommand.h"


ClassifyCommand:: ClassifyCommand() {
    description = "3. classify data\n";
    dio = nullptr;
    classified = false;
    linked = false;
    ptrTrn = nullptr;
    ptrTst = nullptr;
}


ClassifyCommand:: ~ClassifyCommand() {
    if (dio != nullptr) {
        delete dio;
    }
}


bool ClassifyCommand:: isLinkedToData() {
    return linked;
}


bool ClassifyCommand:: isClassified() {
    return classified;
}


void ClassifyCommand:: linkToData( vector<tuple<Vector, string>>* _trn, vector<Vector>* _tst) {
    if (linked) {
        results.clear();
        linked = false;
    }
    ptrTrn = _trn;
    ptrTst = _tst;
    linked = true;
    classified = false;
}


void ClassifyCommand:: execute() {
    if (!linked) {
        dio->write("please upload data");
        dio->write("__EOS__"); 
        return;
    }
    if (K > ptrTrn->size()) {
        dio->write("K parameter is too large");
        dio->write("__EOS__"); 
        return;
    }
    int count = 1;
    string res;
    vector<Vector> tstData = (*ptrTst);
    for (int i = 0; i < tstData.size(); ++i) {
        KNN computer(tstData[i]);
        res = computer.classify((*ptrTrn), K, distanceMetric);
        results.push_back({count, res});
        count++;
    }
    classified = true;
    dio->write("classifying data complete");
    dio->write("__EOS__"); 
}


vector<tuple<int, string>>* ClassifyCommand:: getResults() {
    if (results.size() == 0) {
        return nullptr;
    }
    return &results;
}


void ClassifyCommand:: unlinkData() {
    results.clear();
    linked = false;
    classified = false;
}


