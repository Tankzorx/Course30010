#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routine

#include "menu.h"
#include "../hif/console.h"


void renderMenu() {
  // printf("Rendered menu.\n");
  gotoxy(5,5);
  blink(1);
  printf("MENU OPTION 1\n");
  blink(0);
  gotoxy(5,9);
  printf("MENU OPTION 2\n");

}