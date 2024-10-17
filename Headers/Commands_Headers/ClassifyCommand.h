#ifndef CLASSIFYCOMMAND_H
#define CLASSIFYCOMMAND_H
#include "Command.h"
#include "FileIO.h"
#include "KNN.h"


class ClassifyCommand : public Command {
    private:
        bool classified, linked;
        string filePath;
        vector<tuple<Vector, string>>* ptrTrn;
        vector<Vector>* ptrTst;
        vector<tuple<int, string>> results;

    public:
        ClassifyCommand();
        ~ClassifyCommand();
        void execute() override;

        void linkToData( vector<tuple<Vector, string>>*, vector<Vector>*);
        bool isLinkedToData();
        bool isClassified();
        void unlinkData();
        vector<tuple<int, string>>* getResults();

};


#endif