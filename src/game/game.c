#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "game.h"
// #include "../hif/timer.h"
// #include "../api/menu.h"

int tickCounter = 0;

#pragma interrupt
void interruptHandler() {
  tickCounter++;
}


void runGame() {
  int runMainLoop = 1;
  //initTimer(interruptHandler);
  DI();
  // Init Timer and interrupt settings.
  T0CTL = 0x19;
  // timer 0 byte registers set initial value:
  T0H = 0x0;
  T0L = 0x1;
  // Set reload stuff 5A00
  T0RH = 0x0A; // RH high
  T0RL = 0x00; // RL low
  // ENABLE TIMER INTERRUPT Set to level 3.
  IRQ0ENH |= 0x20;
  IRQ0ENL |= 0x20;
  // ENABLE TIMER
  SET_VECTOR(TIMER0, interruptHandler);
  EI();

  T0CTL |= 0x80;
  // addMenuItem("View Highscore");
  // addMenuItem("Start game");
  printf("Initialized game..");
  while (runMainLoop == 1) {
    // printf("asdasd\n");
    if (tickCounter == 1000)
    {
      printf("hallo from mainLoop\n");
    }
  }
  // show menu screen on console
  // Wait for input go to highscore if this option is picked.
  // Start game if this option is picked.
}