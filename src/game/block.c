#include <eZ8.h>
#include <sio.h>

#include "block.h"
#include "../hif/console.h"

Block generateBlock() {
  Block block;
  block.upperLeftX = 15;
  block.upperLeftY = 5;
  block.width = 4;
  block.height = 2;
  block.durability = 3;
  block.indestructible = 1;
  return block;
}

void renderBlock(Block block) {
  int i;
  gotoxy(block.upperLeftX, block.upperLeftY);
  for (i = 0; i < block.height; i++)
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
    gotoxy(block.upperLeftX, block.upperLeftY + 1);
  }
  // Spin it baby.
  // while(1) {
  //   continue;
  // }
}

