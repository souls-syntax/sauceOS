#include <stdio.h>
#include <stdint.h>
#include <limine.h>

void PutPixel(struct limine_framebuffer *fb, int x, int y, uint32_t color) {

  uint64_t offset = (y * fb->pitch) + (x * (fb->bpp / 8));

  uint8_t* address = (uint8_t*)fb->address;

  *((uint32_t*)(address + offset)) = color;
} 
