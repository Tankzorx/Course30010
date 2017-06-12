#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routine

#include "menu.h"
#include "../hif/buttonInput.h"
#include "../hif/console.h"

int getNumItems(MenuItem items[]) {
  return sizeof(items); // THIS ANNOYS ME. This returns the correct answer??? DNO.
}

void render(MenuItem items[], int selectedIndex) {
  int i;
  clrscr();
  for (i = 0; i < getNumItems(items); i++) {
    gotoxy(5,i*5);
    if (i == selectedIndex) {
      blink(1);
    }
  printf("%s", items[i].str);
  blink(0);
  }
}

void selectNext(MenuItem items[], int selectedMenuItem, int numItems) {
  if (selectedMenuItem >= numItems) // If we're already on the last option,
  {                                 // We wrap around and select 0th option.
    render(items, 0);
  } else {
    selectedMenuItem++;
    render(items, selectedMenuItem);
  }
}

void selectPrev(MenuItem items[], int selectedMenuItem, int numItems) {
  if (selectedMenuItem <= 0) // If we're already on the last option,
  {                          // We wrap around and select 0th option.
    render(items, numItems - 1);
  } else {
    selectedMenuItem--;
    render(items, selectedMenuItem);
  }
}
int menu(MenuItem items[]) {
  int selectedMenuItem = 0;
  char lastClicked = 0;
  int numItems = getNumItems(items);

  printf("Num items: %d\n", numItems);

  // Initial rendering.
  render(items, selectedMenuItem);

  while (1) {
    switch (readkey()) {
      case 0: // Nothing clicked
        // Do nothing.
        break;
      case 1: // PF7 clicked. // Assume this is "select next"
        if (lastClicked == 1) { continue; } // Guard against click spam.
        selectNext(items, selectedMenuItem, numItems);
        lastClicked = 1;
        break;
      case 2: // PF6 clicked // Assume this is "select previous"
        if (lastClicked == 2) { continue; } // Guard against click spam.
        selectPrev(items, selectedMenuItem, numItems);
        lastClicked = 2;
        break;
      case 4: // PD3 clicked // Dunno what should happen here.
        if (lastClicked == 4) { continue; } // Guard against click spam.
        lastClicked = 4;
        break;
      case 6: // PF6+PD3 clicked // Dunno what should happen here.
        if (lastClicked == 6) { continue; } // Guard against click spam.
        lastClicked = 6;
        break;
      case 7: // PF6+PD3+PF7 clicked // Dunno what should happen here.
        if (lastClicked == 7) { continue; } // Guard against click spam.
        return 1337;
        break;

    }
  }
}