
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
	// long dx, dy, help1, help2, help3;
	// // dx = max(abs(px - x) - width / 2, 0);
	// // dy = max(abs(py - y) - height / 2, 0);
	// // return dx * dx + dy * dy;
	// help3 = FIX14_DIV(block.width, (long)2 << 14);
	// help1 = abs(ball.position.x - (block.position.x + help3));
	// help2 = help1 - FIX14_DIV(block.width, (long) 2 << 14);

	// dx = help2 > 0 ? help2 : 0;

	// help3 = FIX14_DIV(block.height, (long)2 << 14);
	// help1 = abs(ball.position.y - (block.position.y + help3));
	// help2 = help1 - FIX14_DIV(block.height, (long) 2 << 14);

	// dy = help2 > 0 ? help2 : 0;
	// gotoxy(70,65);
	// printf("dx: %d, dy: %d", dx >> 14, dy >> 14);
	// gotoxy(70,67);
	// help3 = FIX14_MULT(dx,dx) + FIX14_MULT(dy,dy);
	// printf("%ld\n", help3);
	// return help3;

	// printf("ASDASDASDASD: %d\n", dx >> 14);
	// return -1;
	long epsilon = (long) 1 << 13; // We need some variable to define a
	// Collision range, as we're now using fixed point.
	// Ball is completely outside block range.
	// if (ball.position.x < block.position.x || 
	// 	ball.position.x > block.position.x + block.width ||
	// 	ball.position.y < block.position.y ||
	// 	ball.position.y > block.position.y + block.height)
	// {
	// 	return 0;
	// }

	// Ball hit left side We can no longer check 
	// If ball position is exactly on a coordinate,
	// as we're using fixed points.
	if (((ball.position.x > (block.position.x - epsilon)) &&
		(ball.position.x < (block.position.x + epsilon))) &&
		(ball.position.y <= block.position.y &&
		 ball.position.y >= block.position.y + block.height))
	{
		return 1;
	}

	// Ball hit bottom side. How to format expressions like this xD?
	// If you have a better idea on how to format this shit,
	// Please, show me!
	if (
		(
			(ball.position.y > (block.position.y + block.height - epsilon)) 
			&&
			(ball.position.y < (block.position.y + block.height + epsilon))
	    ) 
	    &&
		(
			ball.position.x >= block.position.x 
			&&
		 	ball.position.x <= block.position.x + block.height
		)
	   )
	{
		return 2;
	}

	// Ball hit right side
	if (((ball.position.x > (block.position.x - epsilon)) &&
		(ball.position.x < (block.position.x + epsilon))) &&
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
			(ball.position.y < (block.position.y + epsilon))
	    ) 
	    &&
		(
			ball.position.x >= block.position.x 
			&&
		 	ball.position.x <= block.position.x + block.height
		)
	   )
	{
		return 4;
	}
	


	return -1;

}
