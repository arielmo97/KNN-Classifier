#ifndef SERVERHEADERS_H
#define SERVERHEADERS_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include "Authentication.h"
#include "ArgsValidity.h"
#include "FileIntegrity.h"
#include "Vector.h"
#include "KNN.h"
#include "Command.h"
#include "UploadCommand.h"
#include "SettingsCommand.h"
#include "ClassifyCommand.h"
#include "DisplayCommand.h"
#include "DownloadCommand.h"
#include "MenuCommand.h"
#include "ExitCommand.h"
#include "DefaultIO.h"
#include "SocketIO.h"
#include "FileIO.h"
#define BUFFER_LENGTH 4096
using namespace std;


#endif