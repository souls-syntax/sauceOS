// #include <video.h>
// #include <limine.h>
//
// #define FONT8x16_IMPLEMENTATION
// #include "font8x16.h"
//
// static int cursor_x = 0;
// static int cursor_y = 0;
//
//
// void kputc(struct limine_framebuffer *fb, char c, uint32_t color) {
//   unsigned char char_idx = (unsigned char)c;
//
//   if (char_idx == '\n') {
//     cursor_x = 0;
//     cursor_y += 16;
//     return;
//   }
//   if (char_idx == '\r') {
//     cursor_x = 0;
//     return;
//   }
//
//   for (int y = 0; y < 16; y++) {
//     unsigned char row_data = font8x16[char_idx][y];
//
//     for (int x = 0; x < 8; x++) {
//       if((row_data >> (7-x)) & 1) {
//
//         PutPixel(fb, cursor_x + x, cursor_y + y, color);
//       }
//     }
//   }
//   cursor_x += 8;
//
//   if ((uint64_t)cursor_x >= fb->width) {
//     cursor_x = 0;
//     cursor_y += 16;
//   }
//
//   return;
// }
//
//
// void kprint(struct limine_framebuffer *fb, const char *str, uint32_t color) {
//   while(*str) {
//     kputc(fb,*str,color);
//     str++;
//   }
// }
