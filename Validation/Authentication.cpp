
#include "Authentication.h"





/// @brief  Remove_Blanks recieves a string and removes the leading and trailing blanks of the given string.
/// @param s 
/// @return  a substring without the blanks.
string removeBlanks(string s) {
    int i = s.find_first_not_of(' '); // find index of the first non-blank character.
    int j = s.find_last_not_of(' '); // find index of the last non-blank character.
    string x = s.substr(i, j-i+1); // extract relevant substring.
    return x;
}


/// @brief Elements recieves a string of numbers seperated by blanks and creates a string list of those numbers.
/// @param s 
/// @param token 
/// @return a list of numbers as strings.
list<string> seperateElements(string s, char token) {
    list<string> ls;
    string collector = ""; // the collector will collect all the character of a single number.
    s.push_back(token);
    for(int i = 0; i < s.length(); ++i) {
        if(s[i] == token) {
            ls.push_back(collector); // add the number to the list of strings.
            collector = "";
            continue;
        }
        else {
            collector.push_back(s[i]); // concatenate the string to the collector.
        }
    }
    ls.remove("");
    return ls;
}


/// @brief containsLetters recieves a string and checks if it contains at most one letter. In case of no letters - returnes 0. In case of one letter - returns 1. In case of at least 2 letters - returns -1.
/// @param curr 
/// @return true or false.
int isFormatE(string curr) {
    bool found = false;
    int count = 0;
    int index;
    for(int i = 0; i < curr.length(); ++i) {
        if(isalpha(curr[i])) {
           count++;
           if(curr[i] == 69) {
            found = true;
            index = i;
           }
        }
    }
    if(found && count == 1 && 0 < index && index < curr.length() - 2) {
        return index;
    }
    if(count == 0) {
        return 0;
    }
    return -1;
}


/// @brief  Is_Double recieves a list of strings and checks if all the elements are real numbers.
/// @param ls 
/// @return true or false.
bool isDouble(list<string> ls) {
   string curr;
   int count = 0;
   bool eFormat = false; // indicator for 'E' format.
   list<string>::iterator it = ls.begin();
    while(it != ls.end()) {
        curr = *it;
        int index = isFormatE(curr);
        if(index < 0) {
            return false;
        }
        if(index > 0) {
            eFormat = true;
            if(curr[index + 1] != 45) {return false;}
        }
        if((curr[0] < 48 && curr[0] != 45) || curr[0] > 57) { // check first char of string.
            return false;
        }
        for(int i = 1; i < curr.length(); ++i) {
            if(eFormat && (i == index || i == index + 1)) {
                continue;
            }
            if((curr[i] < 48 && curr[i] != 46) || curr[i] > 57) {
                return false;
            } else {
                if(curr[i] == 46) { // increment the counter if a dot was spotted.
                    count++;
                }
            }
        }
        if(count > 1) { // if more than one decimal dot were spotted in the string.
            return false;
        }
        eFormat = false;
        count = 0;
        ++it;
    }
    return true;
}


/// @brief appendZero appends 0 to all the strings in the list that begin with a decimal dot.
/// @param ls 
/// @return list of strings
list<string> appendZero(list<string> ls) {
    list<string> tmp;
    string curr;
    list<string>::iterator it;
    for(it = ls.begin(); it != ls.end(); ++it) {
        curr = *it;
        if(curr[0] == 45 && curr[1] == 46) { // check if string begins with "-."
            string num = curr.substr(1);
            string withZeroNeg = "-0";
            withZeroNeg.append(num);
            tmp.push_back(withZeroNeg);
        }
         else if(curr[0] == 46) { // check if string begins with dot.
            string withZero = "0";
            withZero.append(curr); // append 0 to beginning of string.
            tmp.push_back(withZero);
        } else {
            tmp.push_back(curr);
        }
    }
    return tmp;
}


/// @brief Authenticate_Input recieves a string and authenticates the input (checks if the input is a valid input of a string that contains real numbers). The function uses its auxilliary functions (mentioned above) to deter whether the input is valid or not.
/// @param s 
/// @param token 
/// @return true or false.
bool authenticateInput(string s, char token) {
    if(!s.length()) {
        return false;
    }
    string x = removeBlanks(s);
    list<string> ls = seperateElements(x, token);
    list<string> tmpList = appendZero(ls);
    ls.swap(tmpList);
    if(!isDouble(ls)) {
        return false;
    }
    return true;
}


/// @brief Make_Vector recieves a string of real numbers that has already been authenticated and creates a vector (from the vector library) that stores those numbers.
/// @param s 
/// @param token 
/// @return vector that store the given numbers.
vector<double> makeVector(list<string> ls) {
    vector<double> v;
    double num;
    list<string>::iterator it; // initialize a list iterator.
    for(it = ls.begin(); it != ls.end(); ++it) {
        num = stod(*it); // convert the number data type from string to double.
        v.push_back(num); 
    }
    return v;
}