#include <eZ8.h>

#include "../hif/timer.h"
#include "../hif/console.h"

#include "../api/menu.h"

#include "reflexBall.h"
#include "block.h"
#include "game.h"
#include "highscore.h"

static int tick = 0;
static int LEDFlag = 0;
static int ms10Tick = 1;
static int ms50Tick = 0;
static int ms100Tick = 1;
static int ms200Tick = 0;
static int debounceGuard = 1;
static int moveFlag = 0;
static int strikerMoveFlag = 0;

#pragma interrupt
void interruptHandler() {
  tick++;
  ms10Tick++;
  ms50Tick++;
  ms200Tick++;
  ms100Tick++;
  debounceGuard++;
  LEDFlag = 1;

  if (ms10Tick > 40)
  {
    ms10Tick = 0;
    moveFlag = 1;
  }

  if (ms50Tick > 50)
  {
    ms50Tick = 0;
  }

  if (ms100Tick > 130)
  {
    ms100Tick = 0;
    strikerMoveFlag = 1;
  }

  if (ms200Tick > 200)
  {
    ms200Tick = 0;
  }

  if (debounceGuard > 300) {
    debounceGuard = 0;
  }

  if (tick > 1000)
  {
    tick = 0;
  }
}


void runReflexBall() {
  int state = 1;

  int i, j;
  int currentPlayerScore = 0;

  int highscores[10];


  for (i = 0; i < 10; i++)
  {
    highscores[i] = 0;
  }


  initTimer();
  SET_VECTOR(TIMER0, interruptHandler); // Can't avoid this call sadly.
  startTimer();
  clrscr();


  while (1) {
    switch (state) {
      case 1:
        state = defaultMenu(&tick);
        break;
      case 2:
        state = game(&moveFlag, &debounceGuard, &strikerMoveFlag, &currentPlayerScore, &LEDFlag);
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
    }
  }
}
