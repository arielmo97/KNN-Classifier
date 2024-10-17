
#include "KNN.h"


/// @brief Consturctor of the KNN class.
/// @param other 
KNN::KNN(Vector other) {
        inputVect = Vector();
        inputVect = other;
       
    }


/// @brief calcDistances calculates the distance between all the vectors in the file based on the given distance metric.
/// @param distances 
/// @param data 
/// @param calcMethod 
void KNN::calcDistances(list<tuple<double, string>>& distances, vector<tuple<Vector, string>> data, string calcMethod) {
    vector<tuple<Vector, string>>::iterator it;
    for(it = data.begin(); it != data.end(); ++it) {
        double dist = inputVect.getDistance(get<0>(*it), calcMethod);
        distances.push_back(make_tuple(dist, get<1>(*it)));
    }
    return;
}


/// @brief fetchNeighbors recieves the list of the distances from the input vector and returns the K-Nearest neighbors to that vector.
/// @param distances 
/// @param neighbors 
/// @return vector<tuple<double, string>>.
vector<tuple<double, string>> KNN::fetchNeighbors(list<tuple<double, string>>& distances, int neighbors) {
    distances.sort();
    vector<tuple<double, string>> ourNeighbors;
    list<tuple<double, string>>::iterator it;
    it = distances.begin();
    int i = 0;
    while (i != neighbors) {
        ourNeighbors.push_back(*it);
        ++it;
        ++i;
    }
    return ourNeighbors;
}


/// @brief initMap initializes a map with the neighbors as the keys and 0 as the values. This map will be a counter map to every appearence of every neighbor.
/// @param ourNeighbors 
/// @return map<string, int>.
map<string, int> KNN::initMap(vector<tuple<double, string>> ourNeighbors) {
    map<string, int> occurs;
    vector<tuple<double, string>>::iterator it;
    for(it = ourNeighbors.begin(); it != ourNeighbors.end(); ++it) {
        if(occurs.find(get<1>(*it)) == occurs.end()) {
            occurs.insert({get<1>(*it), 0});
        } 
        else {continue;}
    }
    return occurs;
}


/// @brief countOccurs counts each occurennce of the neighbors.
/// @param occurs 
/// @param ourNeighbors 
void KNN::countOccurs(map<string, int>& occurs, vector<tuple<double, string>>& ourNeighbors) {
    vector<tuple<double, string>>::iterator it;
    for(it = ourNeighbors.begin(); it != ourNeighbors.end(); ++it) {
        occurs[get<1>(*it)]++;
    }
    return;
}


/// @brief findKNN recieves the databse which was extracted from the given file and prforms the KNN algorithm on it.
/// @param data 
/// @param neighbors 
/// @param calcMethod 
/// @return vector<tuple<double, string>>.
vector<tuple<double, string>> KNN::findKNN(vector<tuple<Vector, string>> data, int neighbors, string calcMethod) {
    list<tuple<double, string>> distances;
    calcDistances(distances, data, calcMethod);
    vector<tuple<double, string>> ourNeighbors = fetchNeighbors(distances, neighbors);
    return ourNeighbors;
}


/// @brief classifies the input vector according to its neighbors.
/// @param data 
/// @param neighbors 
/// @param calcMethod 
/// @return string.
string KNN::classify(vector<tuple<Vector, string>> data, int neighbors, string calcMethod) {
    vector<tuple<double, string>> ourNeighbors = findKNN(data, neighbors, calcMethod);
    map<string, int> occurs = initMap(ourNeighbors);
    countOccurs(occurs, ourNeighbors);
    int max = 0;
    string nearest;
    map<string, int>::iterator it;
    for(it = occurs.begin(); it != occurs.end(); ++it) {
        if(max < it->second) {
            max = it->second;
            nearest = it->first;
        }
    }
    return nearest;
}


/// @brief updateVector is a setter for the Vector member of the class.
/// @param other 
void KNN:: updateInputVect(Vector other) {
    inputVect = other;
}