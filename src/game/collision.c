
#include "collision.h"
#include "../api/vector.h"
#include "../hif/console.h"
#include <sio.h>
#include "ball.h"
#include "block.h"

// long abs(long a) {
// 	a & 0x7FFFFFFF;
// }

/*
 * 0: No collision
 * 1: Hit left side
 * 2: Hit bottom side
 * 3: Hit right side
 * 4: Hit top side
 */
int detectCollisionBallBlock(Block block, Ball ball) {
	long epsilon = (long) 1 << 13; // We need some variable to define a

	// Ball hit left side We can no longer check 
	// If ball position is exactly on a coordinate,
	// as we're using fixed points.
	if ((ball.position.x > (block.position.x - epsilon)) &&
		(ball.position.x < (block.position.x)) &&
		(ball.position.y >= block.position.y &&
		 ball.position.y <= block.position.y + block.height))
	{
		return 1;
	}

	// Ball hit bottom side. How to format expressions like this xD?
	// If you have a better idea on how to format this shit,
	// Please, show me!
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

	// Ball hit right side
	if (((ball.position.x > (block.position.x + block.width)) &&
		(ball.position.x < (block.position.x + block.width + epsilon))) &&
		(ball.position.y >= block.position.y &&
		 ball.position.y <= block.position.y + block.height))
	{
		return 3;
	}

	// Ball hit top side
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
