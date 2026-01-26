//scroll.c
#include <video.h>
#include <limine.h>
#include <stdint.h>
#include <string.h>

void framebuffer_scroll(void) {
  uint8_t *fb = (uint8_t * )g_framebuffer->address;
  uint64_t pitch = g_framebuffer->pitch;
  uint64_t height = g_framebuffer->height;

  uint64_t scroll_bytes = 16 * pitch;
  uint64_t total_bytes  = height * pitch;

  memmove(fb, fb + scroll_bytes, total_bytes - scroll_bytes);
  memset(fb + total_bytes - scroll_bytes, 0, scroll_bytes);
}
