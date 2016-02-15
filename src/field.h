#ifndef FIELD_H
#define FIELD_H

#include "general.h"
struct Rep;

struct FieldPoint{
  int x, y;
  vector<double> vals;
  FieldPoint(int x_, int y_) : x(x_), y(y_){
    vals = vector<double>(N_FIELDS, 1.0);
  }
};

struct Field{
  Field();
  int size_x, size_y;
  vector<FieldPoint> points;

  void gen_single_point();
};

#endif
