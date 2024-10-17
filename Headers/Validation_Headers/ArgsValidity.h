#ifndef ARGSVALIDITY_H
#define ARGSVALIDITY_H
#include <iostream>
#include <stdbool.h>
#include <map>
#include <vector>
#include <tuple>
using namespace std;



void printArgsErr();
bool argsLength(int, int);
bool isValidMetric(string);
bool isValidK(string, int);

#endif