#include <sio.h>

#include "ball.h"
#include "../api/vector.h"
#include "../hif/console.h"
#include "../api/sincos.h"

// void moveBallRightN(Ball*  ball, int n) {
// 	clearBall(ball);
// 	ball->xPos = ball->xPos + n;
// 	renderBall(ball);
// }

// void moveBallLeftN(Ball*  ball, int n) {
// 	clearBall(ball);
// 	ball->xPos = ball->xPos - n;
// 	renderBall(ball);
// }

// void moveBallUpN(Ball*  ball, int n) {
// 	clearBall(ball);
// 	ball->yPos = ball->yPos - n;
// 	renderBall(ball);
// }

// void moveBallDownN(Ball*  ball, int n) {
// 	clearBall(ball);
// 	ball->yPos = ball->yPos + n;
// 	renderBall(ball);
// }

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
	// Vector test;
	// Regular format
	int widthHalf = ((striker->width >> 14) / 2);
	// gotoxy(100,38);
	// test.x = 4 << 14;
	// printFix(test.x << 2);


	// test.y = 5 << 14;
	// gotoxy(100,39);
	// printFix(test.y << 2);
	// rotate(&test, 256);
	// gotoxy(100,40);
	// printFix(test.x << 2);
	// gotoxy(100,41);
	// printFix(test.y << 2);

	// gotoxy(120, 20);
	// printFix(ballPtr->velocity.x << 2);
	// gotoxy(120, 21);
	// printFix(ballPtr->velocity.y << 2);
	// return;

	// gotoxy(100,41);
	// printf("%ld", ballPtr->velocity.y);
	// Then modify based on where the ball hit.
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
	// ballPtr->
	// gotoxy(120, 22);
	// printFix(ballPtr->velocity.x << 2);
	// gotoxy(120, 23);
	// printFix(ballPtr->velocity.y << 2);
	// ballPtr->velocity.x = ballPtr->velocity.x >> 1;
	// ballPtr->velocity.y = ballPtr->velocity.y >> 1;
	// printf("Ball after collisionArea modification: (%d, %d)\n", ballPtr->velocity.x >> 14, ballPtr->velocity.y >> 14);
}

void moveUpEpsilonBall(Ball* ball) {
    long epsilon = (long) 1 << 13;
	ball->position.y = ball->position.y - epsilon;
}
