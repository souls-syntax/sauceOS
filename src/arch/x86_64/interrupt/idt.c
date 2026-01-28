//idt.c

#include <string.h>
#include <idt.h>
#include <stdint.h>
#include <io.h>
#include <stdbool.h>
/*
 * Port I/O helpers
 *
 * x86 port addresses are always 16-bit.
 * Data width depends on the instruction variant:
 *  - outb: 8-bit value
 *  - outw: 16-bit value
 *  - outl: 32-bit value
 *
 * Note:
 * IRQs above 31 are currently masked.
 * They will be unmasked once IRQ handlers are installed.
 */

#define IDT_MAX_DESCRIPTORS 256

struct idt_entry_struct idt_entries[IDT_MAX_DESCRIPTORS];
struct idt_entry_ptr idt_ptr;

static bool vectors[IDT_MAX_DESCRIPTORS];

extern void* isr_stub_table[];

void initIdt() {
  idt_ptr.base = (uintptr_t)&idt_entries;
  idt_ptr.limit = sizeof(struct idt_entry_struct) * IDT_MAX_DESCRIPTORS - 1;
  
  memset(&idt_entries, 0, sizeof(struct idt_entry_struct)*IDT_MAX_DESCRIPTORS);
  
  //0x0020 commands and 0x0021 data := master PIC
  //0x00A0 commands and 0x00A1 data := slave PIC
  
  // Initialinzing the chip
  outPortB(0x20, 0x11);
  outPortB(0xA0, 0x11);

  // Offsets for our chip
  outPortB(0x21, 0x20);
  outPortB(0xA1, 0x28);

  outPortB(0x21, 0x04);
  outPortB(0xA1, 0x02);

  outPortB(0x21, 0x01);
  outPortB(0xA1, 0x01);

  outPortB(0x21, 0xFD); // Remember we are still masking over the interrupt over 31+ so set it back to 0 and unmake it when irq handlers are ready.
  outPortB(0xA1, 0xFF);


  for (uint8_t vector = 0; vector < 48; vector++) {
    setIdtGate(vector, isr_stub_table[vector], 0x8E);
    vectors[vector] = true;
  }

  __asm__ volatile ("lidt %0" : : "m"(idt_ptr)); // load new idt
  __asm__ volatile ("sti"); //setup interrupt flag
}

void setIdtGate(uint8_t vector, void* isr, uint16_t flags) {
  struct idt_entry_struct* descriptor = &idt_entries[vector];
  
  descriptor->offset_1               = (uint64_t)isr &0xFFFF;
  descriptor->selector               = 0x08;
  descriptor->ist                    = 0;
  descriptor->type_attributes        = flags;
  descriptor->offset_2               = ((uint64_t)isr >> 16) & 0xFFFF;
  descriptor->offset_3               = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
  descriptor->zero                   = 0;
}

