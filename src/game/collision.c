
#include "collision.h"
#include "ball.h"
#include "block.h"


int detectCollisionBallBlock(Block block, Ball ball) {
	// Ball is completely outside block range.
	if (ball.xPos < block.upperLeftX || 
		ball.xPos > block.upperLeftX + block.width ||
		ball.yPos < block.upperLeftY ||
		ball.yPos > block.upperLeftY + block.height)
	{
		return 0;
	}

	// Ball hit left side
	if (ball.xPos == block.upperLeftX &&
		(ball.yPos <= block.upperLeftY &&
		 ball.yPos >= block.upperLeftY + block.height))
	{
		return 1;
	}

	// Ball hit bottom side
	if (ball.yPos == block.upperLeftY + block.height &&
		(ball.xPos >= block.upperLeftX &&
		 ball.xPos <= block.upperLeftX + block.height))
	{
		return 2;
	}

	// Ball hit right side
	if (ball.xPos == block.upperLeftX + block.width &&
		(ball.yPos >= block.upperLeftY &&
		 ball.yPos <= block.upperLeftY + block.height))
	{
		return 3;
	}

	// Ball hit top side
	if (ball.yPos == block.upperLeftY &&
		(ball.xPos >= block.upperLeftX &&
		 ball.xPos <= block.upperLeftX + block.height))
	{
		return 4;
	}

	return -1;

}
