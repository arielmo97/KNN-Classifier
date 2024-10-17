#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include "ServerHeaders.h"

enum OPTS {_MNU_ = 0, _UPLD_ = 1, _STNGS_ = 2, _CLSFY_ = 3, _DSPLY_ = 4, _DWNLD_ = 5, _EXT_ = 8 };


void handleClinet(int);
void initCommands(map<OPTS, Command*>&);
void attachSocket(map<OPTS, Command*>&, SocketIO*);
string generateMenu(const map<OPTS, Command*>&);
void updateSettings(map<OPTS, Command*>&);
void runKNN(map<OPTS, Command*>&);
void canDisplay(map<OPTS, Command*>&);
void detachClient(map<OPTS, Command*>&);
bool canDownload(map<OPTS, Command*>&, SocketIO*);
void startDownload(map<OPTS, Command*>&);

#endif