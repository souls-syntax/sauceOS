//vini.c

#include <limine.h>
#include <video.h>
#include <stddef.h>
#include <stdbool.h>

__attribute__((used, section(".limine_requests")))
static volatile uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(4);

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
  .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
  .revision = 0
};

__attribute__((used, section(".limine_requests_start")))
static volatile uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile uint64_t limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;


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

