#ifndef _DTU_CONSOLE_
#define _DTU_CONSOLE_

void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();
void clrscr();
void clreol();
void printN(int n, char c);
void gotoxy(int x, int y);
void underline(char on);
void blink(char on);
void reset();

#endif /*! _DTU_CONSOLE_ */