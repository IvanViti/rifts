
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>
#include <algorithm>


using namespace std;

void vectorSaver (vector <double> totals, string fileName,double xSteps)
{
string tmp =  string(fileName);

ofstream file;
    file.open ( tmp.c_str() );
    file.precision(6);
    file.setf(ios::fixed | ios::scientific);
    cout.precision(6);
    cout.setf(ios::fixed | ios::scientific);

for (int n = 0; n <xSteps ; n++)
{
file<<totals[n]<<" ";
}

}


