#ifndef _DTU_STRIKER_
#define _DTU_STRIKER_

// Should be moved to more generic lib. dno where?

#include "../api/vector.h"

typedef struct 
{
  Vector position;
  Vector lastRenderPosition;
  long width;
} Striker;

void renderStriker(Striker *striker);
void clearStriker(Striker *striker);

void moveStriker(Striker *striker, char buttonInput);



#endif /*! _DTU_STRIKER_ */
