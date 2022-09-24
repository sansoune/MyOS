#include "include/stdint.h"
#include "include/stdio.h"




void __attribute__((cdecl)) start(uint16_t bootDrive)
{ 
  print("hello from c!");

  return;
}
