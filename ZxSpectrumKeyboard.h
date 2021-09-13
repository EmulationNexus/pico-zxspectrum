#pragma once

#include <pico/printf.h>

class ZxSpectrumKeyboard {
  
  unsigned char _line[8];

public:
  ZxSpectrumKeyboard() {
    reset();
  }

  void reset() {
    for(int i = 0; i < 8; ++i) _line[i] = 0xff;
  }

  void press(unsigned int line, unsigned int key) {
    _line[line] &= ~(1 << key);
  }

  void release(unsigned int line, unsigned int key) {
    _line[line] |= 1 << key;
  }

  unsigned char read(int address) {
    int rs = address >> 8;
    unsigned int a = 0xff;
    for (int i = 0; i < 8; ++i) {
      if (~rs & (1 << i)) a &= _line[i];
    }
    //if (a != 0xff) printf("input %04X %02X\n", address, a);
    return a;
  }
};
