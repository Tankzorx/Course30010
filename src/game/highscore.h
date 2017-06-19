#ifndef _DTU_HIGHSCORE_
#define _DTU_HIGHSCORE_

#include "../api/CircularDoublyLinkedList.h"


typedef struct {
	int score;
} HighscoreItem;


typedef struct {
  int mx;
  int my;
  int cx;
  int cy;
  Node* items;
} Highscore;


int highscorex(Highscore* highscore, int* tick);

Highscore* initializeDefaultHighscore();

Highscore* insertHighscore(Highscore* highscore, int score);


#endif /*! _DTU_HIGHSCORE_ */
