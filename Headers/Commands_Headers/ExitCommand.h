#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H
#include <list>
#include "Command.h"
#include "DefaultIO.h"

class ExitCommand : public Command {
    private:
        list<Command*> allocs;

    public:
        ExitCommand();
        ~ExitCommand();
        void execute() override;
        void collectAllocMem(Command*);
};




#endif