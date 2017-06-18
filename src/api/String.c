#include "String.h"


int length(char text[]) {
	int i;
	for (i = 0; text[i] != '\0'; i++){}
	return i;
}
