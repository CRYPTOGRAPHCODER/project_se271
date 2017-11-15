#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <cstring>

class player(){
private:
  std::string name;
  int life;
  int money;
  int stats;
  int equipments;
  int credit_acquired;
  int credit_required_ess;
  int credit_required_chs;
  int score;
public:
  player(){};
  ~player(){};
};

#endif
