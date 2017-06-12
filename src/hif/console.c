#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "console.h"

#define ESC 0x1B

void fgcolor(int foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  int type = 22;             // normal text
  if (foreground > 7) {
    type = 1;                // bold text
    foreground -= 8;
  }
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(int background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
                way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(int foreground, int background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  int type = 22;             // normal text
  if (foreground > 7) {
    type = 1;                // bold text
    foreground -= 8;
  }
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr() {
  printf("%c[2J", ESC);
}

void clreol() {
  printf("%c[K", ESC);
}

void gotoxy(int x, int y) {
  printf("%c[%d;%dH", ESC, y, x);
}

void underline(char on) {
  int code = on ? 4 : 24;
  printf("%c[%dm", ESC, code);
}

void blink(char on) {
  int code = on ? 5 : 25;
  printf("%c[%dm", ESC, code);
}


void reset() {
  printf("%c[%d;%d;%d;%d;%d;%dm", ESC, 22,23,24,25,26,27);
}