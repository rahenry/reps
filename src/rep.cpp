#include "tank.h" 
#include "rep.h"
#include "rng.h"

void Rep::time_step(){
  if (!alive) return; 

  interact(); // interact must be before movement, otherwise reps will've moved away from where they generated the rep fields

  double v_x = p_x / mass;
  double v_y = p_y / mass;
  
  double x_old = x;
  x += v_x * tank->dt;
  y += v_y * tank->dt;
  if (x >= tank->siz_x || x < 0.0) x = x - tank->siz_x * floor(x / tank->siz_x);
  if (y >= tank->siz_y || y < 0.0) y = y - tank->siz_y * floor(y / tank->siz_y);
  cout.precision(6);
  //if (x >= tank->siz_x || x < 0.0) cout << "!>L!L! " << x << " " << x_old << " " << v_x << " " << p_x << " " << mass << endl;
  //if (y >= tank->siz_y || y < 0.0) cout << "SLJKDFLJKDS " << y << endl;

  energy -= pow(mass,1.1) * HUNGER_COEFFICIENT * tank->dt * (1.0 + 0.21 * energy);
}

void Rep::interact(){
  for (auto & fp : field.points){
    int field_x, field_y;
    field_x = floor(x+fp.x);
    field_y = floor(y+fp.y);
    field_x = field_x - tank->siz_x * floor(double(field_x) / tank->siz_x);
    field_y = field_y - tank->siz_y * floor(double(field_y) / tank->siz_y);

    // field 0: eats nutrients
    double tank_nutrients = tank->nutrient_field(field_x, field_y);

    if (identifier == 15){
      //cout << tank_nutrients << endl;
    }
    double nutrients_absorbed = min(tank->dt * tank_nutrients * fp.vals[0] * NUTRIENT_ABSORBTION, tank_nutrients);
    energy += nutrients_absorbed;
    tank->nutrient_field(field_x, field_y) -= nutrients_absorbed;

    // field 0: eats sunlight
    double tank_sunlight = tank->sunlight_field(field_x, field_y);
    energy += tank->dt * tank_sunlight * fp.vals[0];
    

    // field 0: gets eaten by field 1
    if ((tank->rep_fields[1](field_x, field_y) - fp.vals[1]) < 0.0) cout << ":( " << fp.vals[1] << " " << tank->rep_fields[1](field_x, field_y) << endl;
    energy -= (tank->rep_fields[1](field_x, field_y) - fp.vals[1]) * fp.vals[0] * CARNIVORE_COEFFICIENT * tank->dt;

    // field 1: eats field 0
    energy += (tank->rep_fields[0](field_x, field_y) - fp.vals[0]) * fp.vals[1] * CARNIVORE_COEFFICIENT * tank->dt;
  }
}

void Rep::mutate(){

  mass = 0.0;
  for (auto & fp : field.points){
    for (auto & v : fp.vals){
      double g = 0.01;
      double rand = rng() * 2.0 * g - g;
      v += rand;
      if (v < 0.0) v = 0.0;
      mass += v;
    }
  }

  // randomise direction of motion
  double theta = rng() * 2.0 * PI;
  double mod_p = sqrt(p_x*p_x + p_y*p_y);
  p_x = mod_p * sin(theta);
  p_y = mod_p * cos(theta);

}
