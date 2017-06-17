#include <eZ8.h>
#include <sio.h>

#include "menu.h"
#include "boss.h"
#include "../hif/timer.h"
#include "../hif/buttonInput.h"
#include "../hif/console.h"

int getNumItems(MenuItem items[]) {
  return sizeof(items); // THIS ANNOYS ME. This returns the correct answer??? DNO.
}

void render(MenuItem items[], int selectedIndex) {
  int i;
  for (i = 0; i < getNumItems(items); i++) {
    gotoxy(10, 10 + i*5);
    clreol();
    if (i == selectedIndex) {
      blink(1);
    }
  printf("%s", items[i].str);
  blink(0);
  }

  
}

void selectNext(MenuItem items[], int* selectedMenuItem, int numItems) {
  if (*selectedMenuItem >= numItems - 1) // If we're already on the last option,
  {                                      // We wrap around and select 0th option.
    *selectedMenuItem = 0;
    render(items, 0);
  } else {
    *selectedMenuItem = *selectedMenuItem + 1;
    render(items, *selectedMenuItem);
  }
  // gotoxy(35,35);
  // printf("selectNext. selectedMenuItem %d", *selectedMenuItem);
}

void selectPrev(MenuItem items[], int* selectedMenuItem, int numItems) {
  if (*selectedMenuItem <= 0) // If we're already on the last option,
  {                          // We wrap around and select 0th option.
    render(items, numItems - 1);
    *selectedMenuItem = numItems - 1;
  } else {
    *selectedMenuItem = *selectedMenuItem - 1;
    render(items, *selectedMenuItem);
  }
  // gotoxy(35,45);
  // printf("selectPrev. selectedMenuItem %d", *selectedMenuItem);
}
int menu(MenuItem items[], int* debounceGuard, int* ms50Tick) {
  int keyRead = 0;
  int selectedMenuItem = 0;
  // int spamSafety = 0;
  int numItems = getNumItems(items);


  // Initial rendering. 
  clrscr();
  render(items, selectedMenuItem);

  gotoxy(50,getNumItems(items)*5 + 15);
  printf("Controls:");
  gotoxy(50,getNumItems(items)*5 + 16);
  printf("PF7: Select Next");
  gotoxy(50,getNumItems(items)*5 + 17);
  printf("PF6: Select Previous");
  gotoxy(50,getNumItems(items)*5 + 18);
  printf("PD3: Choose Current Selection");
  // gotoxy(25,25);
  // printf("Num items: %d\n", numItems);

  // cuurrentreadkey
  // while(cuurrentreadkey ){
  // MAGNUS: SLEEP STATE.
  // }
  
  // Wait 'debounceGuard' milliseconds before activating controls
  *debounceGuard = 1;
  while(*debounceGuard != 0) {}

  while (1) {
    switch (readkey()) {
      case 1: // PF7 clicked. // Assume this is "select next"
        *ms50Tick = 1;
        while (*ms50Tick != 0) {}
        if (readkey() == 1) {
          selectNext(items, &selectedMenuItem, numItems);
          *debounceGuard = 1;
          while(*debounceGuard != 0) {}
        } 
        break;
      case 2: // PF6 clicked // Assume this is "select previous"
        // gotoxy(25,25);
        // printf("lastClicked: %d\n", lastClicked);
        // return;
        *ms50Tick = 1;
        while (*ms50Tick != 0) {}
        if (readkey() == 2) {
          selectPrev(items, &selectedMenuItem, numItems);
          *debounceGuard = 1;
          while(*debounceGuard != 0) {}
        } 
        break;
      case 4: // PD3 clicked // Assume this is 'select this option'
        return items[selectedMenuItem].stateNum;
        break;
      case 6: // PF6+PD3 clicked // Dunno what should happen here.
        break;
      case 7: // PF6+PD3+PF7 clicked // BOSS KEY ;)
        renderBossMode();
        *debounceGuard = 1;
        while(*debounceGuard != 0) {}
        while(readkey() == 0) {}
        render(items, selectedMenuItem);
        break;

    }
  }
}