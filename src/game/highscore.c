#include "../hif/console.h"
#include <sio.h>             // special encore serial i/o routines
#include "../hif/buttonInput.h"
#include "../api/boss.h"


void renderHighscore(int highscores[]) {
  int i;
  clrscr();
  for (i = 0; i < 10; i++) {
    gotoxy(10,10 + i*5);
    printf("Player %d:  %d", i, highscores[i]);
  }

  gotoxy(50, 65);
  printf("Click pd3 to go back.");
}


int highscore(int highscores[], int* debounceGuard, int* ms50Tick) {
  char keyRead = 0;
  renderHighscore(highscores);

  // Wait 'debounceGuard' milliseconds before activating controls
  *debounceGuard = 1;
  while(*debounceGuard != 0) {}

  while (1) {
    switch (readkey()) {
      case 0:
        break;
      case 7:
        renderBossMode();
        *debounceGuard = 1;
        while(*debounceGuard != 0) {}
        while(readkey() == 0) {}
        renderHighscore(highscores);
        break;
      case 4:
        *ms50Tick = 1;
        while (*ms50Tick != 0) {}
        if (readkey() == 4) {
          return 1;
        } 
        break;
      default:
        break;
    }
  }
}
