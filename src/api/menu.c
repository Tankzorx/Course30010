#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routine

#include "menu.h"
#include "../hif/console.h"


int menu(MenuItem items[]) {
  int selectedMenuItem = 0;
  int i;


  clrscr();
  for (i = 0; i < 2; i++) {
    gotoxy(5,i*5);
  	if (i == selectedMenuItem) {
		blink(1);
	}
	printf("%s", items[i].str);
	blink(0);
  }	
}