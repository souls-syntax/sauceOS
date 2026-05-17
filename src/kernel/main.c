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
#include <paging.h>
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
    // SetMemoryMap(6);
    pmm_init();
    init_PML4();
    man_page((void*)0x0000100000000000, pmm_alloc_frame(), PTE_PRESENT | PTE_WRITABLE);
    uint64_t* test = (uint64_t*)0x0000100000000000;
    *test = 0xDEADBEEF;
    kprintf("              Testing Paging\nVlaue: %x\n", *test);
    kprintf("MemoryMapMapping Initialized. \n");
    // Test_BasicAllocation();
    
    hcf();

}

