#include <eZ8.h>
#include <sio.h>

#include "menu.h"
#include "../hif/buttonInput.h"
#include "../hif/console.h"

// MenuItem[] generateMenu() {
//   MenuItem items[2] = {{2, "Play Game" }, {3, "High Score"}};
//   return items;
// }

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

void selectNext(MenuItem items[], int* selectedMenuItem, int numItems) {
  if (*selectedMenuItem >= numItems - 1) // If we're already on the last option,
  {                                 // We wrap around and select 0th option.
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
int menu(MenuItem items[]) {
  int selectedMenuItem = 0;
  // int spamSafety = 0;
  char lastClicked = 0;
  int numItems = getNumItems(items);


  // Initial rendering. 
  render(items, selectedMenuItem);
  // gotoxy(25,25);
  // printf("Num items: %d\n", numItems);

  // cuurrentreadkey
  // while(cuurrentreadkey ){
  // MAGNUS: SLEEP STATE.
  // }

  while (1) {
    switch (readkey()) {
      case 0: // Nothing clicked
        if (lastClicked == 0) { continue; } // Guard against click spam.
          lastClicked = 0;
        break;
      case 1: // PF7 clicked. // Assume this is "select next"
        if (lastClicked == 1) { continue; } // Guard against click spam.
        // gotoxy(25,25);
        // printf("lastClicked: %d\n", lastClicked);
        selectNext(items, &selectedMenuItem, numItems);
        lastClicked = 1;
        break;
      case 2: // PF6 clicked // Assume this is "select previous"
        if (lastClicked == 2) { continue; } // Guard against click spam.
        // gotoxy(25,25);
        // printf("lastClicked: %d\n", lastClicked);
        // return;
        selectPrev(items, &selectedMenuItem, numItems);
        lastClicked = 2;
        break;
      case 4: // PD3 clicked // Assume this is 'select this option'
        if (lastClicked == 4) { continue; } // Guard against click spam.
        // gotoxy(25,25);
        // printf("lastClicked: %d\n", lastClicked);
        return items[selectedMenuItem].stateNum;
        break;
      case 6: // PF6+PD3 clicked // Dunno what should happen here.
        if (lastClicked == 6) { continue; } // Guard against click spam.
        lastClicked = 6;
        break;
      case 7: // PF6+PD3+PF7 clicked // BOSS KEY ;)
        if (lastClicked == 7) { continue; } // Guard against click spam.
        return 1337;
        break;

    }
  }
}