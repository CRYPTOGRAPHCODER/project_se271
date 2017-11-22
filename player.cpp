#include "player.h"
player::player(){
  this->stats = new int[STATS];
  this->equipments = new int[EQUIPMENTS_MAX];
  //stats : life / recov / math / science / literature / code
  for (int i = 0; i < STATS; i++){
		this->stats[i] = 0;}
  for (int i = 0; i < EQUIPMENTS_MAX; i++){
    this->equipments[i] = 0;}
  this->life = this->stats[0]*100+1000;
  this->money = 0;
  this->credit_acquired_ess = 0;
  this->credit_required_ess = 50;
  this->credit_acquired_chs = 0;
  this->credit_required_chs = 70;
  this->score = 0;
};
player::~player(){

};
