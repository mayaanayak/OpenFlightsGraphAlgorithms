#include "parseDat.h"
#include <fstream>
#include <cstdlib> 
#include "makeGraph.h"

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
        ofs << vect[3069][6] << " " << vect[3069][7] << endl;
        // int count = 0;
        // for (auto v : vect) {
        //     // ofs << count << " ";
        //     for (auto str : v) {
        //         ofs << str << " ";
        //     }
        //     ofs << "" << endl;
        // }
        ofs << vect[0][1] << endl;
        ofs << vect[0][2] << endl;
        ofs << vect[0][3] << endl;
        ofs << vect[0][4] << endl;
        ofs << vect[0][5] << endl;
        ofs << vect[0][6] << endl;
        ofs << vect[0][7] << endl;
        makeGraph mkg;
        //ofs << mkg.getAirports(5).airportID << endl;
        ofs << mkg.getAirports(5).latitude << endl;
        //ofs << mkg.getAirports(5).longitude << endl;

        ofs.close();
    } else {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
   
    return 0;
    
}