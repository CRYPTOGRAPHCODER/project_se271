#include "main.h"
#include "game.h"

void menu_main();
void menu_start();

int main(int argc, const char * argv[]){
  menu_main();
  return 0;

}

void menu_main() {
	boolean isKey_vaild = true;
	while (isKey_vaild) {
		system("cls");
		printf("main menu\ns.start l.load x.exit \n >> ");
		char menu_select = getchar();
		while (getchar() != '\n');

		switch (menu_select) {
		case 'S':
		case 's':
			menu_start();
			break;
		case 'L':
		case 'l':
			//menu_load();
			break;
		case 'X':
		case 'x':
			isKey_vaild = false;
			break;
		default:
			break;
		}
	}
}

void menu_start(){
  game_start();
}
