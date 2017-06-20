#include <sio.h>

#include "vector.h"
#include "sincos.h"
#include "../hif/console.h"

void flipX(Vector* vector) {
	vector->x = -(vector->x);
	return;
}

void flipY(Vector* vector) {
	vector->y = -(vector->y);
	return;
}

long dotP(Vector v1, Vector v2) {
	long aux1, aux2;
	aux1 = FIX14_MULT(v1.x, v2.x);
	aux2 = FIX14_MULT(v1.y, v2.y);
	return aux1 + aux2;
}

void rotate(Vector* vector, int angle) {
	long aux1,aux2;
	long oldX,oldY;
	long sinAngle = (long) sin(angle);
	long cosAngle = (long) cos(angle);

	oldX = vector->x;
	oldY = vector->y;

	aux1 = (oldX*cosAngle)>>14;
	aux2 = FIX14_MULT(oldY, sinAngle);

	vector->x = aux1 - aux2;
	aux1 = FIX14_MULT(oldX, sinAngle);
	aux2 = FIX14_MULT(oldY, cosAngle);

	vector->y = aux1 + aux2;
}
