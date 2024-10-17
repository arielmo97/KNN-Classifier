
#include "ArgsValidity.h"


/// @brief Prints an error message in case an invalid argument was passed to the program.
void printArgsErr() {
    cout << "Invalid arguments passed.";
    cout << "Terminating the program." << endl;
    return;
}


/// @brief Checks if exactly arguments were passed to the program.
/// @param argc 
/// @return true or false.
bool argsLength(int argc, int from) {
    if (from == 1) {
        return (argc == 2);
    }
    return (argc == 3);
}


/// @brief Checks if the distance metric that was passed to the program is a valid one.
/// @param s 
/// @return true or false.
bool isValidMetric(string s) {
    map<string, int> metrics = {{"AUC", 0}, {"MAN", 0}, {"CHB", 0}, {"CAN", 0}, {"MIN", 0}};
    if(metrics.find(s) == metrics.end()) { // check if the given metric exists in metric map.
        return false;
    } else {return true;}
}


/// @brief checks if the 'K' of the KNN algorithm is valid number.
/// @param k 
/// @param dataSize 
/// @return true or false.
bool isValidK(string k, int dataSize) {
    int num;
    try {
        num = stoul(k); // check if 'K' is an integer.
    }
    catch (invalid_argument) {
        return false;
    }
    if (num < 1) { // check if 'K' is positive.
        return false; 
    }
    if (to_string(num) != k) { // check if the passed 'K' is a "pure number".
        return false; 
    }
    if (0 < dataSize && dataSize < num) { // check if the passed 'K' is not too big.
        return false;
    }
    return true;
}










