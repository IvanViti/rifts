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
vector<vector<double > > observationPoints(int nPoints, double radius);

vector<vector<vector<vector<double> > > >EfieldCalculator(vector<vector<vector<double> > >  positions,  vector<vector<vector<double> > >  velocities, vector<vector<vector<double> > >  accelerations, double obsPoints,  vector<vector<double > > observation,double tSteps, vector<vector<vector<vector<double> > > > & measurements, double dt,double nParticles);

double normalizer (double* vector);

void parser(double nParticles,int tSteps,char *  fileName,char * timeFile, vector<vector<vector<double> > > & positions, vector<vector<vector<double > > > & velocities, vector<vector<vector<double > > > & accelerations,vector<double > & timevector);

void parser2(double nParticles,int tSteps,char *  fileName,char * timeFile, vector<vector<vector<double> > > & positions, vector<vector<vector<double > > > & velocities, vector<vector<vector<double > > > & accelerations,vector<double > & timevector);

 void crossProducter(double* vector1, double* vector2,double vector3[] );

vector<vector<vector<vector<double> > > >  mainParametrize(double tSteps,double dt, vector<vector<vector<vector<double> > > >  & measurements,double nParticles)
{

//double nParticles = 64;
double c = 299792458;
char omnifile[100];
sprintf(omnifile,"%s", "omnifile.txt");

char timeFile[100];
sprintf(timeFile,"%s", "timefile.txt");


int timeSteps = tSteps; //apparently "new" doesnt like double
double radius = 1;
double nPoints = 100;//same thing as obsPoints
  vector<vector<vector<double> > > positions;
  vector<vector<vector<double> > > velocities;
  vector<vector<vector<double> > > accelerations;
  vector< vector < vector<vector< double> > > > EfieldMatrix;
//  vector< vector < vector< double> > > measurements; 
  vector<vector<double > > observation;
  vector<double> vectorSave;
  vector<vector<double> > matrixSave;

observation = observationPoints( nPoints, radius);

//  double thetaLength = 25*sqrt(1-startingBeta*startingBeta);

  double *times = new double[timeSteps];
vector<double> timevector;
parser2(nParticles,timeSteps, omnifile,timeFile,  positions,  velocities,  accelerations,timevector);
for (int t = 0;t < timeSteps; t++)
{ 
	times[t] = timevector.at(t);
}
double simulationTime = timevector[tSteps] - timevector[0];


EfieldMatrix = EfieldCalculator(positions,  velocities, accelerations, nPoints, observation,tSteps,measurements,dt,nParticles);

/*
for (int t = 0; t < tSteps; t++)
//for (int n = 0; n < nPoints; n++)

{
for (int q = 0; q < 3; q++)
{
vectorSave.push_back(EfieldMatrix[t][50][q]);
//vectorSave.push_back(observation[n][q]);
}
//cout<<vectorSave[0]<<endl;

//matrixSave.push_back(vectorSave);
//vectorSave.clear();
}
//int dimensions = 3;
//matrixSaver (matrixSave, dimensions, tSteps, "positionMatrix.dat");
//matrixSaver (matrixSave, dimensions, nPoints, "positionMatrix.dat");
*/
return(EfieldMatrix);

}




 void crossProducter(double* vector1, double* vector2,double vector3[] )
 {

    vector3[0] = vector1[1]*vector2[2] - vector1[2]*vector2[1];
    vector3[1] = vector1[2]*vector2[0] - vector1[0]*vector2[2];
    vector3[2] = vector1[0]*vector2[1] - vector1[1]*vector2[0];

 }


  double normalizer (double* vector)
 {
     double norm;
     norm = sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);

     return(norm);
 }

vector<vector<vector<vector<double> > > > EfieldCalculator(vector<vector<vector<double> > > positions, vector<vector<vector<double> > > velocities, vector<vector<vector<double> > > accelerations, double obsPoints,  vector<vector<double > > observation,double tSteps ,vector<vector<vector<vector<double> > > > & measurements, double dt,double nParticles)
{
double c = 299792458; 
  vector < vector < vector < vector < double > > > > v4d;
  vector < vector < vector < double> > > v3d;
  vector< double> sixth;
  vector < vector < double> > depthMatrix;

	vector<double> m1d;
	vector<vector<double> > m2d;
	vector<vector<vector<double > > > m3d;	
	vector<vector<vector<vector<double > > > > m4d;

double first[3];
double second[3];
double third[3];
double seventh[3];
  double cross[3];
double betadotArray[3];
double obsPointArray[3];
double betaArray[3];
double fourth;
double fifth;
double ninth;
double tenth;
double norm;
double betaNorm;
  for (int t=0; t<tSteps; t++)
  {

    for (int n=0; n<(obsPoints); n++)
    {
for(int p = 0;p < nParticles;p++)
{

for (int k = 0;k < 3; k++)
{
obsPointArray[k] = observation[n][k]-positions[t][p][k];//slightly more accurate
//obsPointArray[k] = observation[n][k];//simplified
betaArray[k] = velocities[t][p][k];
}
           norm =   normalizer(obsPointArray);
 	   betaNorm = normalizer(betaArray);


fourth = 0;
for(int i = 0;i<3;i++)
{
betadotArray[i] = accelerations[t][p][i];
obsPointArray[i] = obsPointArray[i]/norm;
first[i] = (obsPointArray[i] - velocities[t][p][i]);//beta of the first particle ( i think)

//picking a spot and getting measurement out of the way, why not?
m1d.push_back(t*dt +norm/c);
//cout<<"the time section of measurement is "<<t*dt<<endl;
//cout<<"the norm/c section is "<<norm/c<<endl; 
//m1d.push_back(t*dt -norm/c);




if (n==50)
{
//cout<<first[i]<<endl;
}
fourth = fourth + velocities[t][p][i]*obsPointArray[i];
seventh[i] = first[i];

}
fifth = pow((1-fourth),2);
ninth = fifth;
tenth = ninth*norm*(1/(1-betaNorm*betaNorm));
   crossProducter(first,betadotArray,second);
   crossProducter(obsPointArray,second,third);
//sixth.clear();
//cout<<fifth<<endl;
//cout<<betadotArray[1]<<endl;
for (int j = 0;j<3;j++)
{
//sixth.push_back(seventh[j]/tenth+third[j]/fifth); //both
sixth.push_back(third[j]/fifth); // just radiation
//sixth.push_back(seventh[j]/tenth);// just coulomb velocity
//cout<<third[j]/fifth<<endl;

}
//find the polarizations
for (int q = 0; q < 3; q++)
	{
	if(q == 2 || q ==0 || q == 1)
		{sixth[q] = sixth[q];
		}
	else
		{sixth[q] = 0;
		}

//probably add another dimension storer here
}
m2d.push_back(m1d);
m1d.clear();
        depthMatrix.push_back(sixth);
        sixth.clear();


    }
m3d.push_back(m2d);
m2d.clear();
          v3d.push_back(depthMatrix);
      depthMatrix.clear();

}
m4d.push_back(m3d);
m3d.clear();
v4d.push_back(v3d);
v3d.clear();
}
   measurements = m4d; 
  
 return (v4d);


}






void parser(double nParticles,int tSteps,char *  fileName,char * timeFile, vector<vector<vector<double> > > & positions, vector<vector<vector<double > > > & velocities, vector<vector<vector<double > > > & accelerations,vector<double > & timevector)
{
int range = nParticles*3;
//char * omnifile = "omnifile.txt";



FILE * pFile;
FILE * tFile;
vector <double> r1d;
vector <double> v1d;
vector <double> a1d;
vector<vector<double> > r2d;
vector<vector<double> > v2d;
vector<vector<double> > a2d;
vector<vector<vector<double> > > r3d;
vector<vector<vector<double> > > v3d;
vector<vector<vector<double> > > a3d;
//may have a problem later calling these char, ut i  can probably convert
//double mystring [range*3];//it needs enough to get n*i*rav
//double timestring [1];

double temptime;
//char mystring [range*3];//it needs enough to get n*i*rav
char mystring [range*9];//it needs enough to get n*i*rav

double doubletime;
char timestring [10];
vector<double> timetest;
timetest.push_back(2);
timetest.push_back(2);

//cout<<"gets to here"<<endl;
	int count = 1;
tFile = fopen(timeFile,"rb");
pFile = fopen(fileName,"rb");
for (int t = 0;t < tSteps;t++)
{
   fgets (mystring , range*1000 , pFile);

 //  fgets (timestring,900,tFile);
   fscanf(tFile,"%lf", &doubletime );

//cout<<mystring<<endl;
//cout<<"gets to here "<<doubletime<<endl;
doubletime = doubletime;
// temptime = atof(timestring);
//doubletime = (double) temptime;
//cout<<"gets to here 3 "<<doubletime<<endl;  
//timetest.push_back (doubletime);
//cout<<"gets to here 4"<<endl;
timetest.push_back (doubletime);
//cout<<"gets to here"<<endl;
	cout<<"gets to here "<<t<<endl;
	for(int p = 0;p < nParticles;p++)
	{ 
		for(int i = 0; i < 3; i++)
		{
			r1d.push_back(mystring[count*0 + i - 1]);
			v1d.push_back(mystring[count*3 + i - 1]);
			a1d.push_back(mystring[count*6 + i - 1]);
		}
	count++;
	r2d.push_back(r1d);
	r1d.clear();
        v2d.push_back(v1d);
        v1d.clear();
        a2d.push_back(a1d);
        a1d.clear();
	}
        r3d.push_back(r2d);
        r2d.clear();
        v3d.push_back(v2d);
        v2d.clear();
        a3d.push_back(a2d);
	a2d.clear();

}
positions = r3d;
velocities = v3d;
accelerations = a3d;

}



void parser2(double nParticles,int tSteps,char *  fileName,char * timeFile, vector<vector<vector<double> > > & positions, vector<vector<vector<double > > > & velocities, vector<vector<vector<double > > > & accelerations,vector<double > & timevector)
{
FILE * pFile;
FILE * tFile;
        int count = 1;

vector <double> r1d;
vector <double> v1d;
vector <double> a1d;
vector<vector<double> > r2d;
vector<vector<double> > v2d;
vector<vector<double> > a2d;
vector<vector<vector<double> > > r3d;
vector<vector<vector<double> > > v3d;
vector<vector<vector<double> > > a3d;
double thistime;
double first,second,third,fourth,fifth,sixth,seventh,eigth,neinth;
tFile = fopen(timeFile,"rb");
pFile = fopen(fileName,"rb");

for (int t = 0;t < tSteps;t++)
{
   
fscanf(tFile,"%lf", &thistime );
timevector.push_back (thistime);
//cout<<thistime<<endl;
 for(int p = 0;p < nParticles;p++)
        {      fscanf(pFile,"%lf %lf %lf", &first,&second,&third );
	       fscanf(pFile,"%lf %lf %lf", &fourth,&fifth,&sixth );
		 fscanf(pFile,"%lf %lf %lf", &seventh,&eigth,&neinth );

                for(int i = 0; i < 3; i++)
                {
//		cout<<first<<"is the position,the time is "<<t<<endl;
		r1d.push_back(first);
               r1d.push_back(second);
               r1d.push_back(third);
                v1d.push_back(fourth);
               v1d.push_back(fifth);
               v1d.push_back(sixth);
                a1d.push_back(seventh);
               a1d.push_back(eigth);
               a1d.push_back(neinth);

		

        	}
        count++;
        r2d.push_back(r1d);
        r1d.clear();
        v2d.push_back(v1d);
        v1d.clear();
        a2d.push_back(a1d);
        a1d.clear();
        }
        r3d.push_back(r2d);
        r2d.clear();
        v3d.push_back(v2d);
        v2d.clear();
        a3d.push_back(a2d);
        a2d.clear();

}
positions = r3d;
velocities = v3d;
accelerations = a3d;

fclose(tFile);
fclose(pFile);
}








vector<vector<double > > observationPoints(int nPoints, double radius)
{
   int counter;
  int nDimensions = 3;
    vector < vector <  double> >  v2d;
    double pi = 3.1415926535;
    int m;
  vector< double> row;


 counter = 0;
    for (float n=0; n<(nPoints*nDimensions); n++)
    {
    m = (n -fmod(n,3))/3;
//cout<<nPoints-m<<endl;
        if (counter%3 == 0)
        {
   //    row.push_back(radius*sin(pi/2 + pi*(nPoints-m)/(nPoints*10000))); //zoom
//       row.push_back(radius*sin(pi*(nPoints-m)/nPoints)); //normal
      row.push_back(radius*cos((.125)*pi*(nPoints-m)/nPoints + .4375*pi)); //zoom for ics motion
//       row.push_back(radius*sin((.5)*pi*(nPoints-m)/nPoints + .25*pi)); //zoom?
//cout<<"x values are "<<radius*cos((.5)*pi*(nPoints-m)/nPoints + .25*pi)<<endl; 
// row.push_back(radius*cos((.5)*pi*(nPoints-m)/nPoints + .25*pi)); //zoom for ics motion in z direction

    //    row.push_back(radius*sin(pi*(nPoints)/nPoints));
  //    row.push_back(radius*sin(.03 + pi*(nPoints-m)/nPoints));

   }
        if (counter%3 == 1)
        {
        row.push_back(0);
        }
        if (counter%3 == 2)
        {
       row.push_back(radius*sin((.125)*pi*(nPoints-m)/nPoints + .4375*pi)); //zoom for ics motion

//      row.push_back(radius*cos(pi/2 + pi*(nPoints-m)/(nPoints*10000))); //zoom
//cout<<pi/2 + pi*(nPoints-m)/(nPoints*10)<<endl;
  //    row.push_back(radius*cos(pi*(nPoints-m)/nPoints)); //normal
//  row.push_back(radius*cos((.5)*pi*(nPoints-m)/nPoints + .25*pi)); //zoom?
//cout<<"z values are "<<radius*sin((.5)*pi*(nPoints-m)/nPoints + .25*pi)<<endl;
//      row.push_back(radius*sin((.5)*pi*(nPoints-m)/nPoints + .25*pi)); //zoom for ics motion in z direction


 //  row.push_back(radius*cos(pi*()/nPoints));
//       row.push_back(.03 + radius*cos(pi*(nPoints-m)/nPoints));//exploring possible issue at theta = 0

        }
        counter++;
//cout<<row[0]<<endl;

    if( counter%(nDimensions) == 0)
    {
      v2d.push_back(row);
      row.clear();


    }
    }

 return (v2d);
}

