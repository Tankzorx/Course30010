#include <eZ8.h>
#include <sio.h>

#include "block.h"
#include "../hif/console.h"
#include "../api/vector.h"

void generateDefaultBlockMap(Block blockMap[]) {
  int i,j;
  Vector auxVector;
  // Block blockMap[30];
  Block b;
  // This is one way of generating the blockMap:
  // (Shorthand version of struct creation didn't work.)
  // Rows
  // for (i = 0; i < 3; i++) {
  //   // Columns
  //   for (j = 0; j < 10; j++) {
  //     auxVector.x = (long)(15+j*12) << 14;
  //     auxVector.y = (long)(5+i*10) << 14;
  //     b.position = auxVector;
  //     b.width = 10 << 14;
  //     b.height = 8 << 14;
  //     b.durability = 3;
  //     b.indestructible = 1;
  //     blockMap[i*10 + j] = b;
  //   }
  // }
  auxVector.x = (long)(0) << 14;
  auxVector.y = (long)(0) << 14;
  b.position = auxVector;
  b.width = 3 << 14;
  b.height = 70 << 14;
  b.durability = 3;
  b.indestructible = 1;   
  blockMap[0] = b;

  auxVector.x = (long)(195) << 14;
  auxVector.y = (long)(0) << 14;
  b.position = auxVector;
  b.width = 3 << 14;
  b.height = 70 << 14;
  b.durability = 3;
  b.indestructible = 1;   
  blockMap[1] = b;

  auxVector.x = (long)(0) << 14;
  auxVector.y = (long)(0) << 14;
  b.position = auxVector;
  b.width = 195 << 14;
  b.height = 3 << 14;
  b.durability = 3;
  b.indestructible = 1;   
  blockMap[2] = b;


  b.indestructible = 3;
  blockMap[99] = b;

  // return &blockMap[0];
}



void renderBlock(Block block) {
  int i;
  gotoxy(block.position.x >> 14, block.position.y >> 14);
  for (i = 0; i <= block.height >> 14; i++)
  {
    switch (block.durability) {
      case 1:
        printN(block.width >> 14, 'A');
        break;
      case 2:
        printN(block.width >> 14, 'B');
        break;
      case 3:
        printN(block.width >> 14, 'C');
        break;
    }
    gotoxy(block.position.x >> 14, (block.position.y >> 14) + i);
  }
  // Spin it baby.
  // while(1) {
  //   continue;
  // }
}

void renderBlockMap(Block blockMap[]) {
  int i;
  for (i = 0; i < blockMap[99].indestructible; i++)
  {
    renderBlock(blockMap[i]);
  }
}

