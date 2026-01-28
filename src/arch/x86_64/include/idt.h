
//Idt.h
#ifndef _IDT_H
#define _IDT_H 1

#include <stdint.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

struct idt_entry_struct {
  uint16_t offset_1;
  uint16_t selector; // a code segment selector in GDT or LDT
  uint8_t ist; // bits 0..2 holding Interrupt Stack Table offset rest of bits are zero
  uint8_t type_attributes; // gate type, dpl, and p fields
  uint16_t offset_2; 
  uint32_t offset_3;
  uint32_t zero; // reserved
}__attribute__((packed));

struct idt_entry_ptr {
  uint16_t limit;
  uint64_t base;
}__attribute__((packed));

void initIdt();
void setIdtGate(uint8_t vector, void* isr, uint16_t flags);

#ifdef __cplusplus
}
#endif

#endif

