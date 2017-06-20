#include <sio.h>
#include <stdlib.h>

#include "../hif/console.h"
#include "../hif/buttonInput.h"

#include "Debounce.h"
#include "String.h"
#include "boss.h"
#include "menu.h"


void clearMenu(Menu* menu) {
  MenuItem* menuItem = menu->items->data;

  gotoxy(menu->mx, menu->my);
  printN(length(menuItem->name), ' ');
}


void renderMenu(Menu* menu) {
  MenuItem* menuItem = menu->items->data;

  gotoxy(menu->mx, menu->my);
  printf("%s", menuItem->name);
}


void renderMenuControls(Menu* menu) {
  MenuItem* menuItem = menu->items->data;

  gotoxy(menu->mx + menu->cx, menu->my + menu->cy);
  printf("PF7: Next - PF6: Previous - PD3: Select");
}


void nextMenu(Menu* menu) {
  menu->items = next(menu->items);
}


void prevMenu(Menu* menu) {
  menu->items = prev(menu->items);
}


int state(Menu* menu) {
  MenuItem* menuItem = menu->items->data;
  return menuItem->state;
}


int listenMenu(Menu* menu, int* tick){

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
        clearMenu(menu);
        nextMenu(menu);
        renderMenu(menu);
        break;
      case 2:
        clearMenu(menu);
        prevMenu(menu);
        renderMenu(menu);
        break;
      case 3:
        renderBossMode();
        sleep(tick, 300);
        spin();
        renderMenuControls(menu);
        renderMenu(menu);
        break;
      case 4:
        free(menu);
        return state(menu);
        break;
    }
  }
}


int menux(Menu* menu, int* tick) {
  clrscr();

  renderMenuControls(menu);
  renderMenu(menu);

  listenMenu(menu, tick);
}


Menu* menuFromNode(Node* items) {
  Menu* menu;
  menu = malloc(sizeof(*menu));

  menu->items = items;

  return menu;
}


int defaultMenu(int* tick) {
  Menu* menu;

  MenuItem play = { 2, "Play Game" };
  MenuItem highScore = { 3, "High Score" };

  Node* items;

  items = singleton(&play);
  items = insert(items, &highScore);

  menu = menuFromNode(items);
  menu->mx = 75;
  menu->my = 35;
  menu->cx = 0;
  menu->cy = 5;

  return menux(menu, tick);
}
