#ifndef _DTU_BLOCK_
#define _DTU_BLOCK_

// Should be moved to more generic lib. dno where?

#include "../api/vector.h"

typedef struct
{
  Vector position;
  int width;
  int height;
  int durability; // How many hits can this thing take?
  int indestructible; // For wall blocks.
} Block;


void renderBlock(Block block);


// Block generateBlock();

#endif /*! _DTU_BLOCK_ */
