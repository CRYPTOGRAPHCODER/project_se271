#include "game.h"
#include "subject.h"
#include "player.h"


void game_turn(int turn, player *pl);
  void store();
  void meet_friend();





void game_init(){
  player pl;
  int turn = 0;
  while (true){
    game_turn(turn, &pl);
    turn++;
}
}

void game_turn(int turn, player *pl){
  bool isKey_vaild = true;
	while (isKey_vaild) {
    //SetConsoleOutputCP(CP_UTF8);
    system("cls");
    printf("\n  Year %d, Day %d ",turn/40+1, (turn/4)%10+1);
    switch(turn%4+1){
      case 1:
        printf("Morning\n");break;
      case 2:
        printf("Afternoon\n");break;
      case 3:
        printf("Evening\n");break;
      case 4:
        printf("Night\n");break;
    }
    printf(" 　　　 　　／⌒ヽ\n⊂二二二（　＾ω＾）二⊃\n　　　　　　|　　　 /\n　　 　　　 （　ヽ/\n　　　　　　 ﾉ>ノ\n　　 三　　レﾚ");
    printf("  What you gonna do?\n");
    printf("  S.Store, F.meet Friend, P.visit Professor \n");
    printf("  C.go to Club room, G.play Game, W.Wander around \n");
    printf("  R.Rest, W.Work");
    if((turn/4)%10+1>7){
      printf(", X.SUGANG.DGIST.AC.KR ");
    }
    printf("\n\n >> ");

    printf("%d",pl->get_value<int>("life"));

    char menu_select = getchar();
    while (getchar() != '\n');
    switch (menu_select) {
    case 'S':
    case 's':
      break;
    case 'L':
    case 'l':
      isKey_vaild = false;
      break;
    default:
      continue;
    }
  }
}
