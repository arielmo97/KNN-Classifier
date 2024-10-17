#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#include <iostream>
#include <stdbool.h>
#include <list>
#include <vector>
using namespace std;


string removeBlanks(string);
list<string> seperateElements(string, char);
bool isDouble(list<string>);
bool authenticateInput(string, char);
vector<double> makeVector(list<string>);
int atMostOneLetter(string);
int isFormatE(string);
list<string> appendZero(list<string>);

#endif
