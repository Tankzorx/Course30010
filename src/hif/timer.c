#include <eZ8.h>

void initTimer() {

  DI();
  // Init Timer and interrupt settings.

  T0CTL = 0x19;
  // timer 0 byte registers set initial value:
  T0H = 0x0;
  T0L = 0x1;
  // Set reload stuff 5A00
  T0RH = 0x09; // RH high
  T0RL = 0x00; // RL low

  // ENABLE TIMER INTERRUPT Set to level 3.
  IRQ0ENH |= 0x20;
  IRQ0ENL |= 0x20;
  // ENABLE TIMER
  //SET_VECTOR(TIMER0, interruptHandler);

}

void disableTimer() {
  DI();
  T0CTL &= 0x7F;
}

void startTimer() {
  EI();
  T0CTL |= 0x80;
}