#include "../hif/console.h"

#include "../api/vector.h"

#include "ball.h"
#include "striker.h"
#include "block.h"
#include "collision.h"


int detectCollisionBallBlock(Block block, Ball ball) {
	long epsilon = (long) 1 << 14;

	if (block.durability == 0)
	{
		return -1;
	}
	if ((ball.position.x > (block.position.x - epsilon)) &&
		(ball.position.x < (block.position.x)) &&
		(ball.position.y >= block.position.y &&
		 ball.position.y <= block.position.y + block.height))
	{
		return 1;
	}

	if (
		(
			(ball.position.y > (block.position.y + block.height))
			&&
			(ball.position.y < (block.position.y + block.height + epsilon))
	    )
	    &&
		(
			ball.position.x >= block.position.x
			&&
		 	ball.position.x <= block.position.x + block.width
		)
	   )
	{
		return 2;
	}

	if (((ball.position.x > (block.position.x + block.width)) &&
		(ball.position.x < (block.position.x + block.width + epsilon))) &&
		(ball.position.y >= block.position.y &&
		 ball.position.y <= block.position.y + block.height))
	{
		return 3;
	}

	if (
		(
			(ball.position.y > (block.position.y - epsilon))
			&&
			(ball.position.y < (block.position.y))
	    )
	    &&
		(
			ball.position.x >= block.position.x
			&&
		 	ball.position.x <= block.position.x + block.width
		)
	   )
	{
		return 4;
	}
	return -1;
}

int detectCollisionBallStriker(Striker striker,Ball ball) {
	int i;
	long j;
    long epsilon = (long) 1 << 14;

    // Ball too high up
    if (ball.position.y < (striker.position.y - epsilon)){
    	return -1;
    }

    // Ball too low down
    if (ball.position.y > (striker.position.y)){
    	return -1;
    }

    // Ball too far left
    if (ball.position.x < striker.position.x) {
    	return -1;
    }

    // Ball too far right (Capitalist pig.)
    if (ball.position.x > striker.position.x + striker.width) {
    	return -1;
    }

	for (i = 0; i < (striker.width >> 14); i++)
	{
		j = i;
		if (ball.position.x > (striker.position.x + (j << 14)) &&
			ball.position.x < (striker.position.x + ((j + 1) << 14)))
		{
			return i;
		}
	}

	return -1;
}

