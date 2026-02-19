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
#include <bootinfo.h>
#include <pmm.h>
#include <test.h>

static void hcf(void) {
  for(;;) {
    asm ("hlt");
  }
}

void kmain(void) {

    bootinfoInit();
    video_init();
    initGdt();
    initIdt();
    initKeyboard();
    PrintMemoryMaps();
    SetMemoryMap(6);
    kprintf("MemoryMapMapping Initialized. \n");
    Test_BasicAllocation();
    
    hcf();

}

