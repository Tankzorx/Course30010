#include <sio.h>             // special encore serial i/o routines

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

	// gotoxy(140, 15);
	// printf("OldX, oldY::\n");
	// gotoxy(140, 16);
	// printFix(oldX << 2);
	// gotoxy(155,16);
	// printf(" %lX",oldX);
	// gotoxy(140, 17);
	// printFix(oldY << 2);
	// gotoxy(155,17);
	// printf(" %lX",oldY);

	// gotoxy(140, 19);
	// printf("sin og cos:\n");
	// gotoxy(140, 20);
	// printFix(sinAngle << 2);
	// gotoxy(140, 21);
	// printFix(cosAngle << 2);
	// sinAngle = expand(sinAngle);
	// cosAngle = expand(cosAngle);
	// gotoxy(60,25);
	// printFix(expand(sinAngle));
	// gotoxy(60,26);
	// printFix(expand(cosAngle));
	aux1 = (oldX*cosAngle)>>14;
	aux2 = FIX14_MULT(oldY, sinAngle);
	// gotoxy(140, 40);
	// printf("AUX1 and AUX2:\n");
	// gotoxy(140, 41);
	// printFix(aux1 << 2);
	// gotoxy(140, 42);
	// printFix(aux2 << 2);
	vector->x = aux1 - aux2;
	aux1 = FIX14_MULT(oldX, sinAngle);
	aux2 = FIX14_MULT(oldY, cosAngle);

	// gotoxy(140, 50);
	// printf("AUX1 and AUX2:\n");
	// gotoxy(140, 51);
	// printFix(aux1 << 2);
	// gotoxy(140, 52);
	// printFix(aux2 << 2);

	vector->y = aux1 + aux2;
}
