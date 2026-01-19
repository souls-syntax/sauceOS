#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include <string.h>
#include <stdio.h>
#include <video.h>

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


// Implementing standard C expected functions.
// Don't delete it can be moved to other files(.c) tho.

// Halt and catch fire function which does smt. (confused)
// Ohh it seems to be assembly instruction to pause the OS

static void hcf(void) {
  for(;;) {
    asm ("hlt");
  }
}



void kmain(void) {
  // Seems to be that pause the os if both are not speaking same lang
  if(LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false) {
    hcf();
  }

  // Ensuring if we got the framebuffer
  if (framebuffer_request.response == NULL
    || framebuffer_request.response->framebuffer_count < 1) {
    hcf();
  }

  // Fetching the first framebuffer
  struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

  kprint(framebuffer, "Hello World! So happy to see everyone from here.", 0x00FF00);
  //
  // // Assuming framebuffer is RGB with 32-bit pixels
  // for(size_t i = 0; i < 100; i++) {
  //   volatile uint32_t *fb_ptr = framebuffer->address;
  //   fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xFF0000; // Don't really get what is happening here tbh
  // }
  //
  // halting the program we are done for this test;
  hcf();
  
}

