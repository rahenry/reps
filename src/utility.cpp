#include "utility.h"

bool valTest(double val1, double val2, double tol){
  if (abs(val1-val2) / abs(val1+val2) > tol) return false;
  return true;
}

string extractInput(string inputString, int offset, char delim)
{
  string result;
  char c;
  unsigned int i = offset;
  while(i < inputString.size()){
    c = inputString[i];
    i++;
    if (c == delim) break;
    result += c;
  }
  return result;
}


double extractDouble(string inputString, string varName, char delim, double defaultValue)
{
  size_t found;
  string result;
  string s = varName + "=";

  found = inputString.find(s);
  if (found != string::npos)
  {
    result = extractInput(inputString, s.size() + found, delim);
    if (result == string()) return defaultValue;
    else return atof(result.c_str());
  }
  else
    return defaultValue;
}

string extractString(string inputString, string varName, char delim, string defaultValue)
{
  size_t found;
  string result;
  string s = varName + "=";

  found = inputString.find(s);
  if (found != string::npos)
  {
    result = extractInput(inputString, s.size() + found, delim);
    return result;
  }
  else
    return defaultValue;
}

bool extractStringNew(string &outputString, string inputString, int &offset){
  char c;
  bool result = false;
  outputString = string();
  while(offset < inputString.size()){
    c = inputString[offset];
    offset++;
    if (c == ' '){
      result = true;
      break;
    }
    else if (c == ';'){
      break;
    }
    outputString += c;
  }
  return result;
}

vector<double> extractVector(string inputString, string varName, vector<double> defaultValue){
  size_t found;
  string extractedString;
  string s = varName + "=";
  bool flag = true;
  int offset;
  vector<double> result;

  found = inputString.find(s);
  if (found != string::npos)
  {
    offset = s.size() + found;
    while (flag){
      flag = extractStringNew(extractedString, inputString, offset);
      result.push_back(atof(extractedString.c_str()));
    }
    return result;
  }
  else return defaultValue;
}

void reportTimeInterval(){
  //cout << double( clock() - GLOBAL_TIME) / (double)CLOCKS_PER_SEC<< endl;
  //GLOBAL_TIME = clock();
}
      
void printMatrixToFile(double * &M, int len, string fileName){
  ofstream outFile;
  outFile.precision (numeric_limits<double>::digits10 + 1);
  cout << "Printing to " << fileName << endl;
  outFile.open(fileName);
  for (int i=0; i<len; i++){
    for (int j=0; j<len; j++){
      outFile << M[i+j*len] << " ";
    }
    outFile << endl;
  }
  outFile.close();
}

void printArrayToFile(vector<double> &A, string fileName, string identifier){
  ofstream outFile;
  outFile.open(fileName);
  if (identifier != ""){
    outFile << identifier << endl;
  }
  outFile << "size = " << A.size() << endl;
  outFile.flags(ios::scientific);
  outFile.precision (numeric_limits<double>::digits10 + 1);
  for (auto & element : A){
    if (element == 0.0) outFile << "0" << endl;
    else if (element == 1.0) outFile << "1" << endl;
    else outFile << element << endl;
  }
  outFile.close();
}

bool readArrayFromFile(vector<double> &tar, string fileName, string identifier, int desiredArraySize){
  tar = vector<double>();
  ifstream inFile;
  inFile.open(fileName);
  string firstLine;
  inFile >> firstLine;
  if (firstLine != identifier){
    return false;
  }

  int secondLine;
  inFile >> secondLine;
  if (secondLine < desiredArraySize){
    return false;
  }

  double a;
  while (inFile){
    inFile >> a;
    tar.push_back(a);
  }
  tar.pop_back();

  return true;
}
