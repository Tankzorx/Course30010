#ifndef _DTU_MENU_
#define _DTU_MENU_


typedef struct  {
	int stateNum;
	char str[30];
} MenuItem;

int menu(MenuItem items[]);

#endif /*! _DTU_MENU_ */