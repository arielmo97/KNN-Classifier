#ifndef DEFAULTIO_H
#define DEFAULTIO_H
#include <string.h>
#include <iostream>
#include <cstring>
using namespace std;

class DefaultIO {

public:
    virtual string read() = 0;
    virtual void write(string) = 0;
    virtual void setFilePath(string) = 0;
};

#endif