#include <eZ8.h>
#include <sio.h>

#include "block.h"
#include "../hif/console.h"
#include "../api/vector.h"

void generateWalls(Block blockMap[]) {
  int i,j;
  int offset;
  Vector auxVector;
  Block b;

  auxVector.x = (long)(1) << 14;
  auxVector.y = (long)(1) << 14;
  b.position = auxVector;
  b.width = 3 << 14;
  b.height = 70 << 14;
  b.durability = 3;
  b.indestructible = 1;   
  blockMap[0] = b;

  auxVector.x = (long)(195) << 14;
  auxVector.y = (long)(1) << 14;
  b.position = auxVector;
  b.width = 3 << 14;
  b.height = 70 << 14;
  b.durability = 3;
  b.indestructible = 1;   
  blockMap[1] = b;

  auxVector.x = (long)(1) << 14;
  auxVector.y = (long)(2) << 14;
  b.position = auxVector;
  b.width = 195 << 14;
  b.height = 3 << 14;
  b.durability = 3;
  b.indestructible = 1;   
  blockMap[2] = b;

  b.indestructible = 3;
  blockMap[39] = b;

  // return &blockMap[0];
}

void generateDefaultMap(Block blockMap[]) {
  Vector auxVector;
  Block b;
  int i,j;
  // Assume walls are in the blockmap.
  // (Shorthand version of struct creation didn't work.)
  // Rows
  for (i = 0; i < 3; i++) {
    // Columns
    for (j = 0; j < 10; j++) {
      auxVector.x = (long)(25+j*15) << 14;
      auxVector.y = (long)(8+i*10) << 14;
      b.position = auxVector;
      b.width = 10 << 14;
      b.height = 5 << 14;
      b.durability = 3;
      b.indestructible = 0;
      blockMap[i*10 + j + 3] = b;
    }
  }
  blockMap[39].indestructible = blockMap[39].indestructible + i*j;

  // // ONE TEST BLOCK FOR TESTING
  // auxVector.x = (long)(50) << 14;
  // auxVector.y = (long)(20) << 14;
  // b.position = auxVector;
  // b.width = 1 << 14;
  // b.height = 1 << 14;
  // b.durability = 1;
  // b.indestructible = 0;
  // blockMap[3] = b;

  // blockMap[99].indestructible = blockMap[99].indestructible + 2;
}



void renderBlock(Block block) {
  int i;
  gotoxy(block.position.x >> 14, block.position.y >> 14);
  for (i = 0; i <= block.height >> 14; i++)
  {
    if (block.indestructible == 1)
    {
      printN(block.width >> 14, 219);
    } else {
      switch (block.durability) {
        case 0:
          printN(block.width >> 14, ' ');
          break;
        case 1:
          fgcolor(1);
          printN(block.width >> 14, 0xB2);
          break;
        case 2:
          fgcolor(3);
          printN(block.width >> 14, 0xB2);
          break;
        case 3:
          fgcolor(2);
          printN(block.width >> 14, 0xB2);
          break;
      }
    }
    fgcolor(15);
    gotoxy(block.position.x >> 14, (block.position.y >> 14) + i);
  }
  // Spin it baby.
  // while(1) {
  //   continue;
  // }
}

void renderBlockMap(Block blockMap[]) {
  int i;
  for (i = 0; i < blockMap[39].indestructible; i++)
  {
    renderBlock(blockMap[i]);
  }
}

