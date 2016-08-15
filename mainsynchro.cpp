#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>
#include <algorithm>
#include "Efielder.h"
#include "linearpolate.h"
#include "fft.h"
#include "modconclude.h"
#include "vectorsaver.h"
#include "matrixSaver.h"
#include <time.h>
#define SWAP(a,b) tempr=(a);(a) = (b); (b) = tempr

using namespace std;


 main(int argc,char* argv[])
{
//double synchrotronRadius = 10;
//double startingBeta = .9;
//double sampleFrequency = 20;//technically finds every frequency in the range
//double tSteps = 8; // arbitrary other than 2^n

double nParticles = atof(argv[1]);

time_t firstTime;
time_t secondTime;



firstTime = time(NULL);

double ten = 10;
double eight = 8;
//double c = 3*pow(ten,eight);
double c = 299792458;
double tSteps = 20000;
double starttime = -800e-15;
double endtime = 800e-15;
double simulationTime = endtime-starttime;
double dt = simulationTime/tSteps;
//global dt is being a poop


cout<<" the total timeSteps in this run are "<<tSteps<<endl;
cout<<" input step size is "<<dt<<endl;


vector<vector<vector<vector<double> > > > EfieldMatrix;

//double (*measurements) [3][tSteps] = new double[100][3][tSteps] ;
vector<vector<vector<vector<double> > > > measurements;

vector<vector<vector<double> > > newEfield;
vector<vector<vector<complex<double > > > > fouriered;
vector<vector<double> > finalW;
vector<double> sampleW;

//EfieldMatrix = mainParametrizeLinear(startingBeta, synchrotronRadius,tSteps,dt);
EfieldMatrix = mainParametrize(tSteps,dt,measurements,nParticles);
//cout<<measurements[1][1][1]<<endl;
  vector<double> vectorSave;
  vector<vector<double> > matrixSave;
char EString[100]; 
sprintf(EString,"%s", "Edump.txt");


double Edimensions = 100;
double Esavedim = 300;
vector<double> fvector;
vector<vector<double> >  svector;

newEfield = mainLinearpolate(EfieldMatrix, tSteps,dt,measurements,nParticles);

vector<vector<double > > sizetwo = newEfield[1];
vector<double> sizeone = sizetwo [1];

cout<<"third dimension size :"<<newEfield.size()<<endl<<"second dimension size :"<<sizetwo.size()<<endl;
cout<<"first dimension size :"<<sizeone.size()<<endl;  
double Elength = sizeone.size();

for  (int findex = 0; findex<Elength ; findex++)
	{
	for(int sindex = 0; sindex < Edimensions; sindex++)
		{
		for(int tindex = 0 ; tindex < 3; tindex++)
			{
//cout<<findex<<" "<<sindex<<" "<<tindex<<endl;
//			fvector.push_back(measurements[sindex][tindex][findex]);
                        fvector.push_back(newEfield[sindex][tindex][findex]);

			}

		}	
svector.push_back(fvector);
fvector.clear();
	}
matrixSaver(svector,EString,Elength,Esavedim);
tSteps = Elength; //need to dynamicise this eventually
fouriered = mainFft(newEfield,tSteps);
finalW = mainConclude(fouriered,tSteps);

double WTotals = 0;

for(int q = 0;q<150;q++)
{
if ( (q % 1)== 0)
{
for (int o = 0;o<100; o++)
{
//cout<<endl<<finalW[o][q]<<endl;
WTotals = WTotals + finalW[o][q];
}
sampleW.push_back(WTotals);
WTotals = 0;
}
}
//cout<<"gets to here"<<endl;
//vectorSaver(sampleW,"sampleW.dat", 150);//for the frequency spectrum

double timelength = tSteps/2;
double dimensions = 100;
char filestring[100] = "fulldump.txt";
matrixSaver(finalW,filestring,dimensions,timelength);



//vectorSaver(sampleW,"sampleW.dat", 100);//for the radial distribution
secondTime = time(NULL);
cout<<"this simulation took "<<secondTime-firstTime<<" seconds"<<endl;
 return (EXIT_SUCCESS);
}






