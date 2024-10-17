#include "FileIO.h"

FileIO:: FileIO(string _filePath) {
    filePath = _filePath;
}


string FileIO:: getFilePath() {
    return filePath;
}


void FileIO:: setFilePath(string _filePath) {
    filePath = _filePath;
}


string FileIO:: read() {
    fstream myFile;
    myFile.open(filePath, ios::in);
    if (myFile.fail()) {
        filePath = "";
        return "__FTO__";
    }
    string content = "";
    string record;
    while (getline(myFile, record)) {
        if (record[record.length()-1] == '\r') {
            record.pop_back();
        }
        content += record + "\n";
    }
    myFile.close(); 
    return content;
}


void FileIO:: write(string record) {
    fstream myFile;
    myFile.open(filePath, ios::out | ios::app);
    if (myFile.fail()) {
        cout << "Failed to open " << filePath << endl;
        return;
    }
    myFile << record;
}