#include <iostream>
#include <fstream>
#include "maxPlanarSubset.h"
using namespace std;

void help_message() {
    cout << "usage: mps <input_file_name> <output_file_name>" << endl;
}

int main(int argc, char* argv[])
{
    if(argc < 3 || argc > 3) {
       help_message();
       return 0;
    }

    MpsSolver *mpss = new MpsSolver();

    //here we will read the input files
    fstream fin;
    fstream fout;
    fin.open(argv[1],ios::in); //reading
    if (!fin) return 1;
    fout.open(argv[2],ios::out); //writing
    if (!fout) return 1;

    //go ahead and get the size
    int v,zero;
    zero = 0;
    fin>>v;
    mpss->setVerticeNum(v);

    //now we should get a blank arrays
    mpss->buildArray();

    //now fill in the values to the array
    mpss->fillArray(fin);
    fin.close();

    v--;
    //value of the maximum planar subset
    int MPSdaAn = mpss->maxPlanarSubset(zero, v);
    fout << MPSdaAn <<endl;

    //path for the maximum planar subset
    mpss->getPlanarSubset(zero, v);
    mpss->printLines(fout);
    fout.close();

    //remember to delete
    delete mpss;
    return 0;
}