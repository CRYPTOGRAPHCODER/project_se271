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

  //functions for subject data handling
  // title
  std::string get_title() { return this->title; };
  void set_title(std::string value) { this->title = value; };
  void add_title(std::string value) { this->title += value; };

  //timetale
  int* get_timetable() { return this->timetable; };
  void set_timetable(int value, int i) { timetable[i] = value; };
  void add_timetable(int value, int i) { timetable[i] += value; };

  //credit
  int get_credit() { return this->credit; };
  void set_credit(int value) { this->credit = value; };
  void add_credit(int value) { this->credit += value; };

  //attend_limit
  int get_attend_limit() { return this->attend_limit; };
  void set_attend_limit(int value) { this->attend_limit = value; };
  void add_attend_limit(int value) { this->attend_limit += value; };

  //attend_hope
  int get_attend_hope() { return this->attend_hope; };
  void set_attend_hope(int value) { this->attend_hope = value; };
  void add_attend_hope(int value) { this->attend_hope += value; };

  //attend_people
  int get_attend_people() { return this->attend_people; };
  void set_attend_people(int value) { this->attend_people = value; };
  void add_attend_people(int value) { this->attend_people += value; };

  //category
  int get_category() { return this->category; };
  void set_category(int value) { this->category = value; };
  void add_category(int value) { this->category += value; };

  //score
  int get_score() { return this->score; };
  void set_score(int value) { this->score = value; };
  void add_score(int value) { this->score += value; };

  //workload
  double get_workload() { return this->score; };
  void set_workload(double value) { this->score = value; };
  void add_workload(double value) { this->score += value; };
};

#endif
