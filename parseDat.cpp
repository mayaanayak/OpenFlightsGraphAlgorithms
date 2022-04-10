#include "parseDat.h"
#include <fstream>
#include <sstream>

using std::ifstream;
using std::ostream;
using std::cout;
using std::endl;
using std::getline;

parseData::parseData() {

}

//converts csv file into 1 D vector
void parseData::fileToVect(const string& file) {
    ifstream ifs(file);
    string str;
    while (getline(ifs, str)) {
        csvVector.push_back(str);
    }
    ifs.close();
}

//takes the 1 D vector and converts it into 2D
void parseData::vectorToTwoDimension() {
    for (string& str : csvVector) {
        csvInTwoDimension.push_back(splitString(str));
    }
}   

//splits the string 
vector<string> parseData::splitString(string str) {
    // std::stringstream sstr(str);
    vector<string> v;
    // while(sstr.good())
    // {
    //     string substr;
    //     getline(sstr, substr, ',');
    //     v.push_back(substr);
    // }
    // return v;

    string line; 
    std::stringstream sstr(str);
    while (getline(sstr, line)) {        // read full line
        const char *mystart = line.c_str();    // prepare to parse the line - start is position of begin of field
        bool instring{false};                
        for (const char* p = mystart; *p; p++) {  // iterate through the string
            if (*p == '"')                        // toggle flag if we're btw double quote
                instring = !instring;     
            else if (*p ==',' && !instring) {    // if comma OUTSIDE double quote
                v.push_back(string(mystart,p - mystart));  // keep the field
                mystart = p + 1;                    // and start parsing next one
            }
        }
        v.push_back(string(mystart));   // last field delimited by end of line instead of comma
    }
    return v;
}

//creates and returns 2-D vector. public function.
vector<vector<string>> parseData::getDataVector(string file) {
    fileToVect(file);
    vectorToTwoDimension();
    return csvInTwoDimension;
}