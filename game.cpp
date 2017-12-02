#include "game.h"
void gameManager::data_set(){
    console_data[0] = "합격을 축하드립니다! 당신은 길고 긴 수험 생활을 끝내고 대학교에 진학하였습니다.";
    button_data[0][0] = "다음";
    console_data[1] = "기본적인 조작 방법에 대해서 설명하겠습니다";
    button_data[1][0] = "다음";
}

gameManager::gameManager(){

    this->turn = 0;
    for(int i=0;i<DATA_LENGTH;i++){
        for(int j=0;j<BUTTON_LENGTH;j++){
            this->button_data[i][j]="";
        }
        this->console_data[i]="";
    }
    data_set();
    for(int i=0;i<BUTTON_LENGTH;i++){
        this->button[i]="";
    }
    print_update();
}

gameManager::~gameManager(){

}

void gameManager::proceed(int input){
    switch(this->gamestate){
    case 0:
        if(input == 1){
            this->gamestate = 1;
        }
        break;
    default:
        break;
    }
    print_update();
}

void gameManager::print_update(){
    this->console = console_data[gamestate];
    for(int i=0;i<9;i++){this->button[i]=button_data[gamestate][i];}
}
void gameManager::game_init(){
  // Initializes game
  turn = 0;
}

void gameManager::game(){
  // Initializing game
  game_init();
  // Start game
  // Repeat until player is game over or complete the game
  while (pl.get_life()>0){
    // Action of each turn;
    game_turn();

    // Add 1 turn
    turn++;
  }
  // End of game
  game_over();

}

void gameManager::game_turn(){
  // Each Turn
  bool isKey_vaild = true;
	while (isKey_vaild) {
    char menu_select = getchar();
    while (getchar() != '\n');
    switch (menu_select) {
    case 'S': case 's': store(); continue;
    case 'F': case 'f': meet_friend(); isKey_vaild = false; break;
    case 'P': case 'p': visit_professor(); isKey_vaild = false; break;
    case 'C': case 'c': club_room(); isKey_vaild = false; break;
    case 'G': case 'g': play_game(); isKey_vaild = false; break;
    case 'A': case 'a': wander_around(); isKey_vaild = false; break;
    case 'R': case 'r': rest(); isKey_vaild = false; break;
    case 'W': case 'w': work(); isKey_vaild = false; break;
    case 'X': case 'x': sugang(); isKey_vaild = false; break;
    default: continue;
    }
  }
}

void gameManager::store(){};
void gameManager::meet_friend(){};
void gameManager::visit_professor(){};
void gameManager::club_room(){};
void gameManager::play_game(){};
void gameManager::wander_around(){};
void gameManager::rest(){};
void gameManager::work(){};
void gameManager::sugang(){};
void gameManager::calculate_semester(){};
void gameManager::game_over(){};
