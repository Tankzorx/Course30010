#ifndef _DTU_BLOCK_
#define _DTU_BLOCK_

// Should be moved to more generic lib. dno where?

typedef struct
{
  int upperLeftX;
  int upperLeftY;
  int width;
  int height;
  int durability; // How many hits can this thing take?
  int indestructible; // For wall blocks.
} Block;


void renderBlock(Block block);


Block generateBlock();

#endif /*! _DTU_BLOCK_ */
