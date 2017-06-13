#include <eZ8.h>

#include "game.h"
#include "block.h"
#include "ball.h"
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
  int moves[4] = { 1, 1, 1, 0 };
  int collisionState;
  Movement movement;
  int state = 0;
  Block blockMap[30];
  Ball ball;
  Block b;

  for (i = 0; i < sizeof(moves); i++)
  {
    movement.movePattern[i] = moves[i];
  }
  movement.currentMove = 0;

  ball.radius = 1;
  ball.xPos = 50;
  ball.yPos = 60;

  // This is one way of generating the blockMap:
  // (Shorthand version of struct creation didn't work.)
  // Rows
  for (i = 0; i < 3; i++) {
    // Columns
    for (j = 0; j < 10; j++) {
      b.upperLeftX = 15+j*12; // 7 - width = horizontal distance between blocks
      b.upperLeftY = 5+i*10; // 7- height = vertical distance between blocks.
      b.width = 10;
      b.height = 8;
      b.durability = 3;
      b.indestructible = 1;
      blockMap[i*10 + j] = b;
    }
  }

  initTimer();
  SET_VECTOR(TIMER0, interruptHandler); // Can't avoid this call sadly.
  startTimer();

  clrscr();
  for (i = 0; i < 30; i++)
  {
    renderBlock(blockMap[i]);
  }

  while(1) {
    if (ms100Tick == 0)
    {
      // moveBallRightN(&ball, 1);
      // moveBallUpN(&ball, 1);
      // moveBall(&ball, movePattern);
      switch (movement.movePattern[movement.currentMove]) {
        case 0:
          moveBallUpN(&ball, 1);
          break;
        case 1:
          moveBallRightN(&ball, 1);
          break;
        case 2:
          moveBallLeftN(&ball, 1);
          break;
        case 3:
          moveBallDownN(&ball, 1);
          break;
        default: 
          break;
      }
      movement.currentMove++;
      if (movement.currentMove == 4)
      {
        movement.currentMove = 0;
      }
      for (i = 0; i < sizeof(blockMap); i++)
      {
        // collisionState = detectCollisionBallBlock(blockMap[i], ball);
        switch (detectCollisionBallBlock(blockMap[i], ball)) {
          case 0: // No collision
            break;
          case 2: // Hit bottom
            movement.movePattern[0] = 3;
            movement.movePattern[1] = 1;
            movement.movePattern[2] = 1;
            movement.movePattern[3] = 1;
            // while (1) {
            //   // Spin it baby!
            // }
            break;
        }
      }
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