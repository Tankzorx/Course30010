#include "striker.h"
#include "../hif/console.h"




void renderStriker(Striker *striker) {
	gotoxy(striker->position.x >> 14, striker->position.y >> 14);
	printN(striker->width >> 14, '¤');
	striker->lastRenderPosition.x = striker->position.x;
	striker->lastRenderPosition.y = striker->position.y;

}
void clearStriker(Striker *striker) {
	gotoxy(striker->lastRenderPosition.x >> 14, striker->lastRenderPosition.y >> 14);
	printN(striker->width >> 14, ' ');
}




void moveStriker(Striker *striker, char buttonInput) {
	switch (buttonInput) {
		case 1: // Move right
			if (striker->position.x > (((long) 195 << 14) - striker->width))
			{
				striker->position.x = ((long) 195 << 14) - striker->width;
				break;
			}
			striker->position.x = striker->position.x + (3 << 11);
			break;
		case 2: // Move left
			if (striker->position.x < ((long) 5 << 14))
			{
				striker->position.x = ((long) 5 << 14);
				break;
			}
			striker->position.x = striker->position.x - (3 << 11);
			break;
		default:
			break;
	}
}