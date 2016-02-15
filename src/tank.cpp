#include "tank.h"
#include "utility.h"

Tank::Tank()
{

}

void Tank::time_step(){
  regenerate_rep_fields();
  regenerate_nutrient_field();
  n_alive = 0; n_dead = 0; n_replicated = 0;

  for (auto & rep : reps){
    rep.time_step();
  }
  for (int i=0; i < reps.size(); i++){
    process_rep(reps[i]);
  }
}

void Tank::process_rep(Rep& rep){

  if (!rep.alive) return; // this rep was already dead, so we do nothing

  if (rep.energy <= 0.0){ // this rep has just died
    rep.alive = false;
    n_dead++;
    reps_dead.push_back(rep.identifier); // add the rep to the list of currently dead reps
    //nutrient_field(floor(rep.x), floor(rep.y)) += 0.01* rep.mass; // the nutrient field absorbs the dead rep
  }
  else if (rep.energy < rep.mass){ // this rep is still alive, but is not replicating
    n_alive++;
  }
  else{ // this rep is replicating
    double new_energy = rep.energy / double(rep.n_replicate);
    rep.energy = new_energy;
    n_replicated++;
    n_alive += rep.n_replicate;

    if (reps_dead.size() == 0){ // no currently dead reps to replace, so we add to the reps vector
      reps.push_back(rep);
      reps.back().identifier = reps.size();
      reps.back().mutate();
    }
    else{ // there's a currently dead rep whose place the new one can take in the vector
      reps[reps_dead.back()] = rep;
      reps.back().identifier = reps_dead.back();
      reps_dead.pop_back();
      reps.back().mutate();
    }
  }
}

void Tank::regenerate_rep_fields(){

  for (auto & rep_field : rep_fields){
    rep_field = Array(siz_x, siz_y, 0.0);
  }

  for (auto & rep : reps){
    if (!rep.alive) continue;
    for (auto & fp : rep.field.points){
      int field_x = floor(rep.x+fp.x); 
      int field_y = floor(rep.y+fp.y); 
      field_x = field_x - siz_x * floor(double(field_x) / siz_x); 
      field_y = field_y - siz_y * floor(double(field_y) / siz_y); 

      for (int field_index=0; field_index<N_FIELDS; field_index++){
	rep_fields[field_index](field_x, field_y) += fp.vals[field_index];
      }
    }
  }





}

void Tank::regenerate_nutrient_field(){
  int n_blooms = 5;

  for (int i=0; i<n_blooms; i++){
    int bloom_x = floor(siz_x * rng());
    int bloom_y = floor(siz_y * rng());
    double sigma_x = 0.01 * siz_x;
    double sigma_y = 0.01 * siz_y;
    for (int dist_x=floor(-0.01*siz_x); dist_x<floor(0.01*siz_x); dist_x++){
      for (int dist_y=floor(-0.01*siz_y); dist_y<floor(0.01*siz_y); dist_y++){
	int X = dist_x + bloom_x;
	int Y = dist_y + bloom_y;
	X = X - siz_x * floor(double(X) / siz_x);
	Y = Y - siz_y * floor(double(Y) / siz_y);

	nutrient_field(X,Y) += REGENERATION_FACTOR * dt / sigma_x / sigma_y / 2.0 / PI * exp(-0.5 * (pow(X-bloom_x,2)/sigma_x/sigma_x + pow(Y-bloom_y,2)/sigma_y/sigma_y));

      }
    }
  }



}
