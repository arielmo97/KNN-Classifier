#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>
#include <map>

using namespace std;


class Vector {

    private:

    vector<double> vect;

    
    double euclideanDistance(Vector other);
    double manhattanDistance(Vector other);
    double canberraDistance(Vector other);
    double chebyshevDistance(Vector other);
    double minkowskiDistance(Vector other, double p);
    int calcPrec(double num);

    
    public:

    Vector();
    Vector(vector<double> v);
    Vector& operator= (const Vector& other);
    vector<double> getVector();
    int getSize();
    void printDistances(Vector other);
    double getDistance(Vector other, string id);

};

#endif