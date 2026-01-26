//gdt.h
#ifndef _GDT_H
#define _GDT_H 1

#include <stdint.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

struct gdt_entry_struct {
  uint16_t limit;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t flags;
  uint8_t base_high;
}__attribute__((packed));

struct gdt_ptr_struct {
  uint16_t limit;
  uint64_t base;
}__attribute__((packed));

void initGdt();
void setGdtGate(uint32_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);

#ifdef __cplusplus
}
#endif

#endif

