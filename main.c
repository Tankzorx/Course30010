#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routine

// #include "./game/game.h"
#include "./src/hif/timer.h"
int tickCounter = 0;
#pragma interrupt
void interruptHandler() {
  tickCounter++;
}

void main() {
	init_uart(_UART0, _DEFFREQ, _DEFBAUD);  // set-up UART0 to 57600, 8n1
	// runGame();
	initTimer();
	SET_VECTOR(TIMER0, interruptHandler);
	startTimer();
	do {
		if (tickCounter == 1000) {
			printf("tick1000");
			tickCounter = 0;
		} 
	} while (1);
}