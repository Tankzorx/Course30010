#include <sio.h>

#include "ball.h"
#include "../api/vector.h"
#include "../hif/console.h"

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
	ball->position.x = ball->position.x + ball->velocity.x;
	ball->position.y = ball->position.y + ball->velocity.y;
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
