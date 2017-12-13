#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <random>
#include <time.h>

constexpr int BUFFER = 1024;

double rnd_d();
double rnd_r(double min, double max);
int* rnd_ia(int lim, int coun);
/*
char* string_to_char(std::string input){
    char output[BUFFER];
    int i;
    while(input[i]=='\0'){
        output[i] = input[i];
        i++;
    }
    return output;
}

std::string char_to_string(char* input){
    std::string name2 = "";
    int i=0;
    while(input[i]=='\0'){
        name2 +=input[i];
        i++;
    }
    return name2;
}
*/
#endif // FUNCTIONS_H
