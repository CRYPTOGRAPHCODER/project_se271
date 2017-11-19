#include "player.h"

player::player(){
  this->stats = new int[STATS];
  this->name[0] = '0';
  this->copy[0] = '0'; //copy를 초기화
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


template<typename T>
T player::Tem_compare(char *x, char *y, T x) {
	for (int i = 1; x[i] != NULL; i++) {
		if (x[i] != x[i])
			break;
	}
	return T x;
};

template<typename T>
T get(char *x) {
	if (x[0] == 'n')
		Tem_compare<char*>('name', *x, name);
	if (x[0] == 's')
		Tem_compare<int*>('stats', *x, stats);
	if (x[0] == 'e')
		Tem_compare<int*>('equipments', *x, equipments);
	if (x[0] == 'l')
		Tem_compare<int>('life', *x, life);
	if (x[0] == 'm')
		Tem_compare<int>('money', *x, money);
	if (x[0] == 'c') {
		if (x[7] == 'a') {
			if (x[16] == 'e')
				Tem_compare<int>('credit_acquired_ess', *x, credit_acquired_ess);
			else if (x[16] == 'c') {
				Tem_compare<int>('credit_acquired_chs', *x, credit_acquired_chs);
			}
		}
		else if (x[7] == 'r') {
			if (x[16] == 'e')
				Tem_compare<int>('credit_required_ess', *x, credit_required_ess);
			else if (x[16] == 'c') {
				Tem_compare<int>('credit_required_chs', *x, credit_required_chs);
			}
		}
	}
	if (x[0] == 's')
		Tem_compare<int>('score', *x, score);
};
player::~player(){

};
