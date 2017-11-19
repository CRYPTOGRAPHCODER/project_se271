#include "player.h"

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

bool Tem_compare(char*x, char *y) {
	for (int i = 1; x[i] != NULL; i++) {
		if (x[i] != y[i])
			return 0;
	}
	return 1;
};

template<typename T>
T get(char *x) {
	if (x[0] == 'n')
		if (Tem_compare("name", *x) == true) { return this->name; }
	if (x[0] == 's')
		if (Tem_compare("stats", *x) == true) { return this->stats; }
	if (x[0] == 'e')
		if (Tem_compare("equipments", *x) == true) { return this->equipments; }
	if (x[0] == 'l')
		if (Tem_compare("life", *x) == true) { return this->life; }
	if (x[0] == 'm')
		if (Tem_compare("money", *x) == true) { return this->money; }
	if (x[0] == 'c') {
		if (x[7] == 'a') {
			if (x[16] == 'e')
				if (Tem_compare("credit_acquired_ess", *x) == true) { return this->credit_acquired_ess; }
			else if (x[16] == 'c')
				if (Tem_compare("credit_acquired_chs", *x) == true) { return this->credit_acquired_chs; }
		}
		else if (x[7] == 'r') {
			if (x[16] == 'e')
				if (Tem_compare("credit_required_ess", *x) == true) { return this->credit_required_ess; }
			else if (x[16] == 'c')
				if (Tem_compare("credit_required_chs", *x) == true) { return this->credit_required_chs; }
		}
	}
	if (x[0] == 's')
		if (Tem_compare("score", *x) == true) { return this->score; }
};
player::~player(){

};
