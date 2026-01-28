#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include <string.h>
#include <stdio.h>
#include <video.h>
#include <gdt.h>
#include <idt.h>
#include <keyboard.h>

static void hcf(void) {
  for(;;) {
    asm ("hlt");
  }
}

void kmain(void) {

  video_init();
  initGdt();
  initIdt();
  initKeyboard();

  kprintf("KIter Initialized. \n");

  hcf();
}

