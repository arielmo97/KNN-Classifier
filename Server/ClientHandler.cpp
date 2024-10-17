#include "ClientHandler.h"



void initCommands(map<OPTS, Command*>& _commands) {
    _commands[_MNU_] = new MenuCommand();
    _commands[_UPLD_] = new UploadCommand();
    _commands[_STNGS_] = new SettingsCommand();
    _commands[_CLSFY_] = new ClassifyCommand();
    _commands[_DSPLY_] = new DisplayCommand();
    _commands[_DWNLD_] = new DownloadCommand();
    _commands[_EXT_] = new ExitCommand();
}


void attachSocket(map<OPTS, Command*>& _commands, SocketIO* _sockWriter) {
    map<OPTS, Command*>::iterator it;
    for (it = _commands.begin(); it != _commands.end(); ++it) {
        (*it).second->setDIO(_sockWriter);
    }
}


string generateMenu(const map<OPTS, Command*>& _commands) {
    string menu = "";
    map<OPTS, Command*>::const_iterator it;
    for (it = _commands.begin(); it != _commands.end(); ++it) {
        menu += (*it).second->getDescription();
    }
    return menu;
}


void updateSettings(map<OPTS, Command*>& _commands) {
    int newK = _commands[_STNGS_]->getK();
    string newMetric = _commands[_STNGS_]->getDistanceMetric();
    map<OPTS, Command*>::iterator it;
    for (it = _commands.begin(); it != _commands.end(); ++it) {
        if ((*it).first == _STNGS_) {
            continue;
        } else {
            (*it).second->setNewK(newK);
            (*it).second->setNewMetric(newMetric);
        }
    }
}


void runKNN(map<OPTS, Command*>& _commands) {
   if (!((UploadCommand*)_commands[_UPLD_])->recievedData()) {
    _commands[_CLSFY_]->execute();
   } else {
    vector<tuple<Vector, string>>* ptrTRN = ((UploadCommand*) _commands[_UPLD_])->gnrtLnkTRN();
    vector<Vector>* ptrTST = ((UploadCommand*) _commands[_UPLD_])->gnrtLnkTST();
    ((ClassifyCommand*) _commands[_CLSFY_])->linkToData(ptrTRN, ptrTST);
    _commands[_CLSFY_]->execute();
   }
}


void canDisplay(map<OPTS, Command*>& _commands) {
    if (((UploadCommand*) _commands[_UPLD_])->recievedData()) {
        ((DisplayCommand*) _commands[_DSPLY_])->notifyLink();
    }
    if(((ClassifyCommand*) _commands[_CLSFY_])->isClassified()) {
        ((DisplayCommand*) _commands[_DSPLY_])->notifyClsfd();
    }
    vector<tuple<int, string>>* ptrRes = ((ClassifyCommand*) _commands[_CLSFY_])->getResults();
    ((DisplayCommand*) _commands[_DSPLY_])->fetchResultsDisplay(ptrRes);
}


bool canDownload(map<OPTS, Command*>& _commands, SocketIO* _sock) {
    if (((UploadCommand*) _commands[_UPLD_])->recievedData()) {
        ((DownloadCommand*) _commands[_DWNLD_])->notifyLnkd();
    } else {
        _sock->write("please upload data");
        return false;
    }
    if(((ClassifyCommand*) _commands[_CLSFY_])->isClassified()) {
        ((DownloadCommand*) _commands[_DWNLD_])->notifyClsfd();
    } else {
        _sock->write("please classify the data");
        return false;
    }
    vector<tuple<int, string>>* ptrRes = ((ClassifyCommand*) _commands[_CLSFY_])->getResults();
    ((DownloadCommand*) _commands[_DWNLD_])->fetchResultsDownload(ptrRes);
    _sock->write("__OK__");
    return true;
}


void startDownload(map<OPTS, Command*>& _commands) {
    _commands[_DWNLD_]->execute();
}


void detachClient(map<OPTS, Command*>& _commands) {
    map<OPTS, Command*>::iterator it;
    for (it = _commands.begin(); it != _commands.end(); ++it) {
        if (it->first == _EXT_) {
            continue;
        } else {
            ((ExitCommand*) _commands[_EXT_])->collectAllocMem(it->second);
        }
    }
}


void handleClinet(int _clientSock) {
    thread t;
    map<string, int> validOpts = {{"1", 0}, {"2", 0}, {"3", 0}, {"4", 0}, {"5", 0}, {"8", 0}}; // map of menu options
    SocketIO sockWriter(_clientSock);   // socket IO descriptor for all commands
    map<OPTS, Command*> commands;  // map of all commands
    initCommands(commands);  // initialize the commands
    attachSocket(commands, &sockWriter); // attach the client socket to all commands
    string menu = generateMenu(commands);
    bool connected = true;
    while (connected) {
        sockWriter.write(menu);
        string request = sockWriter.read();
        if ((request == "0") || (validOpts.find(request) == validOpts.end())) {
            sockWriter.write("Invalid input");
            continue;
        }

        switch (request[0]) {
            case '1':
                sockWriter.write("1");
                ((ClassifyCommand*) commands[_CLSFY_])->unlinkData();
                ((DisplayCommand*) commands[_DSPLY_])->detachFromData();
                ((DownloadCommand*) commands[_DWNLD_])->detachFrmData();
                commands[_UPLD_]->execute();
                continue;


            case '2':
                sockWriter.write("2");
                commands[_STNGS_]->execute();
                updateSettings(commands);
                continue;


            case '3':
                sockWriter.write("3");
                runKNN(commands);
                continue;


            case '4':
                sockWriter.write("4");
                canDisplay(commands);
                commands[_DSPLY_]->execute();
                continue;


            case '5':
                sockWriter.write("5");
                if (canDownload(commands, &sockWriter)) {
                    startDownload(commands);
                }
                continue;
                
            case '8':
                sockWriter.write("8");
                detachClient(commands);
                commands[_EXT_]->execute();
                connected = false;
                break;
        }

    }
    close(_clientSock);
}