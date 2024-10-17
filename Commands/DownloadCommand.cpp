#include "DownloadCommand.h"


DownloadCommand:: DownloadCommand() {
    description = "5. download results\n";
    dio = nullptr;
    isLnkd = false;
    wasClsfd = false;
}


DownloadCommand:: ~DownloadCommand() {
    if (dio != nullptr) {
        delete dio;
    }
}


void DownloadCommand:: notifyLnkd() {
    isLnkd = true;
}


void DownloadCommand:: notifyClsfd() {
    wasClsfd = true;
}


void DownloadCommand:: fetchResultsDownload(vector<tuple<int, string>>* _res) {
    results = _res;
}


void DownloadCommand:: detachFrmData() {
    results = nullptr;
    isLnkd = false;
    wasClsfd = false;
}


void DownloadCommand:: execute() {
    vector<tuple<int, string>> data = (*results);
    vector<tuple<int, string>>::iterator it;
    for (it = data.begin(); it != data.end(); ++it) {
        string record = to_string(get<0>(*it)) + "\t" + get<1>(*it);
        dio->write(record);
    }
    dio->write("__EOS__");
}

