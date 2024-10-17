#include "SocketIO.h"

SocketIO:: SocketIO(int _clientSock) {
    clientSock = _clientSock;
    memset(buffer, 0, sizeof(buffer));
}


string SocketIO:: read() {
    memset(buffer, 0, sizeof(buffer));
    int readBytes = recv(clientSock, buffer, sizeof(buffer), 0);
    if (readBytes < 0) {
        perror("Failed to retrive data from client");
        return "-1";
    }
    string data;
    data.assign(buffer);
    return data;
}


void SocketIO:: write(string msg) {
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, msg.c_str());
    int sentBytes = send(clientSock, buffer, sizeof(buffer), 0);
    if (sentBytes < 0) {
        perror("Failed to send data to client");
    }
}


void SocketIO:: setFilePath(string _s) {}