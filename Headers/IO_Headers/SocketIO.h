#ifndef SOCKETIO_H
#define SOCKETIO_H
#include "DefaultIO.h"
#include <sys/socket.h>
#define BUFFER_LENGTH 4096

class SocketIO : public DefaultIO {
    private:
        int clientSock;
        char buffer[BUFFER_LENGTH];

    public:
        SocketIO(int);
        string read() override;
        void write(string) override;
        void setFilePath(string) override;
};

#endif