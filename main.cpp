#include "subject.h"
#include "player.h"

void menu_main();

int main(int argc, char[][]args){
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
