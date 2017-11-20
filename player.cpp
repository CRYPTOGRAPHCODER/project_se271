#include "player.h"
#include "functions.h"
player::player(){
  this->stats = new int[STATS];
  this->equipments = new int[EQUIPMENTS_MAX];
  //stats : life / ...
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


template <typename T> T player::get_value(const char *x) {
  if (char_compare("life", *x) == true) { return this->life; }
  if (char_compare("name", *x) == true) { return this->name; }
  if (char_compare("stats", *x) == true) { return this->stats; }
  if (char_compare("equipments", *x) == true) { return this->equipments; }
	if (char_compare("money", *x) == true) { return this->money; }
	if (char_compare("credit_acquired_ess", *x) == true) { return this->credit_acquired_ess; }
	if (char_compare("credit_acquired_chs", *x) == true) { return this->credit_acquired_chs; }
	if (char_compare("credit_required_ess", *x) == true) { return this->credit_required_ess; }
	if (char_compare("credit_required_chs", *x) == true) { return this->credit_required_chs; }
	if (char_compare("score", *x) == true) { return this->score; }
}
player::~player(){

};
