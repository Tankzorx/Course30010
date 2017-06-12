#include <eZ8.h>
#include <sio.h>

#include "game.h"
#include "block.h"
#include "../hif/timer.h"
#include "../api/menu.h"


/* STATE TABLE:
 * 1    : Menu
 * 2    : Playing
 * 1337 : Boss mode
 *
 */

int tickCounter = 1;
#pragma interrupt
void interruptHandler() {
  tickCounter++;
  if (tickCounter > 1000)
  {
    // printf("TICKED TIMER.\n");
    tickCounter = 0;
  }
}

void runGame() {
  int i, j;
  Block blockMap[30];
  Block b;
  MenuItem items[2] = {{2, "asd" }, {3, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}};
  int state = 2; // renderMenu=1, waitForPlaySelection, playing, lost

  // This is one way of generating the blockMap:
  // (Shorthand version of struct creation didn't work.)
  // Rows
  for (i = 0; i < 3; i++) {
    // Columns
    for (j = 0; j < 10; j++) {
      b.upperLeftX = j*7; // 7 - width = horizontal distance between blocks
      b.upperLeftY = i*7; // 7- height = vertical distance between blocks.
      b.width = 4;
      b.height = 2;
      b.durability = 3;
      b.indestructible = 1;
      blockMap[i + j] = b;
    }
  }
  // Init timer sets the reloadnumber etc.
  // We want to set it up so that the timer is interrupts every millisecond.
  initTimer();
  SET_VECTOR(TIMER0, interruptHandler); // Can't avoid this call sadly.
  startTimer();

  while (1) {
    switch (state) {
      case 1: // render menu state
        state = menu(items);
        break;
      case 2:
        for (i = 0; i < 30; i++)
        {
          renderBlock(blockMap[i]);
        }
        return; // Premature return for testing.
        state = 2;
        break;
      case 1337:
        // BOSS STATE.
        break;
      default:
        break;
    };
  }
}