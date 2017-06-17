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
#include "../hif/LED.h"
#include "striker.h"

// gameState som input skal nok gøres senere.
int game(int* moveFlag, int* debounceGuard,  int* strikerMoveFlag,  int* currentPlayerScore,  int* LEDFlag) {
  Striker striker;
  Block blockMap[40];
  LEDData LEDDataInstance;
  char blocksAlive = 0;
  char lives = 3;
  char keyRead;
  int i, j;
  Vector initBallVelocity;
  Vector initBallPosition;
  int collisionState;
  int collisionStateStriker;
  // long collisionStateAUX;
  Ball ball;
  Block b;
  Vector auxVector;

  // Initialize striker
  striker.position.x = 60 << 14;
  striker.position.y = 70 << 14;
  striker.width = ((long) 0x10) << 14;

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

  initLED("Cyka Blyat ", &LEDDataInstance);

  // gotoxy(60,60);
  // printf("%s", LEDDataInstance.LEDText);
  // while(1) {}

  generateWalls(blockMap);
  generateDefaultMap(blockMap);
  
  // SetLEDText("yalla");
  // initTimer();
  // SET_VECTOR(TIMER0, interruptHandler); // Can't avoid this call sadly.
  // startTimer();

  clrscr();
  // gotoxy(10,10);
  // printf("Block position: (%d, %d)\n", blockMap[0].position.x >> 14, blockMap[0].position.y >> 14);
  // return;
  renderBlockMap(blockMap);
  renderStriker(&striker);

  while(1) {

    // if (*LEDFlag = 1)
    // {
    //     // LEDUpdate();
    // }

    if (*moveFlag == 1) {
      // Move ball and detect collision between ball&blocks.
      moveBall(&ball);

      if (ballIsDead(ball, 70) == 1)
      {
        if (lives > 0)
        {
            ball.position = initBallPosition;
            lives = lives - 1;
            ball.velocity = initBallVelocity;
        } else {
            return 1; // return menu state for now.
        }
      }

      for (i = 0; i < blockMap[39].indestructible; i++)
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
            *currentPlayerScore = *currentPlayerScore + 1;
            gotoxy(50,0);
            clreol();
            gotoxy(50,0);
            printf("SCORE: %d\n", *currentPlayerScore);
            renderBlock(blockMap[i]);
          }
          // break;
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

      moveStriker(&striker, keyRead);
      *moveFlag = 0;

      if (keyRead == 7)
      {
        renderBossMode();
        *debounceGuard = 1;
        while (*debounceGuard != 0) {}
        keyRead = readkey();
        while (keyRead == 0) {
          keyRead = readkey();
        }
        renderBlockMap(blockMap);
        renderStriker(&striker);
      }

    }

    if (*strikerMoveFlag)
    {

      clearBall(&ball);
      renderBall(&ball);
      clearStriker(&striker);
      renderStriker(&striker);
      *strikerMoveFlag = 0;
    }
  }
}