#ifndef SETTINGSCOMMAND_H
#define SETTINGSCOMMAND_H
#include "Command.h"
#include "SocketIO.h"
#include "Authentication.h"
#include "ArgsValidity.h"

class SettingsCommand : public Command {
    private:
        int dataSize;
        void validParams(list<string>);

    public:
        ~SettingsCommand();
        void execute() override;
        SettingsCommand();       
        void setDataSize(int);
};


#endif