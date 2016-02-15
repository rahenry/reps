#ifndef TANK_H 
#define TANK_H

#include "general.h"
#include "rep.h"
#include "array.h"
#include "field.h"


struct Tank{
  int siz_x, siz_y;
  vector<Array> rep_fields;
  Array nutrient_field;
  Array sunlight_field;
  vector<Rep> reps;
  vector<int> reps_dead;
  double dt;

  Tank(string fileName);
  Tank(int siz_x, int siz_y);
  Tank();
  void initialise();
  void time_step();
  void process_rep(Rep& rep);
  void regenerate_rep_fields();
  void regenerate_nutrient_field();

  int n_alive, n_dead, n_replicated;

  int n_reps_total;
};

#endif
