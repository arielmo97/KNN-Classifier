#ifndef DISPLAYCOMMAND_H
#define DISPLAYCOMMAND_H
#include "Command.h"

class DisplayCommand : public Command {
    private:
        vector<tuple<int, string>>* results;
        bool isLnkd, wasClsfd;

    public:
        DisplayCommand();
        ~DisplayCommand();
        void execute() override;
        void fetchResultsDisplay(vector<tuple<int, string>>*);
        void notifyLink();
        void notifyClsfd();
        void detachFromData();
};


#endif
