#include "player.h"
player::player(){
  this->name = "Waldo";
  //stats : life / recov / science / code / literature / social
  for (int i = 0; i < STATS; i++){
        this->stats[i] = 5;}
  for (int i = 0; i < EQUIPMENTS_MAX; i++){
    this->equipments[i] = 0;}
  for (int i = 0; i < SUBJECTS_MAX; i++){
    this->subjects[i] = -1;}

  this->life_f = 1000;
  for(int i =0;i<this->stats[0];i++){
      this->life_f = (int)(this->life_f*1.03);
  }
  this->life = this->life_f;

  this->money = 0;

  this->credit_acquired_ess = 0;
  this->credit_required_ess = 24;
  this->credit_acquired_chs = 0;
  this->credit_required_chs = 36;

  this->score = 0;
  stat_update();
}
player::~player(){
    /*
    delete[] this->stats;
    delete[] this->equipments;
    delete[] this->subjects;*/
}

void player::stat_update(){
    this->life_f=1000;
    for(int i =0;i<this->stats[0];i++){
        this->life_f = (int)(this->life_f*1.03);
    }

}

bool player::check_item(int index){
    for(int i =0;i < EQUIPMENTS_MAX;i++){
        if(this->equipments[i] == index){
            return true;
        }
    }
    return false;
}
