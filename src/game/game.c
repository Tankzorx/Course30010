#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routine

#include "game.h"
#include "../hif/timer.h"
#include "../api/menu.h"


int tickCounter = 1;
#pragma interrupt
void interruptHandler() {
  tickCounter++;
  if (tickCounter > 1000)
  {
    tickCounter = 0;
  }
}


void runGame() {
  MenuItem items[2] = {{2, "Start Game" }, {3, "Go to Highscore"}};
  // Init timer sets the reloadnumber etc.
  // We want to set it up so that the timer is interrupts every millisecond.
  // GameState gs;
  // gs.state = 1;
  int state = 1; // renderMenu=1, waitForPlaySelection, playing, lost
  initTimer();
  SET_VECTOR(TIMER0, interruptHandler); // Can't avoid this call sadly.
  startTimer();

  while (1) {
    switch (state) {
      case 1: // renderMenu state
	  	
	  	menu(items);
        state = 2;
        break;
      case 2:
        state = 2;
        break;
    };
  }
}