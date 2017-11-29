#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>

constexpr int STATS = 5;
constexpr int EQUIPMENTS_MAX = 10;
// add compile option -static-libstdc++
class player{
private:
  std::string name;
  int *stats;
  int *equipments;
  int *subjects;
  int life;
  int life_f;
  int money;
  int credit_acquired_ess;
  int credit_required_ess;
  int credit_acquired_chs;
  int credit_required_chs;
  int score;
public:
  player();
  ~player();

  //name
  std::string get_name() { return this->name; };
  void set_name(int value) { this->name = value; };

  //stats
  int* get_stats() { return this->stats; };
  void set_stats(int value) { *stats = value; };
  void add_stats(int value) { *stats += value; };

  //equipments
  int* get_equipments() { return this->equipments; };
  void set_equipments(int value) { *equipments = value; };
  void add_equipments(int value) { *equipments += value; };

  //life
  int get_life() { return this->life; };
  void set_life(int value) { this->life = value; };
  void add_life(int value) { this->life += value; };

  //life_f
  int get_life_f() { return this->life_f; };
  void set_life_f(int value) { this->life_f = value; };
  void add_life_f(int value) { this->life_f += value; };

  //money
  int get_money() { return this->money; };
  void set_money(int value) { this->money = value; };
  void add_monet(int value) { this->money += value; };

  //credit_acquired_ess
  int get_credit_acquired_ess() { return this->credit_acquired_ess; };
  void set_credit_acquired_ess(int value) { this->credit_acquired_ess = value; };
  void add_credit_acquired_ess(int value) { this->credit_acquired_ess += value; };

  //credit_required_ess
  int get_credit_required_ess() { return this->credit_required_ess; };
  void set_credit_required_ess(int value) { this->credit_required_ess = value; };
  void add_credit_required_ess(int value) { this->credit_required_ess += value; };

  //credit_acquired_chs
  int get_credit_acquired_chs() { return this->credit_acquired_chs; };
  void set_credit_acquired_chs(int value) { this->credit_acquired_chs = value; };
  void add_credit_acquired_chs(int value) { this->credit_acquired_chs += value; };

  //credit_required_chs
  int get_credit_required_chs() { return this->credit_required_chs; };
  void set_credit_required_chs(int value) { this->credit_required_chs = value; };
  void add_credit_required_chs(int value) { this->credit_required_chs += value; };

  //score
  int get_score() { return this->score; };
  void set_score(int value) { this->score = value; };
  void add_score(int value) { this->score += value; };
};

#endif
