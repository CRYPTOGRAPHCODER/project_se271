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

  this->life_f = this->stats[0]*100+1000;
  this->life = this->life_f;

  this->money = 0;

  this->credit_acquired_ess = 0;
  this->credit_required_ess = 24;
  this->credit_acquired_chs = 0;
  this->credit_required_chs = 36;

  this->score = 0;
}
player::~player(){

}
