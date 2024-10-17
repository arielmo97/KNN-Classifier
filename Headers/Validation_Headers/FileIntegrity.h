#ifndef FILEINTEGRITY_H
#define FILEINTEGRITY_H

#include <iostream>
#include <stdbool.h>
#include <vector>
#include <fstream>
#include <tuple>
#include "Authentication.h"
#include "Vector.h"
using namespace std;


vector<string> fetchStrings(string);
tuple<Vector, string> convertToTuple(string);
vector<tuple<Vector, string>> fetchData(string);
void fileIntegrityErr();
bool nameFound(list<string>&);
bool checkLength(vector<tuple<Vector, string>>&);
bool checkLengthUnclssfd(vector<Vector>&);

#endif

