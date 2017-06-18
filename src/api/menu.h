#ifndef _DTU_MENU_
#define _DTU_MENU_

#include "CircularDoublyLinkedList.h"


typedef struct {
	int state;
	char name[30];
} MenuItem;


typedef struct {
  int mx;
  int my;
  int cx;
  int cy;
  Node* items;
} Menu;


int defaultMenu(int* tick);

#endif /*! _DTU_MENU_ */
