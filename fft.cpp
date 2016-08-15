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

vector<complex<double> > bitReversal(vector<complex<double> > data, int nValues);

vector<complex< double> > DLpart(vector<complex<double> > data,int nValues);

double mypow(double numOne, double numTwo);

vector<vector<vector<complex<double> > > > mainFft(vector<vector<vector<double > > > newEfield,double tSteps)
{
vector<complex <double> > input;
vector<complex <double> > output;
vector<vector<complex<double > > > fourieredObs;
vector<vector<vector<complex<double > > > > fouriered;
vector<vector<vector<complex<double > > > > transformed;
vector<vector<complex<double > > > twodfouriered;
vector<complex <double> > onedfouriered;

vector<double> sampleSpace;
double obsPoints = 100; //should be called or global
double y;
double nValues = tSteps;
double simulationTime = 1; //arbitrary for now
for (int n = 0; n < obsPoints ; n++)
{
for (int i = 0; i < 3;i++)
{
for (double t = 0;t < tSteps;t++)
{

y = newEfield[n][i][t];

input.push_back(complex<double>(y,0));
//cout<<y<<endl;
}
input = bitReversal(input,tSteps);
output = DLpart(input,nValues); //only aesthetic reason to do output instead of input again
input.clear();
fourieredObs.push_back(output);

}
transformed.push_back(fourieredObs);
fourieredObs.clear();
}
//theres probably an easier way to cut transformed in half timewise
for (int n = 0; n < obsPoints ; n++)
{
for (int i = 0; i < 3;i++)
{
for(int w = 0 ; w < tSteps/2 ; w++)//technically w (kinda until its combined with 1/t)
{
//cout<<w<<endl;
onedfouriered.push_back(transformed[n][i][w]);
}
twodfouriered.push_back(onedfouriered);
onedfouriered.clear();
}
fouriered.push_back(twodfouriered);
twodfouriered.clear();
}

return (fouriered);

}

vector<complex<double> > bitReversal(vector<complex<double> > data, int nValues)
{vector<double> checklist;
for(int h = 0;h<nValues;h++)
{
checklist.push_back(0);
}
int max = nValues;
int toggle = 0;
complex<double> temp;
int j; //will be the bitreversed index
int a;
for(int i = 0; i< nValues; i++)
{max = nValues;
j = 0;
a = i;
while (a )
{j <<= 1;
j |= a & 1;
a >>= 1;
max >>=1;
}
max>>=1;
while(max)
{
max>>=1;
j<<=1;
}
if (checklist[i] == 0)
{// cout<<"gets into here"<<endl;
temp = data[i];
data[i] = data[j];
data[j] = temp;
checklist[j] = 1;
}
toggle=0;
}
return(data);
}


vector<complex< double> > DLpart(vector<complex<double> > data,int nValues)
{
double element = 0;
double p = log(nValues)/log(2);
//cout<<p<<endl;
complex<double> temp;
complex<double>  W;
double pi = 3.1415926535;
double o;
double N;
complex<double> im (0,1);
complex<double> two (2,0);
for(int i = 0; i < p; i++)

{for(int k = 0; k < nValues/(mypow(2,(i+1))) ; k++)
{for(int j = 0; j < nValues/mypow(2,p-1-i); j++)// not sure why p-1-i 

{
//cout<<j<<endl;
if (j<mypow(2,i))
{//top wing
o = j;
N = mypow(2,i+1);
W = exp(-2*pi*im*o/N);
data[element] = data[element] + W*data[element + mypow(2,i)];
//cout<<element<<" "<<j<<endl;
//cout<<pow(2,i)<<endl;
element++;
}
if (j>= mypow(2,i))
{//bottom wing
o = j-mypow(2,i);
N = mypow(2,i+1);
W = exp(-2*pi*im*o/N);
data[element] = data[element-mypow(2,i)] - two*W*data[element]; //easier than having 2 copies
//cout<<element<<" "<<i<<endl;
//cout<<pow(2,i)<<endl;
element++;
}
//cout<<element<<endl;
}
}
//cout<<element<<endl;
element = 0;
}
return(data);
}



double mypow(double numOne,double numTwo)
{
return(pow(numOne,numTwo));
}
