#include "functions.h"

double rnd_d(){
    static std::random_device rd;
    static std::mt19937 rng(time(0));
    std::uniform_real_distribution<double> rand(0.0, 1.0);
    return rand(rng);
}
int* rnd_ia(int lim, int coun) {
    int* rnd_a = new int[coun];
    for (int t = 0; t < coun; t++) { rnd_a[t] = 0; };
    for (int i = 0; i < coun; i++) {
        rnd_a[i] = (int)(rnd_d()*lim);
        for (int k = 0; k < i; k++) {
            if (rnd_a[k] == rnd_a[i]) {
                rnd_a[i] = 0;
                i--;
            break;
            }
        }
    }
    return rnd_a;
}
