#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include "Vector.h"
#include "DefaultIO.h"
#define BUFFER_LENGTH 4096
using namespace std;

class Command {
    public:
        virtual void execute() = 0;
        virtual string getDescription();
        virtual void setNewK(int);
        virtual void setNewMetric(string);
        virtual int getK();
        virtual string getDistanceMetric();
        void setDIO(DefaultIO*);

    protected:
        string description;
        int K = 5;
        string distanceMetric = "AUC";
        DefaultIO* dio;
        vector<tuple<Vector, string>> trainData;
        vector<Vector> testData;
        
};


#endif