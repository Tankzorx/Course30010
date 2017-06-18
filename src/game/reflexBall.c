#include <eZ8.h>
#include <sio.h>

#include "reflexBall.h"
#include "block.h"
#include "game.h"
#include "highscore.h"
#include "../api/menu.h"
#include "../hif/timer.h"
#include "../hif/console.h"

int tickCounter = 1;
int LEDFlag = 0;
int ms10Tick = 1;
int ms100Tick = 1;
int ms50Tick = 0;
int debounceGuard = 1;
int moveFlag = 0;
int strikerMoveFlag = 0;

#pragma interrupt
void interruptHandler() {
  tickCounter++;
  ms10Tick++;
  ms50Tick++;
  ms100Tick++;
  debounceGuard++;
  LEDFlag = 1;

  if (ms10Tick > 10)
  {
    ms10Tick = 0;
    moveFlag = 1;
  }

  if (ms100Tick > 100)
  {
    strikerMoveFlag = 1;
    ms100Tick = 0;
  }

  if (ms50Tick > 50)
  {
    ms50Tick = 0;
  }

  if (debounceGuard > 300) {
    debounceGuard = 0;
  }

  if (tickCounter > 1000)
  {
    tickCounter = 0;
  }
}

/* STATE TABLE:
 * 1    : Menu
 * 2    : Playing
 * 3    : Highscore
 * 1337 : Boss mode
 *
 */

void runReflexBall() {
  int i, j;
  int currentPlayerScore = 0;
  int highscores[10];
  int state = 1; // renderMenu=1, waitForPlaySelection, playing, lost

  initTimer();
  SET_VECTOR(TIMER0, interruptHandler); // Can't avoid this call sadly.
  startTimer();
  clrscr();

  for (i = 0; i < 10; i++)
  {
    highscores[i] = 0;
  }

  while (1) {
    switch (state) {
      case 1: // render menu state
        state = defaultMenu(&tickCounter);
        break;
      case 2:
        state = game(&moveFlag, &debounceGuard, &strikerMoveFlag, &currentPlayerScore, &LEDFlag);
        // Update the highscore list.
        for (i = 0; i < 10; i++)
        {
          if (currentPlayerScore > highscores[i])
          {
            for (j = 9; j > i; j--)
            {
              highscores[j] = highscores[j-1];
            }
            highscores[i] = currentPlayerScore;
            break;
          }
        }        
        currentPlayerScore = 0;
        break;
      case 3:
        state = highscore(highscores, &debounceGuard, &ms50Tick);
        break;
      default:
        break;
    };
  }
}
