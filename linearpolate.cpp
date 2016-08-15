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


vector<double> linterpolating(vector <double> oneVector, vector<double>interpolated, vector<vector<vector<vector<double> > > > EfieldMatrix,int t,int n, int i, double dt, vector<vector<vector<vector<double> > > > & measurements,double midstep,double goodstep,double tSteps,double nParticles,int p);


vector<double> linterpolating2(vector <double> oneVector, vector<double>interpolated, vector<vector<vector<vector<double> > > > EfieldMatrix,int t,int n, int i, double dt, vector<vector<vector<vector<double> > > > & measurements,double midstep,double goodstep,double tSteps,double nParticles,int p);



vector<double> Tcreator(double goodstep,double midstep);

double findmin(vector<vector<vector<vector<double> > > > & measurements,double tSteps, vector<vector<double> > & centralstep,double nParticles);

vector<vector<vector<double> > >  mainLinearpolate(vector<vector<vector<vector<double> > > > EfieldMatrix,double tSteps,double dt,vector<vector<vector<vector<double> > > > & measurements,double nParticles)
{
vector<vector<vector<double> > > newEfield;
vector<double > oneVector;//EfieldMatrix gets interpolated one vector at a time
vector<double > linterpolated;
vector<vector< double > > interpolatedObsPoint;
int q;
double obsPoints = 100;
vector<vector<double> >  centralstep ;
//cout<<"makes it into linterpolate"<<endl;
double minstep = findmin(measurements,tSteps,centralstep,nParticles);
//cout<<"gets past findmin "<< minstep<<endl;
//double goodstep = minstep/2;
double goodstep = minstep/2;
cout<<"output step size is "<<goodstep<<endl;
vector<double> stackedEr;

//double midstep = centralstep[1][1];
//double midstep = 0;
//double midstep = 3.33645e-09; //closest
double midstep = 3.336445e-09; //

//double midstep = 3.33564095e-9; //0 at 1 meter away lightwise
//cout<<goodstep<<" " <<midstep<<endl;
 oneVector = Tcreator(goodstep,midstep);
for (int t = 0;t <oneVector.size();t++)
{
stackedEr.push_back(0);
}



double t = 3;//too lazy to remove
cout<<"the maximum frequency measured at the detector is "<<.5/goodstep<<endl;
//double centralstep = mainstep; //to prevent confusion with minstep
for (int n = 0; n < obsPoints; n++)
{
for (int i = 0; i < 3 ; i++)
{
for (int p = 0 ;p < nParticles; p++)
{
//cout<<"gets to particle "<<p<<endl;
linterpolated =  linterpolating2(oneVector,linterpolated, EfieldMatrix,t,n,i,dt,measurements,midstep,goodstep, tSteps,nParticles,p);
//cout<<"the size of oneVector is "<<oneVector.size()<<endl;
//cout<<"the size of linterpolated is "<<linterpolated.size()<<endl;
for (int t = 0; t<oneVector.size();t++)
{
stackedEr[t] = stackedEr[t] + linterpolated[t];
}
//cout<<"at particle "<<p + 1<<" the Efield at t = 2 is "<<stackedEr[2]<<endl;

linterpolated.clear();

} 
//cout<<"the size of t when stacked is put in is "<<stackedEr.size()<<endl;
//cout<<"gets to here"<<endl;
interpolatedObsPoint.push_back(stackedEr);
stackedEr.clear();
for (int reset = 0;reset < oneVector.size(); reset++)
{
stackedEr.push_back(0) ;
}

}

newEfield.push_back(interpolatedObsPoint);
interpolatedObsPoint.clear();
}
return(newEfield);
}

vector<double> linterpolating(vector<double> oneVector, vector<double> interpolated,vector<vector<vector<vector<double> > > > EfieldMatrix, int t,int n, int i,double dt,  vector<vector<vector<vector<double> > > > & measurements,double midstep,double goodstep,double tSteps,double nParticles , int p)
{

//cout<<" got to observation point "<<n<<endl;

double beforetime = 999;
int bstep = 999;
double slope;
double yintercept;
double newVal;
for (int k = 0; k < tSteps ; k++)
	{
//	cout<<"time step "<<k<<endl;
//	cout<<"the first given step is "<<oneVector[0]<<endl;
//	cout<<"the first measurement is at"<< measurements[k][n][p][1]<<endl;
cout<<"is "<<measurements[k][n][p][1]<<" less than "<< oneVector[0]<<endl;
	if (measurements[k][n][p][1] < oneVector[0])
		{
		beforetime = measurements[k][n][p][1];
		bstep = k; 
cout<<"measurements do go that far back"<<endl;
		}
	}
if((bstep == 999) || (beforetime == 999))
	{
	cout<<measurements[0][n][p][1]<<" "<<oneVector[0]<<endl;
	cout<<"measurements dont go that far back at obs point "<<n<<endl;
	}
if(oneVector[oneVector.size()-1] > measurements[tSteps-1][n][p][1])
	{cout<<"measurements went too far at obs point "<<n<<endl;}
//so now i have to go through and get y values for all my onevector x's
for (double g = 0;g < oneVector.size() ; g++)
	{
	if (oneVector[g] > measurements[bstep + 1][n][p][1])
		{
		bstep = bstep + 1;
		} 

	
	slope = (EfieldMatrix[bstep+1][n][p][i] - EfieldMatrix[bstep][n][p][i])/(measurements[bstep+1][n][p][1] - measurements[bstep][n][p][1]);
	yintercept = EfieldMatrix[bstep][n][p][i] - slope*measurements[bstep][n][p][1];
	newVal = slope*oneVector[g] + yintercept;	
	interpolated.push_back(newVal);

	}
return(interpolated);
}

vector<double> linterpolating2(vector<double> oneVector, vector<double> interpolated,vector<vector<vector<vector<double> > > > EfieldMatrix, int t,int n, int i,double dt,  vector<vector<vector<vector<double> > > > & measurements,double midstep,double goodstep,double tSteps,double nParticles , int p)
{

//cout<<" got to observation point "<<n<<endl;

double beforetime = 999;
int bstep = 999;
double slope;
double yintercept;
double newVal;
measurements[0][n][p][1] = -800;
measurements[tSteps-1][n][p][1] = 800;
for (int fix = 0; fix < 3 ; fix++)
{
	EfieldMatrix[0][n][p][fix] = 0;
	EfieldMatrix[tSteps-1][n][p][fix] = 0;
}
for (int k = 0; k < tSteps ; k++)
        {
        if (measurements[k][n][p][1] < oneVector[0])
                {
                beforetime = measurements[k][n][p][1];
                bstep = k;
             }
        }
if((bstep == 999) || (beforetime == 999))
        {
        cout<<measurements[0][n][p][1]<<" "<<oneVector[0]<<endl;
        }
if(oneVector[oneVector.size()-1] > measurements[tSteps-1][n][p][1])
        {cout<<"measurements went too far at obs point "<<n<<endl;}
//so now i have to go through and get y values for all my onevector x's
for (double g = 0;g < oneVector.size() ; g++)
        {
//cout<<"gets to real time point "<<g<<endl;
        if (oneVector[g] > measurements[bstep + 1][n][p][1])
                {
                bstep = bstep + 1;
                }


        slope = (EfieldMatrix[bstep+1][n][p][i] - EfieldMatrix[bstep][n][p][i])/(measurements[bstep+1][n][p][1] - measurements[bstep][n][p][1]);
        yintercept = EfieldMatrix[bstep][n][p][i] - slope*measurements[bstep][n][p][1];
        newVal = slope*oneVector[g] + yintercept;
        interpolated.push_back(newVal);

        }
return(interpolated);
}



vector<double> Tcreator(double goodstep,double midstep)
{
vector<double> oneVector;
// double dt;
//cout<<dt<<endl;
double retardsteps =1024;
double retardtime;
for (double x = 0;x<retardsteps;x++)
{
retardtime = midstep + (goodstep*x - goodstep*retardsteps/2);
oneVector.push_back(retardtime);
//cout<<retardtime<<endl;
}
return(oneVector);
}


double findmin(vector<vector<vector<vector<double> > > > & measurements,double tSteps,vector<vector<double> > & centralstep,double nParticles)
{

vector <double> centralv1;
double minVal = 1000;
double obsCentral;
double obsMin = 1000;
double difference;
for (int p = 0; p <nParticles; p++)
	{
  for (int n=0; n<100; n++)
  	{
	for (int t=0; t<(tSteps - 1); t++)
    		{
		difference = measurements[t+1][n][p][1] - measurements[t][n][p][1];
		if (difference <minVal)
			{	
			obsCentral = measurements[t][n][p][1];
			minVal = difference;
			}			
			
		}
//        centralstep.push_back(obsCentral);
	centralv1.push_back(0);
	}
centralstep.push_back(centralv1);
centralv1.clear();
}
return minVal;
}

