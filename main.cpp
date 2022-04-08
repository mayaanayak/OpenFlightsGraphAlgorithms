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
        // int count = 0;
        for (auto v : vect) {
            // ofs << count << " ";
            for (auto str : v) {
                ofs << str << " ";
            }
            ofs << "" << endl;
        }
        ofs.close();
    } else {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
   
    return 0;
}