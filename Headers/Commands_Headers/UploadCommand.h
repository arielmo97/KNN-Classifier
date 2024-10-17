#ifndef UPLOADCOMMAND_H
#define UPLOADCOMMAND_H
#include "Command.h"
#include "SocketIO.h"
#include "Authentication.h"
#include "FileIntegrity.h"

class UploadCommand : public Command {
    private:
        bool hasData;
        bool uploadTrainData();
        bool uploadTestData();

    public:
        UploadCommand();
        ~UploadCommand();
        void execute() override;
        bool recievedData();
        vector<tuple<Vector, string>>* gnrtLnkTRN();
        vector<Vector>* gnrtLnkTST();
                

};

#endif