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

struct tss_entry_struct {
  uint32_t reserved0;
  uint64_t rsp0;
  uint64_t rsp1;
  uint64_t rsp2;
  uint32_t reserved1;
  uint32_t reserved2;
  uint64_t ist1;
  uint64_t ist2;
  uint64_t ist3;
  uint64_t ist4;
  uint64_t ist5;
  uint64_t ist6;
  uint64_t ist7;
  uint32_t reserved3;
  uint32_t reserved4;
  uint16_t reserved5;
  uint16_t iopb;
}__attribute__((packed));

void initGdt();
void setGdtGate(uint32_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);
void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0);
#ifdef __cplusplus
}
#endif

#endif

