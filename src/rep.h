#ifndef REP_H 
#define REP_H 

struct Tank;

#include "field.h"

struct Rep{
  Field field;
  double x, y, energy, p_x, p_y, mass;
  int identifier;
  bool alive;
  int n_replicate; // number to split into when replicating
  Tank *tank;

  void death();
  void replicate();
  void time_step();
  void interact();
  void mutate();

  Rep(){};
};

#endif
