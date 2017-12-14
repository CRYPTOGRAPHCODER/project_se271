#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <random>
#include <time.h>

constexpr int BUFFER = 1024;

double rnd_d();
double rnd_r(double min, double max);
int* rnd_ia(int lim, int coun);
#endif // FUNCTIONS_H
