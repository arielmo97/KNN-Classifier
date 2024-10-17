
#include "FileIntegrity.h"
using namespace std;


/// @brief fetchStrings recieves a .csv file and extracts each row of the file into a vector of strings.
/// @param fileName 
/// @return A vector of strings.
vector<string> fetchStrings(string fileName) {
    fstream stream;
    stream.open(fileName); // try to open the file.
    if(stream.fail()) {
        cout << "Unable to open " << fileName << ". Terminating the program.";
        exit(1); // terminate program if failed to open file.
    }

    vector<string> rows;
    while(stream.peek() != EOF) {
        string row;
        getline(stream, row, '\n');
        rows.push_back(row); // extract row by row.
    }
    stream.close(); // finished reading, close the file.
    return rows;
}


/// @brief prints an error message if corrupted data was detected in the given file.
void fileIntegrityErr() {
    cout << "File integrity warning: The given file contains corrupted data." << endl;
    cout << "Terminating the program." << endl;
    return;
}


/// @brief nameFound recieves a list of vectors as strings and ensures that each vector has a "name" attached to it.
/// @param ls 
/// @return true or false.
bool nameFound(list<string>& ls) {
    double num;
    try {
        num = stod(ls.back());
        return false;
    } catch (invalid_argument) {
        return true;
    }
}


/// @brief checkLength recieves the database which was extraacted from the given file and checks if all the vectors in the file are from the same dimension.
/// @param data 
bool checkLength(vector<tuple<Vector, string>>& data) {
    vector<tuple<Vector, string>>::iterator it;
    it = data.begin();
    int size = get<0>(*it).getSize();
    ++it;
    while(it != data.end()) {
        if (get<0>(*it).getSize() != size) {
            return false;
        }
        ++it;
    }
    return true;
}


/// @brief checkLengthUnclssfd recieves the database of unclassified vectors which was extraacted from the given file and checks if all the vectors in the file are from the same dimension.
/// @param data 
/// @return 
bool checkLengthUnclssfd(vector<Vector>& data) {
    vector<Vector>::iterator it = data.begin();
    int size = (*it).getSize();
    ++it;
    while(it != data.end()) {
        if((*it).getSize() != size) {
            return false;
        }
        ++it;
    }
    return true;
}


/// @brief convertToTuple recieves a single row from the .csv file and converts it to a tuple of a vector of real numbers and the "name" of the vector.
/// @param row 
/// @return 
tuple<Vector, string> convertToTuple(string row) {
    list<string> ls = seperateElements(row, ',');
    while(ls.back() == "\r") { // remove trailing blanks.
        ls.pop_back();
    }
    if (!nameFound(ls)) { // check if vector is classified.
        fileIntegrityErr();
        exit(1);
    }
    string vecName = ls.back();
    ls.pop_back();
    list<string> tmpList = appendZero(ls);
    ls.swap(tmpList);
    if(!isDouble(ls)) { // check if the vector contains only real numbers.
        fileIntegrityErr();
        exit(1);
    }
    vector<double> tmp;
    list<string>::iterator it;
    for(it = ls.begin(); it != ls.end(); ++it) {
        tmp.push_back(stod(*it)); // convert to double and push into the vector.
    }
    Vector v(tmp);
    return make_tuple(v, vecName);
}


/// @brief fetchData recieves a .csv file and prepares a database which contains the content of the file.
/// @param fileName 
/// @return vector<tuple<Vector, string>>
vector<tuple<Vector, string>> fetchData(string fileName){
    vector<string> rows = fetchStrings(fileName);
    vector<tuple<Vector, string>> data;
    for(string row: rows) {
       tuple<Vector, string> records = convertToTuple(row);
       data.push_back(records);
    }
    checkLength(data);
    return data;   
}






    

