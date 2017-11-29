#include "game.h"
#include "subject.h"
#include "player.h"
#include "sugang_simulator_2017.h"



gameManager::gameManager(){
    this->turn = 0;
}

gameManager::~gameManager(){

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
/*
void gameManager::print_game_turn(int turn){
  // Temp Printing Each Turn;
  system("cls");
  printf("\n  Year %d, Day %d ",turn/40+1, (turn/4)%10+1);
  switch(turn%4+1){
    case 1: printf("Morning\n");break;
    case 2: printf("Afternoon\n");break;
    case 3: printf("Evening\n");break;
    case 4: printf("Night\n");break;
  }
  printf("\n 　　　 　　／⌒ヽ\n⊂二二二（　＾ω＾）二⊃\n　　　　　　|　　　 /\n　　 　　　 （　ヽ/\n　　　　　　 ﾉ>ノ\n　　 三　　レﾚ\n\n");
  printf("  What you gonna do?\n");
  printf("  S.Store, F.meet Friend, P.visit Professor \n");
  printf("  C.go to Club room, G.play Game, A.wander Around \n");
  printf("  R.Rest, W.Work");
  if((turn/4)%10+1>7){
    printf(", X.SUGANG.DGIST.AC.KR ");
  }
  printf("\n\n >> ");
}
*/

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
void gameManager::game_save(){};
void gameManager::game_load(){};
