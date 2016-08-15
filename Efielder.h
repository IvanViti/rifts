#ifndef PARAMETRIZE_H
#define PARAMETRIZE_H

using namespace std;

extern double dt;

vector<vector<vector<vector<double> > > > EfieldCalculator(vector<vector<vector<double> > > positions , vector<vector<vector<double> > > velocities, vector<vector<vector<double> > > accelerations, double obsPoints,  vector<vector<double > > observation,double tSteps, vector<vector<vector<double> > > & measurements, double dt,double nParticles);

 void crossProducter(double* vector1, double* vector2,double vector3[] );

 double normalizer (double* vector);

void parser(double nParticles,int tSteps,char *  fileName,char * timeFile, vector<vector<vector<double> > > & positions, vector<vector<vector<double > > > & velocities, vector<vector<vector<double > > > & accelerations,vector<double > & timevector);

void parser2(double nParticles,int tSteps,char *  fileName,char * timeFile, vector<vector<vector<double> > > & positions, vector<vector<vector<double > > > & velocities, vector<vector<vector<double > > > & accelerations,vector<double > & timevector);

vector<vector<double > > observationPoints(int nPoints, double radius);

vector<vector<vector<vector<double> > > >  mainParametrize(double tSteps,double dt,vector<vector<vector<vector<double> > > > & measurements,double nParticles);
#endif


