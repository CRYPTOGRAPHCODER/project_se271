#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <cstdio>
#include "windows.h"
#include "sugang_simulator_2017.h"


class gameManager{
private:
    // Global variables that indicates turns and player
    // Turn : 10 Days, 4 times
    int turn;
    player pl;
public:
    gameManager();
    ~gameManager();
    void game();
    void game_init();
    void game_load();
    void game_save();
    void game_turn();

    void store();
    void meet_friend();
    void visit_professor();
    void club_room();
    void play_game();
    void wander_around();
    void rest();
    void work();

    void sugang();

    void calculate_semester();
    void game_over();

    player get_pl(){return pl;}
    int get_turn(){return turn;}
};


#endif
