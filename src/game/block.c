#include <eZ8.h>
#include <sio.h>

#include "block.h"
#include "../hif/console.h"

// Block generateBlock() {
//   Block block;
//   Vector position;
//   position.x = 15 << 14;
//   position.y = 5 << 14;
//   block.position = position;
//   block.width = 4;
//   block.height = 2;
//   block.durability = 3;
//   block.indestructible = 1;
//   return block;
// }

void renderBlock(Block block) {
  int i;
  gotoxy(block.position.x >> 14, block.position.y >> 14);
  for (i = 0; i <= block.height; i++)
  {
    switch (block.durability) {
      case 1:
        printN(block.width, 'A');
        break;
      case 2:
        printN(block.width, 'B');
        break;
      case 3:
        printN(block.width, 'C');
        break;
    }
    gotoxy(block.position.x >> 14, (block.position.y >> 14) + i);
  }
  // Spin it baby.
  // while(1) {
  //   continue;
  // }
}

