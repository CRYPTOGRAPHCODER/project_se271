#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <cstdio>
#include "windows.h"
#include "subject.h"
#include "player.h"


constexpr int MAX_SUBJECT = 100;
constexpr int DATA_LENGTH = 100;
constexpr int BUTTON_LENGTH = 9;
class gameManager{
private:
    // Global variables that indicates turns and player
    // Turn : 10 Days, 4 times
    int turn;
    // Player variable holds data of player
    player pl;
    // Determine state of the game
    // -1, -2 ... game over
    // 0, start of the game
    int gamestate = 0;
    // Define enough number of subjects
    subject s[MAX_SUBJECT];
    // String data to print to console
    std::string console;
    // String data to print to buttons
    std::string button[BUTTON_LENGTH];
    // data
    std::string console_data[DATA_LENGTH];
    std::string button_data[DATA_LENGTH][BUTTON_LENGTH];
public:
    gameManager();
    ~gameManager();
    void game();
    void game_init();
    void game_turn();
    void data_set();

    void proceed(int input);
    void print_update();




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

    player get_pl(){return this->pl;}
    int get_turn(){return this->turn;}
    int get_gamestate(){return this->gamestate;}
    std::string get_console(){return this->console;}
    std::string get_button(int i){return this->button[i];}
};


#endif
