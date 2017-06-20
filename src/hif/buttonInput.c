#include <eZ8.h>

char readkey() {
  // PFIN:
  // 00101111 = both pressed
  // 01101111 = PF7 pressed
  // 10101111 = PF6 pressed
  // 11101111 = none pressed

  char PF7DTU = ~PFIN & 0x80;
  char PF6DTU = ~PFIN & 0x40;
  char PD3DTU = ~PDIN & 0x8;

  PF7DTU = (PF7DTU >> 7) & 0x1;
  PF6DTU = (PF6DTU >> 5) & 0x2;
  PD3DTU = PD3DTU  >> 1;
  return PD3DTU | PF6DTU | PF7DTU;
}
