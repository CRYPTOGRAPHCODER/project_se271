#include "main.h"
#include "game.h"

void menu_main();
void menu_start();

int main(int argc, const char * argv[]){
  // Set console codepage
  SetConsoleCP(65001);
  // Load Main menu
  menu_main();
  return 0;
}

void menu_main() {
  // Variable to check input is vaild
	bool isKey_vaild = true;
	while (isKey_vaild) {
    //Print main menu
		system("cls");
		printf("main menu\ns.start l.load x.exit \n >> ");

    //Basic input
    char menu_select = getchar();
		while (getchar() != '\n');

		switch (menu_select) {
    // Start game with Basic settings
    case 'S': case 's':
      menu_start(); break;
    // Load game
		case 'L': case 'l':
			//menu_load();
      break;
    // Exit game
		case 'X': case 'x':
			isKey_vaild = false; break;
		default: break;
		}
	}
}

void menu_start(){
  // Start game
  game();
}
