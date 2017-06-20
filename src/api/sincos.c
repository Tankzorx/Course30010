#include <sio.h>
#include "LUT.h"
#include "sincos.h"


void printFix(long i) {
	if ((i & 0x80000000) != 0) {
		printf("-");
		i = ~i+1;
	}
	printf("%1d.%04ld \n", i >> 16, 10000 * (unsigned long) ( i & 0xffff) >> 16);
}

long expand(long i) {
  return i << 2;
}

signed short sin(int i) {
  return SIN[i];
}

signed short cos(int i) {
	return SIN[i+128];
}
