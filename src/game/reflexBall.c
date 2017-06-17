#include <eZ8.h>
#include <sio.h>

#include "reflexBall.h"
#include "block.h"
#include "game.h"
#include "../api/menu.h"
#include "../hif/console.h"


/* STATE TABLE:
 * 1    : Menu
 * 2    : Playing
 * 1337 : Boss mode
 *
 */

void runReflexBall() {
  int i, j;
  MenuItem items[2] = {{2, "Play Game" }, {3, "High Score"}};
  int state = 2; // renderMenu=1, waitForPlaySelection, playing, lost

  clrscr();

  while (1) {
    switch (state) {
      case 1: // render menu state
        state = menu(items);
        break;
      case 2:
        // clrscr();
        // for (i = 0; i < 30; i++)
        // {
        //   renderBlock(blockMap[i]);
        // }
        // return; // Premature return for testing.
        state = game();
        break;
      case 1337:
        // BOSS STATE.
        break;
      default:
        break;
    };
  }
}