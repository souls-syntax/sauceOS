//vini.c

#include <limine.h>
#include "video.h"
#include <stddef.h>
#include <stdbool.h>
#include "bootinfo.h"

static void hcf(void) {
    for(;;) { asm ("hlt"); }
}

struct limine_framebuffer *g_framebuffer = NULL;

void video_init(void) {
  if(LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false) {
    hcf();
  }

  // Ensuring if we got the framebuffer
  if (framebuffer_request.response == NULL
    || framebuffer_request.response->framebuffer_count < 1) {
    hcf();
  }

  // Fetching the first framebuffer
  g_framebuffer = framebuffer_request.response->framebuffers[0];

}

