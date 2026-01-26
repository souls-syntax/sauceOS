#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include <string.h>
#include <stdio.h>
#include <video.h>
#include <gdt.h>

static void hcf(void) {
  for(;;) {
    asm ("hlt");
  }
}

void kmain(void) {

  video_init();
  initGdt();

  kprintf("TSS is online");
  hcf();
}

