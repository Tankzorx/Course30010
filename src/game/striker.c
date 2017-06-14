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
			striker->position.x = striker->position.x + (1 << 10);
			break;
		case 2: // Move left
			striker->position.x = striker->position.x - (1 << 10);
			break;
		default:
			break;
	}
}