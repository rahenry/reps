#ifndef ARRAY_H
#define ARRAY_H
#include "general.h"

struct Tank;

struct Array{
  int siz_x, siz_y;
  vector<double> vals;

  double& operator()(int i, int j) {
    if (i > siz_x || j > siz_y || i < 0 || j < 0) cout << "!" << endl;
    return vals[i + siz_x*j];
  };

  double operator()(int i, int j) const {
    if (i > siz_x || j > siz_y || i < 0 || j < 0) cout << "!" << endl;
    return vals[i + siz_x*j];
  };


  Array(int siz_x_, int siz_y_, double k_);
  Array() = default;
};

#endif
