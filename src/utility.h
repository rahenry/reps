#ifndef UTILITY_H
#define UTILITY_H

#include "general.h"
#include <time.h>

string extractInput(string inputString, int offset, char delim);
double extractDouble(string inputString, string varName, char delim, double defaultValue);
string extractString(string inputString, string varName, char delim, string defaultValue);

void printMatrixToFile(double * &M, int len, string fileName);

template<typename T>
void printVector(vector<T> V){
  if (V.size() == 0) return;
  for (int i = 0; i < V.size(); i++)
    cout << V[i] << endl;
  cout << endl;
}

void reportTimeInterval();

void printArrayToFile(vector<double> &A, string fileName, string identifier);
bool readArrayFromFile(vector<double> &tar, string fileName, string identifier, int desiredArraySize);

bool extractStringNew(string &outputString, string inputString, int &offset);
vector<double> extractVector(string inputString, string varName, vector<double> defaultValue);
bool valTest(double val1, double val2, double tol);

#endif
