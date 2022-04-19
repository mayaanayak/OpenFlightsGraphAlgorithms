#include "makeGraph.h"
#include "parseDat.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main() {

  // check if data works
  ofstream ofs;
  ofs.open("output.txt"); // output file
  if (ofs) {
   makeGraph mkg;
    // ofs << mkg.getAirports(5).airportID << endl;
    // ofs << mkg.getAirports(5).latitude << endl;
    // ofs << mkg.getAirports(5).longitude << endl;
    vector<vector<double>> vect = mkg.getGraph();

    for (size_t i = 0; i < vect.size(); i++) {
      for (size_t j = 0; j < vect.size(); j++) {
    //     // cout<<vect[i][j] << "<--" <<endl;
        ofs << vect[i][j] << " ";
    //     // cout<<"here in" <<endl;
      }
    //   // cout<<""<<endl;
      ofs << endl;
     }
    ofs.close();
  } else {
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }

  return 0;
}