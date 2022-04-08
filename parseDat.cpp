#include "parseDat.h"
#include <fstream>
#include <sstream>

using std::ifstream;
using std::ostream;
using std::cout;
using std::endl;

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
    std::stringstream sstr(str);
    vector<string> v;
    while(sstr.good())
    {
        string substr;
        getline(sstr, substr, ',');
        v.push_back(substr);
    }
    return v;
}

//creates and returns 2-D vector. public function. 
vector<vector<string>> parseData::getDataVector(string file) {
    fileToVect(file);
    vectorToTwoDimension();
    return csvInTwoDimension;
}