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