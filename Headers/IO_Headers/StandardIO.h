#ifndef STANDARDIO_H
#define STANDARDIO_H
#include "DefaultIO.h"

class StandardIO : public DefaultIO {
    public:
        string read() override;
        void write(string) override;
         void setFilePath(string) override;
};



#endif