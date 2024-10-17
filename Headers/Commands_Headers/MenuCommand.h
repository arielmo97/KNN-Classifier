#ifndef MENUCOMMAND_H
#define MENUCOMMAND_H
#include "Command.h"

class MenuCommand : public Command {
    public:
        MenuCommand();
        ~MenuCommand();
        void execute() override;
};


#endif
