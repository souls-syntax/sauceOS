//io.c
#include <io.h>

void outPortB(uint16_t port, uint8_t value) {
  asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inPortB(uint16_t port) {
  uint8_t result;
  __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
  return result;
}
