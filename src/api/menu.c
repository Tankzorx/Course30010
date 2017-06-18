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


void renderControls(Menu* menu) {
  MenuItem* menuItem = menu->items->data;

  gotoxy(menu->mx + menu->cx, menu->my + menu->cy);
  printf("PF7: Next - PF6: Previous - PD3: Select");
}


void next(Menu* menu) {
  menu->items = menu->items->next;
}


void prev(Menu* menu) {
  menu->items = menu->items->prev;
}


int state(Menu* menu) {
  MenuItem* menuItem = menu->items->data;
  return menuItem->state;
}


int listen(Menu* menu, int* tick){

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
        next(menu);
        renderMenu(menu);
        break;
      case 2:
        clearMenu(menu);
        prev(menu);
        renderMenu(menu);
        break;
      case 3:
        renderBossMode();
        sleep(tick, 300);
        spin();
        renderControls(menu);
        break;
      case 4:
        return state(menu);
        break;
    }
  }
}


Menu* fromNode(Node* items) {
  Menu* menu;
  menu = malloc(sizeof(*menu));

  menu->items = items;

  return menu;
}


int defaultMenu(int* tick) {
  Menu* menu;

  MenuItem play = { 2, "Play Game" };
  MenuItem highScore = { 3, "High Score" };
  MenuItem exit = { 4, "Exit - Not implemented" };

  Node* items = singleton(&play);
  insert(items, &highScore);
  insert(items, &exit);

  menu = fromNode(items);
  menu->mx = 10;
  menu->my = 10;
  menu->cx = 0;
  menu->cy = 5;

  renderControls(menu);
  renderMenu(menu);

  //why i dont need return?
  listen(menu, tick);
}
