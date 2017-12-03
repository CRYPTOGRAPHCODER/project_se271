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
    data d;
public:
    gameManager();
    ~gameManager();
    void game();
    void game_init();
    void game_turn();

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


struct data
{
    std::string co_intro01 = "합격을 축하드립니다! 당신은 길고 긴 수험 생활을 끝내고 대학교에 진학하였습니다.";
    std::string bt_intro01[9] = {"다음","","","","","","","",""};
    std::string co_intro02 = "기본적인 조작 방법에 대해서 설명하겠습니다.\n본 게임에서 모든 유효한 조작은 아래 9개의 버튼을 눌러서 사용합니다.";
    std::string bt_intro02[9] = {"다음","","","","","","","",""};
};


#endif
