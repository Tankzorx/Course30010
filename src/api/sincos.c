#include <sio.h>             // special encore serial i/o routines
#include "LUT.h"
#include "sincos.h"
#include "vector.h"


void printFix(long i) {
	if ((i & 0x80000000) != 0) {
		printf("-");
		i = ~i+1;
	}
	printf("%1d.%04ld \n", i >> 16, 10000 * (unsigned long) ( i & 0xffff) >> 16);
}
// Convert from 16.0 to 2.14 ?
long expand(long i) {
  return i << 2;
}

signed short sin(int i) {
  return SIN[i];
}

signed short cos(int i) {
	return SIN[i+128];
}