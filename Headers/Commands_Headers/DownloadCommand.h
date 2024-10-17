#ifndef DOWNLOADCOMMAND_H
#define DOWNLOADCOMMAND_H
#include "Command.h"

class DownloadCommand : public Command {
    private:
        bool isLnkd;
        bool wasClsfd;
        vector<tuple<int, string>>* results;
        
    public:
        DownloadCommand();
        ~DownloadCommand();
        void execute() override;
        void notifyLnkd();
        void notifyClsfd();
        void fetchResultsDownload(vector<tuple<int, string>>*);
        void detachFrmData();
};



#endif