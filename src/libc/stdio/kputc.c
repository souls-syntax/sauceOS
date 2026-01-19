//kputc.c
#include <stdio.h>
#include <limine.h>
#include <video.h>

#define FONT8x16_IMPLEMENTATION
#include "font8x16.h"

static int cursor_x = 0;
static int cursor_y = 0;

void kputc(char c) {
  unsigned char char_idx = (unsigned char)c;
  
  if (char_idx == '\n') {
    cursor_x = 0;
    cursor_y += 16;
  }
  else if (char_idx == '\r') {
    cursor_x = 0;
    return;
  }
  else {
    for (int y = 0; y < 16; y++) {
      unsigned char row_data = font8x16[char_idx][y];

      for (int x = 0; x < 8; x++) {
        if((row_data >> (7-x)) & 1) {

          PutPixel(cursor_x + x, cursor_y + y);
        }
      }
    }
    cursor_x += 8;
  }
  if ((uint64_t)(cursor_x + 8) > g_framebuffer->width) {
    cursor_x = 0;
    cursor_y += 16;
  }
  if ((uint64_t)(cursor_y + 16) > g_framebuffer->height) {
    framebuffer_scroll();
    cursor_y -= 16;
  }
  
  return;
}
