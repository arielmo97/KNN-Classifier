#include "PackageReciever.h"



void initIODescriptors(map<DIOS, DefaultIO*>& _dios, int _sock) {
    _dios[_SOK_] = new SocketIO(_sock);
    _dios[_FIO_] = new FileIO("");
    _dios[_STD_] = new StandardIO();
}


bool sendData(map<DIOS, DefaultIO*>& _dios, string _records) {
    string status;
    list<string> rows = seperateElements(_records, '\n');
    for (string row : rows) {
        _dios[_SOK_]->write(row); // send the classified data to server row by row
        status = _dios[_SOK_]->read();
        if (status != "__ACK__") { // check if can continue to the rest of the data.
             _dios[_STD_]->write(status);
             return false;
        }
    }
    _dios[_SOK_]->write("__EOS__");
    return true;
}


void uploadRequest(map<DIOS, DefaultIO*>& _dios) {
    string filePath, records, lenStatus;
     _dios[_STD_]->write(_dios[_SOK_]->read()); // wait for server to ask for upload classified
    filePath = _dios[_STD_]->read(); // read classified file path input from user
    _dios[_FIO_]->setFilePath(filePath); 
    records = _dios[_FIO_]->read(); // try to read all classified data from the file
    if (records == "__FTO__") { // check if was able to open classified file
         _dios[_STD_]->write("Invalid input");
         _dios[_SOK_]->write("__EOS__");
        return;
    }
    if (!sendData(_dios, records)) {
        return;
    }
    lenStatus = _dios[_SOK_]->read(); // check if all vectors in the file are from the same dimension
    if (lenStatus != "__ACK__") {
         _dios[_STD_]->write(lenStatus);
          //_dios[_SOK_]->write("__EOS__");
        return;
    }


    _dios[_STD_]->write(_dios[_SOK_]->read()); // wait for server to ask for upload uncalssified
    filePath = _dios[_STD_]->read(); // read unclassified file path input from user
    _dios[_FIO_]->setFilePath(filePath);
    records = _dios[_FIO_]->read(); // try to read all unclassified data from the file
    if (records == "__FTO__") { // check if was able to open unclassified file
        _dios[_STD_]->write("Invalid input");
        _dios[_SOK_]->write("__EOS__");
        return;
    }
    if (!sendData(_dios, records)) {
        return;
    }
    lenStatus = _dios[_SOK_]->read(); // check if all vectors in the file are from the same dimension
    if (lenStatus != "__ACK__") {
        _dios[_STD_]->write(lenStatus);
       // _dios[_SOK_]->write("__EOS__");
        return;
    }
      _dios[_STD_]->write(_dios[_SOK_]->read());
}


void settingsRequest(map<DIOS, DefaultIO*>& _dios) {
    string serverAns;
    _dios[_STD_]->write(_dios[_SOK_]->read()); // recieve current algorithm parameters from server
    string userInput = _dios[_STD_]->read();    // get input for new parameters
    _dios[_SOK_]->write(userInput); // send input to server
    while (true) {
        serverAns = _dios[_SOK_]->read();
        if (serverAns == "__EOS__") {
            break;
        } else {
            _dios[_STD_]->write(serverAns);
        }
    }
}


void classifyRequest(map<DIOS, DefaultIO*>& _dios) {
    string serverAns;
    while (true) {
        serverAns = _dios[_SOK_]->read();
        if (serverAns == "__EOS__") {
            break;
        } else {
            _dios[_STD_]->write(serverAns);
        }
    }
}


void displayRequest(map<DIOS, DefaultIO*>& _dios) {
    vector<string> results;
    string serverAns;
    while (true) {
        serverAns = _dios[_SOK_]->read();
        if (serverAns == "__EOS__") {
            break;
        } else {
            results.push_back(serverAns);
        }
    }
    vector<string>::iterator it;
    for (it = results.begin(); it != results.end(); ++it) {
        _dios[_STD_]->write(*it);
    }
}


bool isReadyToDWNLD(map<DIOS, DefaultIO*>& _dios) {
    string serverAns = _dios[_SOK_]->read();
    if (serverAns == "__OK__") {
        return true;
    }
    _dios[_STD_]->write(serverAns);
    return false;
}


void downloadRequest(map<DIOS, DefaultIO*>& _dios, vector<string>& _dwnldRslts) {
    if (!_dwnldRslts.size()) {
        _dwnldRslts.clear();
    }
    string serverAns;
    while (true) {
        serverAns = _dios[_SOK_]->read();
        if (serverAns == "__EOS__") {
            break;
        }
        if (serverAns == "Done.") {
            continue;
        }
        _dwnldRslts.push_back(serverAns);
    }
}


void writeToFile(map<DIOS, DefaultIO*>& _dios, vector<string>& _dwnldRslts, string _filePath) {
    _dios[_FIO_]->setFilePath(_filePath);
    vector<string>::iterator it;
    for (it = _dwnldRslts.begin(); it != _dwnldRslts.end(); ++it) {
        _dios[_FIO_]->write((*it) + "\n");
    }
    _dwnldRslts.clear();
}


void exitRequest(map<DIOS, DefaultIO*>& _dios) {
    map<DIOS, DefaultIO*>::iterator it;
    for (it = _dios.begin(); it != _dios.end(); ++it) {
        delete it->second;
    }
}