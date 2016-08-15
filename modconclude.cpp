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

vector<vector<double> > mainConclude(vector<vector<vector<complex<double> > > > fouriered,double tSteps)
{

int obsPoints = 100;
vector<double> wAtPoint;
double totalAtPoint = 0;
vector<vector<double> > finalW;

for (int n = 0; n < obsPoints ; n++)
{
for(int w = 0; w < tSteps/2; w++)
{
for (int i = 0; i < 3;i++)
{
//cout<<w<<endl;

totalAtPoint = totalAtPoint + abs(fouriered[n][i][w])*abs(fouriered[n][i][w]);
//cout<<abs(fouriered[n][i][w])*abs(fouriered[n][i][w])<<endl;
}
//totalAtPoint = abs(fouriered[n][1][w])*abs(fouriered[n][1][w]);//just the parallel polarization
//totalAtPoint = sin(3.14*(obsPoints-n)/obsPoints)*abs(fouriered[n][2][w])*abs(fouriered[n][2][w]) + abs(cos(3.14*obsPoints-n)/obsPoints)*abs(fouriered[n][0][w])*abs(fouriered[n][0][w]); 
wAtPoint.push_back(totalAtPoint);
totalAtPoint = 0;
//cout<<wAtPoint.size()<<endl;
//cout<<wAtPoint[5000];
}
finalW.push_back(wAtPoint);
wAtPoint.clear();
//cout<<finalW.size()<<endl;

}


return(finalW);

}
