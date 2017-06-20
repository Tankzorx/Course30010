#include <eZ8.h>

void initTimer() {

  DI();

  T0CTL = 0x19;

  T0H = 0x0;
  T0L = 0x1;

  T0RH = 0x09;
  T0RL = 0x00;

  // ENABLE TIMER INTERRUPT Set to level 3.
  IRQ0ENH |= 0x20;
  IRQ0ENL |= 0x20;

}

void disableTimer() {
  DI();
  T0CTL &= 0x7F;
}

void startTimer() {
  EI();
  T0CTL |= 0x80;
}
