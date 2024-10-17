#include "StandardIO.h"

string StandardIO:: read() {
    string s;
    getline(cin, s);
    return s;
}


void StandardIO:: write (string _input) {
    cout << _input << endl;
}


void StandardIO:: setFilePath(string _s) {}