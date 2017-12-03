#include "player.h"
player::player(){
  this->name = "Waldo";
  this->stats = new int[STATS];
  //stats : life / recov / science / code / literature / social
  for (int i = 0; i < STATS; i++){
        this->stats[i] = 5;}

  this->equipments = new int[EQUIPMENTS_MAX];
  for (int i = 0; i < EQUIPMENTS_MAX; i++){
    this->equipments[i] = 0;}

  this->life_f = this->stats[0]*100+1000;
  this->life = this->life_f/2;

  this->money = 0;

  this->credit_acquired_ess = 0;
  this->credit_required_ess = 50;
  this->credit_acquired_chs = 0;
  this->credit_required_chs = 70;

  this->score = 0;
}
player::~player(){

}
