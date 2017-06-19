#include <sio.h>

#include "ball.h"
#include "../api/vector.h"
#include "../hif/console.h"
#include "../api/sincos.h"

void moveBall(Ball* ball) {
	ball->position.x = ball->position.x + (ball->velocity.x >> 4);
	ball->position.y = ball->position.y - (ball->velocity.y >> 4);
}

void clearBall(Ball* ball) {
    gotoxy(ball->lastRenderPosition.x >> 14, ball->lastRenderPosition.y >> 14);
	printN(1, ' ');
}

void renderBall(Ball* ball) {
	ball->lastRenderPosition.x = ball->position.x;
	ball->lastRenderPosition.y = ball->position.y;
    gotoxy(ball->position.x >> 14, ball->position.y >> 14);
    printf("O");
}

void handleBlockCollision(Ball* ballPtr, int collisionState) {
	switch (collisionState) {
		case 1: // left
			flipX(&(ballPtr->velocity));
			break;
		case 3: // right
			flipX(&(ballPtr->velocity));
			break;
		case 2:
			flipY(&(ballPtr->velocity));
			break;
		case 4:
			flipY(&(ballPtr->velocity));
			break;
		default: 
			break;
	}
}

int ballIsDead(Ball ball, int screenHeight) {
	if ((ball.position.y >> 14) > screenHeight)
	{
		return 1;
	}
	return 0;
}

void handleStrikerCollision(Ball* ballPtr, Striker* striker, int collisionArea) {

	int widthHalf = ((striker->width >> 14) / 2);

	if ((ballPtr->velocity.x) > 0)
	{	
		if (collisionArea < widthHalf) // Ball hit left side of striker coming from left.
		{
			flipY(&(ballPtr->velocity));
			rotate(&(ballPtr->velocity), ((striker->width >> 14) - collisionArea)*2);
		} else {
			rotate(&(ballPtr->velocity), collisionArea*2);
			flipY(&(ballPtr->velocity));
		}
	} else {
		if (collisionArea > widthHalf) // ball hit right side of striker coming from right.
		{
			rotate(&(ballPtr->velocity), collisionArea*2);
			flipY(&(ballPtr->velocity));
		} else {
			flipY(&(ballPtr->velocity));
			rotate(&(ballPtr->velocity), ((striker->width >> 14) - collisionArea)*2);
		}
	}
}

void moveUpEpsilonBall(Ball* ball) {
    long epsilon = (long) 1 << 13;
	ball->position.y = ball->position.y - epsilon;
}
