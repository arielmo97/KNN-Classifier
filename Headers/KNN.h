#ifndef KNN_H
#define KNN_H
#include <list>
#include <tuple>
#include <map>
#include "Vector.h"

using namespace std;

class KNN {
    private:

        Vector inputVect;
        
        void calcDistances(list<tuple<double, string>>&, vector<tuple<Vector, string>>, string);
        vector<tuple<double, string>> fetchNeighbors(list<tuple<double, string>>&, int);
        map<string, int> initMap(vector<tuple<double, string>>);
        vector<tuple<double, string>> findKNN(vector<tuple<Vector, string>>, int, string);
        void countOccurs(map<string, int>&, vector<tuple<double, string>>&);   
           
    public:

        KNN(Vector);
        string classify(vector<tuple<Vector, string>>, int, string);
        void updateInputVect(Vector);
            
};
#endif