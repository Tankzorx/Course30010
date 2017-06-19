#include <eZ8.h>
#include <sio.h>

#include <stdlib.h>

#include "../api/CircularDoublyLinkedList.h"
#include "../game/highscore.h"


#include "reflexBall.h"
#include "block.h"
#include "game.h"
#include "highscore.h"
#include "../api/menu.h"
#include "../hif/timer.h"
#include "../hif/console.h"

int tick = 0;
int LEDFlag = 0;
int ms10Tick = 1;
int ms100Tick = 1;
int ms50Tick = 0;
int debounceGuard = 1;
int moveFlag = 0;
int strikerMoveFlag = 0;

#pragma interrupt
void interruptHandler() {
  tick++;
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

  if (tick > 1000)
  {
    tick = 0;
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
  int state = 1;


  //Highscore* highscore;

  /*
  HighscoreItem highscoreItem = { 21 };
  HighscoreItem highscoreItem1 = { 23 };
  HighscoreItem highscoreItem2 = { 999 };
  HighscoreItem highscoreItem3 = { 212 };

  Node* items;
*/

  int i, j;
  int currentPlayerScore = 0;


  initTimer();
  SET_VECTOR(TIMER0, interruptHandler); // Can't avoid this call sadly.
  startTimer();
  clrscr();


/*
  items = singleton(&highscoreItem);
  items = insert(items, &highscoreItem1);
  items = insert(items, &highscoreItem2);
  items = insert(items, &highscoreItem3);

  highscore = malloc(sizeof(*highscore));

  highscore->mx = 10;
  highscore->my = 10;
  highscore->cx = 0;
  highscore->cy = 5;
  highscore->items = NULL;
*/
  //should change:
  //highscore = initializeDefaultHighscore();

  ///highscore = insertHighscore(highscore, 233);
  //highscore = insertHighscore(highscore, 199);
  //insertHighscore(highscore, 3431);

  //printf("%d", highscore.my);
  //highscoreItem = (highscore.items)->data;

  //gotoxy(highscore.mx, highscore.my);
  //printf("lol: %s", highscoreItem->name);


  while (1) {
    switch (state) {
      case 1: // render menu state
        state = defaultMenu(&tick);
        break;
      case 2:
        state = game(&moveFlag, &debounceGuard, &strikerMoveFlag, &currentPlayerScore, &LEDFlag);
        // Update the highscore list.
        // Update the highscore list.
        // Update the highscore list.
        // Update the highscore list.
//        insertHighscore(highscore, currentPlayerScore);
        currentPlayerScore = 0;
        break;
      case 3:
        //state = highscorex(highscore, &tick);
        break;
      default:
        break;
    }
  }
}
