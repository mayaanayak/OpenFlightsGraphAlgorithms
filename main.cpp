#include "parseDat.h"
#include <fstream>
#include <cstdlib> 

using std::cout;
using std::endl;
using std::ofstream;
using std::cerr;


int main() {

    //check if data works
    ofstream ofs;
    ofs.open("output.txt"); //output file
    if (ofs) {
        parseData pdt;
        vector<vector<string>> vect = pdt.getDataVector("dataset/airports.dat");
        ofs << vect[0][1] << endl;
        ofs << vect[0][2] << endl;
        ofs << vect[0][3] << endl;
        ofs << vect[0][4] << endl;
        ofs << vect[0][5] << endl;
        ofs << vect[0][6] << endl;
        ofs << vect[0][7] << endl;
        ofs.close();
    } else {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
   
    return 0;
}