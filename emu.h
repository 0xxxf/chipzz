#ifndef EMU_H
#define EMU_H

#include <iostream>
#include <fstream>
#include <random>
#include <limits>
#include <vector>

struct Chip {
  uint8_t v[16];  // general purpose registers
  uint16_t i;     // I register: used to store memory addresses
  uint8_t dt;     // delay timer register
  uint8_t st;     // sound timer register
  uint16_t pc = 0x200;    // program counter  
  uint8_t sp;     // stack pointer

  uint16_t stack[16];
  uint8_t memory[0xFFF];

  bool screen[64 * 32] = {false};
  bool keypad[16] = {false};

  std::vector<uint16_t> program_data;

  Chip(const char *rom);
  Chip();
  ~Chip();

  void step();
};

#endif
