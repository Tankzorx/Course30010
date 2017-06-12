#ifndef _DTU_CONSOLE_
#define _DTU_CONSOLE_

void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();
void reset();
void clrscr();
void clreol();
void gotoxy(int x, int y);
void underline(char on);
void blink(char on);

#endif /*! _DTU_CONSOLE_ */