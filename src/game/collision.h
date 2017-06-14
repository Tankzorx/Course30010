#ifndef _DTU_COLLISION_
#define _DTU_COLLISION_

#include "ball.h"
#include "block.h"
#include "striker.h"

int detectCollisionBallBlock(Block block, Ball ball);

int detectCollisionBallStriker(Striker striker, Ball ball);



#endif /*! _DTU_COLLISION_ */
