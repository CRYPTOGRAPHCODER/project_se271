#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
constexpr int STATS = 5;
constexpr int EQUIPMENTS_MAX = 10;

class player{
private:
  char *name;
  int *stats;
  int *equipments;
  int life;
  int money;
  int credit_acquired_ess;
  int credit_required_ess;
  int credit_acquired_chs;
  int credit_required_chs;
  int score;
public:
  player();
  ~player();
  bool Tem_compare(char *x, char *y) {};
  template<typename T>
  T get(char *x) {};
};

#endif
