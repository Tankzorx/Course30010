#include <eZ8.h>
#include <sio.h>             // special encore serial i/o routines

#include "game.h"
#include "block.h"
#include "ball.h"
#include "../api/vector.h"
#include "collision.h"
#include "../hif/console.h"
#include "../hif/buttonInput.h"
#include "../hif/timer.h"
#include "striker.h"



int tickCounter = 1;
int ms10Tick = 1;
int ms50Tick = 1;
int ms100Tick = 1;
int ms500Tick = 1;
char readPosFlag = 0;
#pragma interrupt
void interruptHandler() {
  tickCounter++;
  ms10Tick++;
  ms50Tick++;
  ms100Tick++;
  ms500Tick++;

  if (ms10Tick > 10)
  {
    ms10Tick = 0;
  }

  if (ms50Tick > 50)
  {
    ms50Tick = 0;
  }  

  if (ms100Tick > 100)
  {
    ms100Tick = 0;
  }

  if (ms500Tick > 500) {
    ms500Tick = 0;
  }

  if (tickCounter > 1000)
  {
    // printf("TICKED TIMER.\n");
    tickCounter = 0;
  }
}



// gameState som input skal nok gøres senere.
int game() {
  Striker striker;
  char keyRead;
  int i, j;
  Vector initBallVelocity;
  Vector initBallPosition;
  int moves[4] = { 1, 1, 1, 0 };
  int collisionState;
  int collisionStateStriker;
  // long collisionStateAUX;
  // Movement movement;
  int state = 0;
  Block blockMap[100];
  Ball ball;
  Block b;
  Vector auxVector;

  // Initialize striker
  striker.position.x = 90 << 14;
  striker.position.y = 70 << 14;
  striker.width = 15 << 14;

  ball.radius = 1;
  // ball.xPos = 50;
  // ball.yPos = 60;
  // 18.14 format
  initBallPosition.x = 35 << 14;
  initBallPosition.y = 40 << 14;
  initBallVelocity.x = 6 << 7;
  initBallVelocity.y = 6 << 7;
  ball.position = initBallPosition;
  ball.velocity = initBallVelocity;
  ball.lastRenderPosition = initBallPosition;

  generateWalls(blockMap);

  initTimer();
  SET_VECTOR(TIMER0, interruptHandler); // Can't avoid this call sadly.
  startTimer();

  clrscr();
  gotoxy(10,10);
  // printf("Block position: (%d, %d)\n", blockMap[0].position.x >> 14, blockMap[0].position.y >> 14);
  // return;
  renderBlockMap(blockMap);
  renderStriker(&striker);

  while(1) {
    if (ms10Tick == 0) {
      // Move ball and detect collision between ball&blocks.
      moveBall(&ball);
      for (i = 0; i < blockMap[99].indestructible; i++)
      {
        collisionState = detectCollisionBallBlock(blockMap[i], ball);
        handleBlockCollision(&ball, collisionState);
        // break loop when collisionstate > 0.
      }

      // Move striker and detect collision between ball&striker
      keyRead = readkey();
      moveStriker(&striker, keyRead);

      collisionStateStriker = detectCollisionBallStriker(striker, ball);
      if (collisionStateStriker > -1)
      {
        
        handleStrikerCollision(&ball, striker, collisionStateStriker);
        // return;
      }
    }

    if (ms100Tick == 0)
    {
      clearBall(&ball);
      renderBall(&ball);
      clearStriker(&striker);
      renderStriker(&striker);
    }
  }
}