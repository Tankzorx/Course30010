#ifndef _DTU_BALL_
#define _DTU_BALL_

#include "../api/vector.h"

#include "striker.h"

typedef struct
{
  Vector position;
  Vector velocity;
  Vector lastRenderPosition;
} Ball;

void moveBall(Ball* ball);

void handleBlockCollision(Ball* ballPtr, int collisionState);
void handleStrikerCollision(Ball* ballPtr, Striker* striker, int collisionArea);
void moveUpEpsilonBall(Ball* ball);

int ballIsDead(Ball ball, int screenHeight);

void clearBall(Ball* ball);
void renderBall(Ball* ball);

#endif /*! _DTU_BALL_ */
