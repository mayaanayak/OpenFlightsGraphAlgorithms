#pragma once
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class parseData {
    public:
        parseData();
        vector<vector<string>> getDataVector(string file); //convert a string file to a vector of type string
    private:
        void fileToVect(const string& file); //parse a csv file to a vector of type string
        void vectorToTwoDimension(); //convert vector from fileToVect into two-dimensions
        vector<string> splitString(string str); // split a string using "," delimiter

        vector<string> csvVector;
        vector<vector<string>> csvInTwoDimension;
};