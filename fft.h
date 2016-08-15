#ifndef FFT_H
#define FFT_H

vector<complex<double> > bitReversal(vector<complex<double> > data, int nValues);

vector<complex< double> > DLpart(vector<complex<double> > data,int nValues);

vector<vector<vector<complex<double> > > > mainFft(vector<vector<vector<double > > > newEfield,double tSteps);

double mypow(int numOne, int numTwo);

#endif

