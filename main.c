#include <sio.h>

#include "./src/game/reflexBall.h"


void main() {
  init_uart(_UART0, _DEFFREQ, _DEFBAUD);
  runReflexBall();
  do { } while (1);
}
