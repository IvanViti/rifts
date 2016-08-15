#ifndef LINEARPOLATE_H
#define LINEARPOLATE_H

using namespace std;

extern double dt;

vector<double> linterpolating(vector <double> oneVector, vector<double>interpolated, vector<vector<vector<vector<double> > > > EfieldMatrix, int t,int n, int i, double dt, vector<vector<vector<vector<double> > > > & measurements,double midstep,double goodstep,double tSteps,double nParticles,int p);

vector<double> linterpolating2(vector <double> oneVector, vector<double>interpolated, vector<vector<vector<vector<double> > > > EfieldMatrix, int t,int n, int i, double dt, vector<vector<vector<vector<double> > > > & measurements,double midstep,double goodstep,double tSteps,double nParticles,int p);



vector<double> Tcreator(double tSteps,double dt);

vector<vector<vector<double> > >  mainLinearpolate(vector<vector<vector<vector<double> > > > EfieldMatrix,double tSteps,double dt,vector<vector<vector<vector<double> > > > & measurements,double nParticles);

double findmin(vector<vector<vector<vector<double> > > > & measurements,double tSteps, vector<vector<double> > & centralstep);


#endif

