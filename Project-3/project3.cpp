#include <iostream>
#include <fstream>
#include "SparseMatrix.h"
using namespace std;

int main(int argc, char **argv) {
    SparseMatrix m1, m2, m;
    ifstream infile1(argv[2]), infile2(argv[3]);
    m1.constructor=0;
    m2.constructor=0;
    m.constructor=0;

    string op(argv[1]);
     if (op=="mul") {
        m2.constructor=1;
        infile1 >> m1;
        infile2 >> m2;

        infile1.close(); infile2.close();

        m=m1*m2;}
    else    if (op=="add"){
                     infile1 >> m1;
                             infile2 >> m2;

                                     infile1.close(); infile2.close();

            
            m=m1+m2;
        }
        else if (op=="sub"){ 
                 infile1 >> m1;
                         infile2 >> m2;

                                 infile1.close(); infile2.close();

        
        m=m1-m2;}


        else {
            cerr << "No such operation" << endl;
            return 1;
        }

        ofstream outfile(argv[4]);

        outfile << m;


        outfile.close();
        return 0;
}
