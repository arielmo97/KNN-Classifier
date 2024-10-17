#ifndef FILEIO_H
#define FILEIO_H
#include <fstream>
#include "DefaultIO.h"
#include "Vector.h"

class FileIO : public DefaultIO {
    private:
        string filePath;

    public:
        FileIO(string);
        string read() override;
        void write(string) override;
        string getFilePath();
        void setFilePath(string) override;
        
};

#endif