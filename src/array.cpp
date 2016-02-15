#include "array.h"
#include "general.h"

Array::Array(int siz_x_, int siz_y_, double k_) : siz_x(siz_x_), siz_y(siz_y_) {
  vals = vector<double>(siz_x*siz_y, k_);
}

