#include <eZ8.h>             // special encore constants, macros and flash routines

char readkey() {
  // PFIN:
  // 00101111 = both pressed
  // 01101111 = PF7 pressed
  // 10101111 = PF6 pressed
  // 11101111 = none pressed
  char PF7DTU = ~PFIN & 0x80; // We bitwise 'not' because 1 means off, 0 means on. This is confusing
  char PF6DTU = ~PFIN & 0x40; // so if we 'not' it becomes 1=on, 0=off.
  char PD3DTU = ~PDIN & 0x8;

  PF7DTU = (PF7DTU >> 7) & 0x1;
  PF6DTU = (PF6DTU >> 5) & 0x2;
  PD3DTU = PD3DTU  >> 1;
  return PF7DTU | PF6DTU | PD3DTU;
}