#include <eZ8.h>
#include <sio.h>

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
  char scoreHelp = 0;
  Striker striker;
  char columnArray[5] = { 0x1E, 0x1D, 0x1B, 0x17, 0x0F };
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
  Ball ball;
  // Ball ball2;
  Block b;
  Vector auxVector;

  // Initialize striker
  striker.position.x = 60 << 14;
  striker.position.y = 70 << 14;
  striker.width = ((long) 0x10) << 14;

  // 18.14 format
  initBallPosition.x = 70 << 14;
  initBallPosition.y = 60 << 14;
  initBallVelocity.x = 0 << 14;
  initBallVelocity.y = 0x1FFF;

  ball.position = initBallPosition;
  ball.velocity = initBallVelocity;
  ball.lastRenderPosition = initBallPosition;

  // initBallPosition.x = 50 << 14;
  // initBallPosition.y = 50 << 14;
  // initBallVelocity.x = 1 << 14;
  // initBallVelocity.y = 3 << 14;

  // ball2.position = initBallPosition;
  // ball2.velocity = initBallVelocity;
  // ball2.lastRenderPosition = initBallPosition;

  generateWalls(blockMap);
  generateDefaultMap(blockMap);

  initLED(&LEDDataInstance);
  LEDSetStringByIndex('0',0, &LEDDataInstance);
  LEDSetStringByIndex('0',1, &LEDDataInstance);
  LEDSetStringByIndex('0',2, &LEDDataInstance);
  LEDSetStringByIndex(0x3D,3, &LEDDataInstance);
  // LEDSetStringByIndex((char)(((int)':') + lives),3, &LEDDataInstance);


  clrscr();
  // gotoxy(10,10);
  // printf("Block position: (%d, %d)\n", blockMap[0].position.x >> 14, blockMap[0].position.y >> 14);
  // return;
  renderBlockMap(blockMap);
  renderStriker(&striker);

  while(1) {

    if (*LEDFlag == 1)
    {
        // To avoid a function call, we moved LEDUpdate() body out here.
        PEOUT = columnArray[LEDDataInstance.currentColumn];

        PGOUT = *(&(LEDDataInstance.video_buffer[0][0]) + (5 - LEDDataInstance.currentColumn)); 
        PEOUT &= 0x1F;
        PEOUT |= 0x80; // Send clock signal.

        PGOUT = *(&(LEDDataInstance.video_buffer[1][0]) + (5 - LEDDataInstance.currentColumn)); 
        PGOUT &= 0x7F;
        PGOUT |= 0x80; // Send clock signal.

        PGOUT = *(&(LEDDataInstance.video_buffer[2][0]) + (5 - LEDDataInstance.currentColumn)); 
        PEOUT &= 0x1F;
        PEOUT |= 0x20; // Send clock signal.

        PGOUT = *(&(LEDDataInstance.video_buffer[3][0]) + (5 - LEDDataInstance.currentColumn)); 
        PEOUT &= 0x1F;
        PEOUT |= 0x40; // Send clock signal.


        LEDDataInstance.currentColumn = (LEDDataInstance.currentColumn + 1);

        if (LEDDataInstance.currentColumn == 5) {
          LEDDataInstance.currentColumn = 0;
        }
      *LEDFlag = 0;
    }

    if (*moveFlag == 1) {
      // Move ball and detect collision between ball&blocks.
      moveBall(&ball);
      // moveBall(&ball2);

      // if (ballIsDead(ball, 70) == 1 || ballIsDead(ball2, 70) == 1)
      if (ballIsDead(ball, 70) == 1)
      {
        if (lives > 0)
        {
            initBallPosition.x = 70 << 14;
            initBallPosition.y = 60 << 14;
            initBallVelocity.x = 0 << 14;
            initBallVelocity.y = 0x1FFF;
            ball.position = initBallPosition;
            ball.velocity = initBallVelocity;

            // initBallPosition.x = 50 << 14;
            // initBallPosition.y = 65 << 14;
            // initBallVelocity.x = 1 << 14;
            // initBallVelocity.y = 3 << 14;
            // ball2.position = initBallPosition;
            // ball2.velocity = initBallVelocity;
            lives = lives - 1;
            LEDSetStringByIndex('|' + lives - 1,3, &LEDDataInstance);
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

            // Update LED display
            scoreHelp = (char) (*currentPlayerScore/100);
            LEDSetStringByIndex(scoreHelp + 48,0, &LEDDataInstance);
            scoreHelp = (char) ((*currentPlayerScore % 100) / 10);
            LEDSetStringByIndex(scoreHelp + 48,1, &LEDDataInstance);
            scoreHelp = (char) ((*currentPlayerScore % 10));
            LEDSetStringByIndex(scoreHelp + 48,2, &LEDDataInstance);
            gotoxy(50,0);
            clreol();
            gotoxy(50,0);
            printf("SCORE: %d\n", *currentPlayerScore);
            renderBlock(blockMap[i]);
          }
          // break;
        }
        // collisionState = detectCollisionBallBlock(blockMap[i], ball2);
        // handleBlockCollision(&ball2, collisionState);
        // if (collisionState > 0)
        // {
        //   if (blockMap[i].indestructible == 0)
        //   {
        //     blockMap[i].durability = blockMap[i].durability - 1;
        //     *currentPlayerScore = *currentPlayerScore + 1;
            
        //     // Update LED display
        //     scoreHelp = (*currentPlayerScore/100);
        //     LEDSetStringByIndex(scoreHelp + 48,0, &LEDDataInstance);
        //     scoreHelp = ((*currentPlayerScore % 100) / 10);
        //     LEDSetStringByIndex(scoreHelp + 48,1, &LEDDataInstance);
        //     scoreHelp = *currentPlayerScore % 10;
        //     LEDSetStringByIndex(scoreHelp + 48,2, &LEDDataInstance);
        //     gotoxy(50,0);
        //     clreol();
        //     gotoxy(50,0);
        //     printf("SCORE: %d\n", *currentPlayerScore);
        //     renderBlock(blockMap[i]);
        //   }
        //   // break;
        // }
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
      // collisionStateStriker = detectCollisionBallStriker(striker, ball2);
      // if (collisionStateStriker > -1)
      // {
      //   handleStrikerCollision(&ball2, &striker, collisionStateStriker);
      //   moveUpEpsilonBall(&ball2);
      // }
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

    if (*strikerMoveFlag == 1)
    {
      clearBall(&ball);
      // clearBall(&ball2);
      renderBall(&ball);
      // renderBall(&ball2);
      clearStriker(&striker);
      renderStriker(&striker);
      *strikerMoveFlag = 0;
    }
  }
}
