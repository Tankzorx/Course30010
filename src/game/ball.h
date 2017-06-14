#ifndef _DTU_BALL_
#define _DTU_BALL_

// Should be moved to more generic lib. dno where?
#include "../api/vector.h"

typedef struct
{
  Vector position;
  Vector velocity;
  Vector lastRenderPosition;
  int radius;
} Ball;


// void moveBallRightN(Ball*  ball, int n);
// void moveBallLeftN(Ball*  ball, int n);
// void moveBallUpN(Ball*  ball, int n);
// void moveBallDownN(Ball*  ball, int n);

void moveBall(Ball* ball);

void clearBall(Ball* ball);
void renderBall(Ball* ball);

#endif /*! _DTU_BALL_ */
