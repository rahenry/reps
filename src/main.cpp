#include "general.h"
#include "tank.h"
#include "utility.h"

void basic_test_1();
int main(int argc, char* argv[]){
  string inputFile;
  //GLOBAL_TIME = clock();

  if (argc == 1){
    inputFile = "input.txt";
  }
  else
  {
    inputFile = string(argv[1]);
  }
  basic_test_1();

}

void basic_test_1(){
  Tank tank1;
  tank1.siz_x = 1000;
  tank1.siz_y = 1000;

  tank1.rep_fields.resize(N_FIELDS);

  tank1.nutrient_field = Array(tank1.siz_x, tank1.siz_y, 0.00);
  tank1.sunlight_field = Array(tank1.siz_x, tank1.siz_y, 0.00);
  

  tank1.reps = vector<Rep>();
  tank1.dt = 1.0;

  Rep rep1;
  Field field1;
  field1.gen_single_point();
  rep1.field = field1;
  rep1.alive = true;
  rep1.n_replicate = 2;
  rep1.tank = &tank1;
  rep1.energy = 0.5;
  rep1.mass = 2.0;

  for (int i=0; i<25; i++){
    tank1.reps.push_back(rep1);
    tank1.reps.back().identifier = i;


    double p = rng() * 0.1;
    double theta = rng() * 2.0 * PI;
    tank1.reps.back().p_x = p * sin(theta);
    tank1.reps.back().p_y = p * cos(theta);
    tank1.reps.back().x = floor(rng() * tank1.siz_x);
    tank1.reps.back().y = floor(rng() * tank1.siz_y);
    tank1.reps.back().energy = rng() *2.0;
  }

  int n_reports = 10000;
  int n_steps = 100000;
  ofstream report_stream("report.txt");
  
  for (int i=0; i<1000000; i++){
    bool report = false;
    tank1.time_step();
    if (i % (n_steps / n_reports) == 0){
      report_stream << i << " " << tank1.n_alive << endl;
    }
    //Rep r = tank1.reps[15];
    //cout << i << " " << r.x << " " << r.y << " " << r.energy << " " << tank1.n_alive << " " << tank1.nutrient_field(floor(r.x), floor(r.y)) << endl;

    //printVector(tank1.reps_dead);
  }

  ofstream final_reps_stream("final_reps.txt");
  for (auto & rep : tank1.reps){
    for (auto & fp : rep.field.points){
      if (rep.alive) final_rep_stream << fp.vals[0] << " " << fp.vals[1] << " " << rep.mass << endl;
    }
  }

  cout << tank1.n_alive << endl;


}

