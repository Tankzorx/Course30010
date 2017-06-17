#ifndef _DTU_BLOCK_
#define _DTU_BLOCK_

// Should be moved to more generic lib. dno where?

#include "../api/vector.h"

typedef struct
{
  Vector position;
  long width;
  long height;
  char durability; // How many hits can this thing take?
  char indestructible; // For wall blocks.
} Block;


void renderBlock(Block block);

Block* generateWalls();
void generateDefaultMap(Block blockMap[]);
void renderBlockMap(Block blockMap[]);
// Block generateBlock();

#endif /*! _DTU_BLOCK_ */
