#include "Debounce.h"

#include "../hif/buttonInput.h"


void spin(){
  while(readkey() == 0) {}
}


void sleep(int* tick, int i){
  *tick = 0;
  while(*tick < i) {}
}
