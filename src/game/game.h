#ifndef _DTU_GAME_
#define _DTU_GAME_


/*
 * 0: up
 * 1: right
 * 2: left
 * 3: down
 */
typedef struct
{
  int movePattern[4];
  int currentMove;
} Movement;

int game();

#endif /*! _DTU_GAME_ */
