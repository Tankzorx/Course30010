#include <sio.h>

#include "./src/game/game.h"


void main() {
  init_uart(_UART0, _DEFFREQ, _DEFBAUD);  // set-up UART0 to 57600, 8n1
  runGame();
  do {
  } while (1);
}