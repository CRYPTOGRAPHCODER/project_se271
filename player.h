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
  template <typename T> T get_value(const char *x);
};

#endif
