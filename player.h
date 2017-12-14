#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include "functions.h"
constexpr int STATS = 6;
constexpr int ITEMS_MAX = 8;
constexpr int SUBJECTS_MAX = 20;

// add compile option -static-libstdc++
class player{
private:
  std::string name;
  int stats[STATS];
  int stats_item[STATS];
  int items[ITEMS_MAX];
  int subjects[SUBJECTS_MAX];
  int life;
  int life_f;
  int money;
  int credit_acquired_ess;
  int credit_required_ess;
  int credit_acquired_chs;
  int credit_required_chs;
  int score;
  char names[BUFFER];
public:
  player();
  ~player();
  void stat_update();
  //name
  std::string get_name() { return this->name; }
  void set_name(std::string value) { this->name = value; }

  //stats
  int* get_stats() { return this->stats; }
  void set_stats(int value, int i) { stats[i] = value; }
  void add_stats(int value, int i) { stats[i] += value; }

  //equipments
  bool item_check(int index);
  void item_delete_find(int index);
  void item_add(int index);
  void item_delete(int index){this->items[index] = 0;}
  void set_item(int value, int index){this->items[index] = value;}
  int* get_items(){return this->items;}

  //subjects
  int* get_subjects() { return this->subjects; }
  void set_subjects(int value, int i) { subjects[i] = value; }

  //life
  int get_life() { return this->life; }
  void set_life(int value) { this->life = value; }
  void add_life(int value) { this->life += value; if(this->life>this->life_f){life=life_f;} }

  //life_f
  int get_life_f() { return this->life_f; }
  void set_life_f(int value) { this->life_f = value; }
  void add_life_f(int value) { this->life_f += value; }

  //money
  int get_money() { return this->money; }
  void set_money(int value) { this->money = value; }
  void add_money(int value) { this->money += value; if(this->money<0){int dmg = -this->money; this->money=0; this->life-=dmg/50;}}

  //credit_acquired_ess
  int get_credit_acquired_ess() { return this->credit_acquired_ess; }
  void set_credit_acquired_ess(int value) { this->credit_acquired_ess = value; }
  void add_credit_acquired_ess(int value) { this->credit_acquired_ess += value; }

  //credit_required_ess
  int get_credit_required_ess() { return this->credit_required_ess; }
  void set_credit_required_ess(int value) { this->credit_required_ess = value; }

  //credit_acquired_chs
  int get_credit_acquired_chs() { return this->credit_acquired_chs; }
  void set_credit_acquired_chs(int value) { this->credit_acquired_chs = value; }
  void add_credit_acquired_chs(int value) { this->credit_acquired_chs += value; }

  //credit_required_chs
  int get_credit_required_chs() { return this->credit_required_chs; }
  void set_credit_required_chs(int value) { this->credit_required_chs = value; }

  //score
  int get_score() { return this->score; }
  void add_score(int value) { this->score += value; }

  //misc
  void string_to_char(){
      for(int i = 0; i<5; i++){
          names[i] = name[i];
      }
  }
  void char_to_string(){
      std::string name2 = "";
      for(int i= 0; i<5; i++){
          name2 +=names[i];
      }
      name += name2;
  }
};

#endif
