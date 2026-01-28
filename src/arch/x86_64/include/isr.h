//isr.h
#ifndef _ISR_H
#define _ISR_H 1

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  // manually pushed
  uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp;
  uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
  
  // pushed by stub macros
  uint64_t int_no;
  uint64_t err_code;

  // pushed by cpu
  uint64_t rip;
  uint64_t cs;
  uint64_t rflags;
  uint64_t rsp; // Pushed only if cs & 3 != 0 basically not kernel fault
  uint64_t ss; // Pushed only if cs & 3 != 0 basically not kernel fault
}__attribute__((packed)) registers_t;

void exception_handler(registers_t* regs);

void irq_handler(registers_t* regs);

#ifdef __cplusplus
}
#endif

#endif
