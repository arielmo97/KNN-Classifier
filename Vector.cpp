#include "Vector.h"


/// @brief Euclidean_Distance recieves another Vector and calculates the Euclidean distance between this and the other  vector.
/// @param other 
/// @return Euclidean distance between the two vectors.
double Vector::euclideanDistance(Vector other) {
     return minkowskiDistance(other, 2);
    }


/// @brief Manhattan_Distance recieves another Vector and calculates the Manhattan distance between this and the other vector.
/// @param other 
/// @return Manhattan distance between the two vectors.
double Vector::manhattanDistance(Vector other) {
        return minkowskiDistance(other, 1);
    }


/// @brief Canberra_Distance recieves another Vector and calculates the Canberra distance between this and the other vector.
/// @param other 
/// @return Canberra distance between the two vectors.
double Vector::canberraDistance(Vector other) {
        vector<double> u = other.getVector();
        double sum = 0, numerator, denominator, temp1, temp2;
        for (int i = 0; i < u.size(); i++) {
            numerator = abs(vect[i] - u[i]); //calculating the numerator
            temp1 = abs(vect[i]);
            temp2 = abs(u[i]);
            denominator = temp1 + temp2;  //calculating the denominator
            if (denominator == 0) {
                sum += 0;
            }
            else {
                sum += (numerator / denominator);
            }
        }
    return sum;
    } 


/// @brief Chebyshev_Distance recieves another Vector and calculates the Chebyshev distance between this and the other vector.
/// @param other 
/// @return Chebyshev distance between the two vectors.
double Vector::chebyshevDistance(Vector other) {
     double max = 0;
    vector<double> u = other.getVector();
    for(int i = 0; i < u.size(); ++i) {
        if(max < abs(vect[i] - u[i])) {
            max = abs(vect[i] - u[i]);
         }
     }
    return max;
  }


/// @brief Minkowski_Distance recieves another Vector and calculates the Minkowski distance between this and the other vector.
/// @param other 
/// @param p 
/// @return Minkowski distance between the two vectors.
double Vector::minkowskiDistance(Vector other, double p) {
    vector<double> u = other.getVector();
    double sum = 0, temp;
    for (int i = 0; i < u.size(); ++i) {
        temp = abs(vect[i] - u[i]);
        sum += pow(temp, p);
    }
    return pow(sum, (1/p));  //pow by 1/p is equal to the p root
}  


/// @brief calcPrec recieves a real number and calculates the length of the number after the decimal point.
/// @param num 
/// @return length of the number after the decimal point until the last non-zero digit.
int Vector::calcPrec(double num) {
    ostringstream straeamObj;
    straeamObj.precision(16);
    straeamObj << fixed << num;
    string digits;
    int start, end, len;
    digits = straeamObj.str();
    start = digits.find('.');
    end = digits.find_last_not_of('0');
    len = digits.substr(start, end - start).length();
    return len;
}

    
/// @brief Default constructor of the Vector class.
Vector::Vector() {}


/// @brief  Constructor of the Vector class. recieves a vector (from the vector library) and initializes the field of the class with the given vector.
/// @param v 
Vector::Vector(vector<double> v) { 
    vect = v; 
}


/// @brief Overloading the operator '=' for the Vector class. Basically a copies a given Vector to a new one.
/// @param other 
/// @return New Vector object.
Vector& Vector::operator = (const Vector& other) {
    vect = other.vect;
    return *this;
}


/// @brief getVector returns the field of the class.
/// @return vector field of the class.
vector<double> Vector::getVector() {
    return vect;
}


/// @brief getSize returns the size of the vector field.
/// @return ize of the vector field.
int Vector::getSize() {
     return vect.size();
}


/// @brief printDistances recieves another Vector type variable and prints all the distances between the current vector and the other one. It also checks if a specific distance is a whole number and thus, prints the relevant number of digits after the decimal dot.
/// @param other 
void Vector::printDistances(Vector other) {
    vector<double> dist; // initialize a vector that will store the distances.
    int prec;
    dist.push_back(euclideanDistance(other));
    dist.push_back(manhattanDistance(other));
    dist.push_back(chebyshevDistance(other));
    dist.push_back(canberraDistance(other));
    dist.push_back(minkowskiDistance(other, 2));
    for(int i = 0; i < dist.size(); ++i) {
        prec = calcPrec(dist[i]); // precision of decimal dot.
        if(!prec) {
            cout.precision(1);
        } else {
            cout.precision(prec); // set the precision.
        }
        cout << fixed << dist[i] << endl;
    }
}


/// @brief getDistance calculates the distance between this Vector and another Vector based on the given distance metric.
/// @param other 
/// @param id 
/// @return distance between the Vectors basd on the given distance metric.
double Vector::getDistance(Vector other, string id) {
    map<string, double> distanceMap = {
        {"AUC", other.euclideanDistance(vect)},
        {"MAN", other.manhattanDistance(vect)},
        {"CHB", other.chebyshevDistance(vect)},
        {"CAN", other.canberraDistance(vect)},
        {"MIN", other.minkowskiDistance(vect, 2)}
    };     
    return distanceMap[id];
}




 