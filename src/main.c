#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routine

// #include "./game/game.h"
int tickCounter = 0;
#pragma interrupt
void interruptHandler() {
  tickCounter++;
}

void main() {
	init_uart(_UART0, _DEFFREQ, _DEFBAUD);  // set-up UART0 to 57600, 8n1
	// runGame();
	DI();
	// Init Timer and interrupt settings.
	T0CTL = 0x19;
	// timer 0 byte registers set initial value:
	T0H = 0x0;
	T0L = 0x1;
	// Set reload stuff 5A00
	T0RH = 0x0A; // RH high
	T0RL = 0x00; // RL low
	// ENABLE TIMER INTERRUPT Set to level 3.
	IRQ0ENH |= 0x20;
	IRQ0ENL |= 0x20;
	// ENABLE TIMER
	SET_VECTOR(TIMER0, interruptHandler);
	EI();

	T0CTL |= 0x80;
	do {
	} while (1);
}