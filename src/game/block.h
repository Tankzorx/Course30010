#ifndef _DTU_BLOCK_
#define _DTU_BLOCK_

#include "../api/vector.h"

typedef struct
{
  Vector position;
  long width;
  long height;
  int durability;
  int indestructible;
} Block;


void renderBlock(Block block);
Block* generateWalls();
void generateDefaultMap(Block blockMap[]);
void renderBlockMap(Block blockMap[]);

#endif /*! _DTU_BLOCK_ */
