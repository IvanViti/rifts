
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

void matrixSaver (vector<vector <double> > totals, char *  fileName ,double xSteps, double ySteps)
{
FILE * pFile;
pFile = fopen(fileName,"w");
float holder;
for (int i = 0; i <xSteps ; i++)
	{	
	for(int j = 0;j< ySteps;j++)
		{holder = totals[i][j];
//cout<<endl<<holder<<endl;
		fprintf(pFile," %f", holder);
		}
	fprintf(pFile,"\n");
	}

}


