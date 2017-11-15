#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include <string>
#include <cstdlib>

class subject{
private:
  std::string title;
  std::string prof;
  int *timetable;
  int credit;
  double workload;
  int attend_limit;
  int attend_hope;
  int attend_people;
  int category;
  int score;
public:
  subject();
  ~subject();
  template <typename T1>T1 get(std::string var){};
};

#endif
