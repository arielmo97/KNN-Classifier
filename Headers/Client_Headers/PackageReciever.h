#ifndef PACKAGERECIEVER_H
#define PACKAGERECIEVER_H
#include "ClientHeaders.h"

enum DIOS {_SOK_ = 1, _FIO_ = 2, _STD_ = 3};

void initIODescriptors(map<DIOS, DefaultIO*>&, int);
void uploadRequest(map<DIOS, DefaultIO*>&);
bool sendData(map<DIOS, DefaultIO*>&, string);
void settingsRequest(map<DIOS, DefaultIO*>&);
void classifyRequest(map<DIOS, DefaultIO*>&);
void displayRequest(map<DIOS, DefaultIO*>&);
bool isReadyToDWNLD(map<DIOS, DefaultIO*>&);
void downloadRequest(map<DIOS, DefaultIO*>&, vector<string>&);
void writeToFile(map<DIOS, DefaultIO*>&, vector<string>&, string);
void exitRequest(map<DIOS, DefaultIO*>&);


#endif