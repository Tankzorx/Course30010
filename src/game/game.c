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
  int i, j;
  Vector initBallVelocity;
  Vector initBallPosition;
  int moves[4] = { 1, 1, 1, 0 };
  int collisionState;
  // long collisionStateAUX;
  // Movement movement;
  int state = 0;
  Block blockMap[30];
  Ball ball;
  Block b;
  Vector auxVector;

  ball.radius = 1;
  // ball.xPos = 50;
  // ball.yPos = 60;
  // 18.14 format
  initBallPosition.x = 54 << 14;
  initBallPosition.y = 55 << 14;
  initBallVelocity.x = 0 << 7;
  initBallVelocity.y = -1 << 13;
  ball.position = initBallPosition;
  ball.velocity = initBallVelocity;
  ball.lastRenderPosition = initBallPosition;


  // This is one way of generating the blockMap:
  // (Shorthand version of struct creation didn't work.)
  // Rows
  for (i = 0; i < 3; i++) {
    // Columns
    for (j = 0; j < 10; j++) {
      auxVector.x = (long)(15+j*12) << 14;
      auxVector.y = (long)(5+i*10) << 14;
      b.position = auxVector;
      b.width = 10 << 14;
      b.height = 8 << 14;
      b.durability = 3;
      b.indestructible = 1;
      blockMap[i*10 + j] = b;
    }
  }

  initTimer();
  SET_VECTOR(TIMER0, interruptHandler); // Can't avoid this call sadly.
  startTimer();

  clrscr();
  gotoxy(10,10);
  // printf("Block position: (%d, %d)\n", blockMap[0].position.x >> 14, blockMap[0].position.y >> 14);
  // return;
  for (i = 0; i < 30; i++)
  {
    renderBlock(blockMap[i]);
  }

  while(1) {
    if (ms50Tick == 0) {
      moveBall(&ball);
      for (i = 0; i < 30; i++)
      {
        collisionState = detectCollisionBallBlock(blockMap[i], ball);
        if (collisionState > 0)
        {
          flipY(&ball.velocity);
          gotoxy(60,60); // TEST COLLISION.
          printf("Block nr: %d\n", i);
          printf("Collision state: %d\n", collisionState);
          // return;
        }
      }
    }

    if (ms50Tick == 0)
    {
      clearBall(&ball);
      renderBall(&ball);
      // moveBall(&ball);      


      // moveBallRightN(&ball, 1);
      // moveBallUpN(&ball, 1);
      // moveBall(&ball, movePattern);
      // switch (movement.movePattern[movement.currentMove]) {
      //   case 0:
      //     moveBallUpN(&ball, 1);
      //     break;
      //   case 1:
      //     moveBallRightN(&ball, 1);
      //     break;
      //   case 2:
      //     moveBallLeftN(&ball, 1);
      //     break;
      //   case 3:
      //     moveBallDownN(&ball, 1);
      //     break;
      //   default: 
      //     break;
      // }
      // movement.currentMove++;
      // if (movement.currentMove == 4)
      // {
      //   movement.currentMove = 0;
      // }
      // for (i = 0; i < sizeof(blockMap); i++)
      // {
        // collisionState = detectCollisionBallBlock(blockMap[i], ball);
        // switch (detectCollisionBallBlock(blockMap[i], ball)) {
          // case 0: // No collision
            // break;
          // case 2: // Hit bottom
            // movement.movePattern[0] = 3;
            // movement.movePattern[1] = 1;
            // movement.movePattern[2] = 1;
            // movement.movePattern[3] = 1;
            // while (1) {
            //   // Spin it baby!
            // }
            // break;
        // }
      // }
    }
    // switch (state) {
    //   case 0:
    //     renderBall(&ball);
    //     state = 1;
    //     break;
    //   case 1:
    //     switch (readkey()) {
    //       case 1: // PF7
    //         break;

    //       case 2: // PF6 clicked 

    //         break;

    //       case 4:

    //         break;

    //       default:
    //         break;
    //     }
    //     break;
    // }
  }
}