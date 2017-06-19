#include <sio.h>
#include <stdlib.h>

#include "../hif/console.h"
#include "../hif/buttonInput.h"

#include "../api/boss.h"
#include "../api/Debounce.h"
#include "../api/CircularDoublyLinkedList.h"

#include "highscore.h"


Highscore* initializeDefaultHighscore() {
  Highscore* highscore;

  highscore = malloc(sizeof(*highscore));

  highscore->mx = 10;
  highscore->my = 10;
  highscore->cx = 0;
  highscore->cy = 5;
  highscore->items = NULL;

  return highscore;
}


Highscore* insertHighscore(Highscore* highscore, int score) {
  Node* items;

  HighscoreItem highscoreItem;
  highscoreItem.score = score;

  items = highscore->items;

  gotoxy(12,12);
  printf("FATTTTTTTTTTfafaafafa");

  if( items == NULL) {
    printf("FATTTTTTTTTTTTTTTTTTTIINo scores yet");
    items = singleton(&highscore);
  } else {
    printf("FATTTTTTTAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAyet");
    items = insert(items, &highscoreItem);
  }

  highscore->items = items;

  return highscore;
}


void clearHighscore(Highscore* highscore) {
  HighscoreItem* highscoreItem = highscore->items->data;

  gotoxy(highscore->mx, highscore->my);
  printN(12, ' ');
}


void renderHighscore(Highscore* highscore) {
  HighscoreItem* highscoreItem = highscore->items->data;

  gotoxy(highscore->mx, highscore->my);

  if( highscore->items == NULL) {
    printf("%s", "No scores yet");
  } else {
    printf("Score: %d", highscoreItem->score);
  }
}


void renderHighscoreControls(Highscore* highscore) {
  HighscoreItem* highscoreItem = highscore->items->data;

  gotoxy(highscore->mx + highscore->cx, highscore->my + highscore->cy);
  printf("PF7: Next - PF6: Previous - PD3: Back");
}


void prevHighscore(Highscore* highscore) {
  highscore->items = prev(highscore->items);
}


void nextHighscore(Highscore* highscore) {
  highscore->items = next(highscore->items);
}


int listenHighscore(Highscore* highscore, int* tick) {

  char previousKey, currentKey;
  sleep(tick, 800);

  while (1) {
    currentKey = readkey();

    sleep(tick, 30);

    if(currentKey != readkey()){
      continue;
    }

    if(previousKey == currentKey){
      continue;
    }

    previousKey = currentKey;

    switch (currentKey) {
      case 1:
        clearHighscore(highscore);
        nextHighscore(highscore);
        renderHighscore(highscore);
        break;
      case 2:
        clearHighscore(highscore);
        prevHighscore(highscore);
        renderHighscore(highscore);
        break;
      case 3:
        renderBossMode();
        sleep(tick, 300);
        spin();
        renderHighscoreControls(highscore);
        renderHighscore(highscore);
        break;
      case 4:
        return 1;
        break;
      default:
        break;
    }
  }
}


int highscorex(Highscore* highscore, int* tick) {
//  clrscr();
  renderHighscore(highscore);
  renderHighscoreControls(highscore);
  listenHighscore(highscore, tick);
}
