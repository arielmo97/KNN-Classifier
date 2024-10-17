#include "Command.h"


void Command:: setNewK(int _K) {
    K = _K;
}


void Command:: setNewMetric(string _distanceMetric) {
    distanceMetric = _distanceMetric;
}


string Command:: getDescription() {
    return description;
}


int Command:: getK() {
    return K;
}


string Command:: getDistanceMetric() {
    return distanceMetric;
}


void Command:: setDIO(DefaultIO* _dio) {
    dio = _dio;
}

