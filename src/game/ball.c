#include <sio.h>

#include "ball.h"
#include "../hif/console.h"

void moveBallRightN(Ball*  ball, int n) {
	clearBall(ball);
	ball->xPos = ball->xPos + n;
	renderBall(ball);
}

void moveBallLeftN(Ball*  ball, int n) {
	clearBall(ball);
	ball->xPos = ball->xPos - n;
	renderBall(ball);
}

void moveBallUpN(Ball*  ball, int n) {
	clearBall(ball);
	ball->yPos = ball->yPos - n;
	renderBall(ball);
}

void moveBallDownN(Ball*  ball, int n) {
	clearBall(ball);
	ball->yPos = ball->yPos + n;
	renderBall(ball);
}

void clearBall(Ball* ball) {
	gotoxy(ball->xPos, ball->yPos);
	printN(1, ' ');
}

void renderBall(Ball* ball) {
    gotoxy(ball->xPos, ball->yPos);
    printf("O");
}