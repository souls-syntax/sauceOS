#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include <string.h>
#include <stdio.h>
#include <video.h>
#include <gdt.h>
#include <idt.h>

static void hcf(void) {
  for(;;) {
    asm ("hlt");
  }
}

void kmain(void) {

  video_init();
  initGdt();
  initIdt();

  __asm__ volatile ("int $0x3");
  kprintf("IDT Initialized. \n");

  hcf();
}

