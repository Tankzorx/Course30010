#include <eZ8.h>
#include <sio.h>             // special encore serial i/o routines

#include "game.h"
#include "block.h"
#include "ball.h"
#include "../api/boss.h"
#include "../api/vector.h"
#include "../api/sincos.h"
#include "collision.h"
#include "../hif/console.h"
#include "../hif/buttonInput.h"
#include "../hif/timer.h"
#include "striker.h"

int tickCounter = 1;
int ms10Tick = 1;
int blocksAlive = 0;
int ms50Tick = 1;
int ms100Tick = 1;
int debounceGuard = 1;
int moveFlag = 0;
int strikerMoveFlag = 0;
char readPosFlag = 0;
#pragma interrupt
void interruptHandler() {
  tickCounter++;
  ms10Tick++;
  ms50Tick++;
  ms100Tick++;
  debounceGuard++;

  if (ms10Tick > 10)
  {
    ms10Tick = 0;
    moveFlag = 1;
  }

  if (ms50Tick > 50)
  {
    ms50Tick = 0;
  }  

  if (ms100Tick > 100)
  {
    strikerMoveFlag = 1;
    ms100Tick = 0;
  }

  if (debounceGuard > 500) {
    debounceGuard = 0;
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
  int collisionState;
  int collisionStateStriker;
  // long collisionStateAUX;
  Block blockMap[100];
  Ball ball;
  Block b;
  Vector auxVector;

  // Initialize striker
  striker.position.x = 65 << 14;
  striker.position.y = 70 << 14;
  striker.width = ((long) 0x0F) << 14;

  // Not used currently.
  ball.radius = 1;
  // 18.14 format
  initBallPosition.x = 70 << 14;
  initBallPosition.y = 60 << 14;
  initBallVelocity.x = 0 << 14;
  initBallVelocity.y = 3 << 14;
  //initBallVelocity.y = 2<<14;
  // initBallVelocity.y = (~initBallVelocity.y)+1;

  ball.position = initBallPosition;
  ball.velocity = initBallVelocity;
  ball.lastRenderPosition = initBallPosition;

  generateWalls(blockMap);
  generateDefaultMap(blockMap);
   
  initTimer();
  SET_VECTOR(TIMER0, interruptHandler); // Can't avoid this call sadly.
  startTimer();

  clrscr();
  // gotoxy(10,10);
  // printf("Block position: (%d, %d)\n", blockMap[0].position.x >> 14, blockMap[0].position.y >> 14);
  // return;
  renderBlockMap(blockMap);
  renderStriker(&striker);

  while(1) {
    if (moveFlag == 1) {
      // Move ball and detect collision between ball&blocks.
      moveBall(&ball);

      if (ballIsDead(ball, 70) == 1)
      {
        return 1; // return menu state for now.
      }

      for (i = 0; i < blockMap[99].indestructible; i++)
      {
        if (blockMap[i].durability > 0 &&
            blockMap[i].indestructible == 0)
        {
          blocksAlive = 1;
        }
        collisionState = detectCollisionBallBlock(blockMap[i], ball);
        handleBlockCollision(&ball, collisionState);
        if (collisionState > 0)
        {
          if (blockMap[i].indestructible == 0)
          {
            blockMap[i].durability = blockMap[i].durability - 1;
            renderBlock(blockMap[i]);
          }
          break;
        }
      }

      // If blocksAlive is 0, then no destructible block is alive.
      if (blocksAlive == 0)
      {
        return 1;
      }
      blocksAlive = 0;


      // Move striker and detect collision between ball&striker
      collisionStateStriker = detectCollisionBallStriker(striker, ball);
      if (collisionStateStriker > -1)
      {
        handleStrikerCollision(&ball, &striker, collisionStateStriker);
        moveUpEpsilonBall(&ball);
      }
      keyRead = readkey();

      // Check if user wants to bossstate

      moveStriker(&striker, keyRead);
      moveFlag = 0;

      if (keyRead == 7)
      {
        renderBossMode();
        debounceGuard = 1;
        while (debounceGuard != 0) {}
        keyRead = readkey();
        while (keyRead == 0) {
          keyRead = readkey();
        }
        renderBlockMap(blockMap);
        renderStriker(&striker);
      }

    }

    if (strikerMoveFlag)
    {

      clearBall(&ball);
      renderBall(&ball);
      clearStriker(&striker);
      renderStriker(&striker);
      strikerMoveFlag = 0;
    }
  }
}