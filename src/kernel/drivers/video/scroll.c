//scroll.c
#include <video.h>
#include <limine.h>
#include <stdint.h>

void framebuffer_scroll(void) {
  uint8_t *fb = (uint8_t * )g_framebuffer->address;
  uint64_t pitch = g_framebuffer->pitch;
  uint64_t height = g_framebuffer->height;

  uint64_t scroll_bytes = 16 * pitch;
  uint64_t total_bytes  = height * pitch;

  for(uint64_t i = scroll_bytes; i < total_bytes; i++) {
    fb[i - scroll_bytes] = fb[i];
  }

  for(uint64_t i = total_bytes - scroll_bytes; i < total_bytes; i++) {
    fb[i] = 0x00;
  }
}
