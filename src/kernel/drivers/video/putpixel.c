//putpixel.c
#include <stdio.h>
#include <stdint.h>
#include <limine.h>
#include <video.h>


static uint32_t color = 0x00FF00; 

void PutPixel(int x, int y) {
  if (!g_framebuffer) {
    return;
  }
  uint64_t offset = (y * g_framebuffer->pitch) + (x * (g_framebuffer->bpp / 8));
  
  uint8_t* address = (uint8_t*)g_framebuffer->address;
  
  *((uint32_t*)(address + offset)) = color;
} 
