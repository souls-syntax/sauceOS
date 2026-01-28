//isr.c
#include <isr.h>
#include <idt.h>
#include <stdio.h>

const char* exception_messages[] = {
   "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Security Exception",
    "Reserved"
};


void exception_handler(registers_t* regs) {
  __asm__ volatile ("cli");

  kprintf("\n\n");
  kprintf("---------------------------------------------------------------------------------------\n");

  if (regs->int_no < 32) {
    kprintf("KERNEL PANIC: %s\n", exception_messages[regs->int_no]);
  } else {
    kprintf("KERNEL PANIC: Unknown Exception %d\n", regs->int_no);
  }

  kprintf("-----------------------------------------------------------------------------------------\n");

  kprintf("RIP: %x   CS: %x   RFLAGS: %x\n", regs->rip, regs->cs, regs->rflags);
  kprintf("RAX: %x   RBX: %x   RCX: %x\n", regs->rax, regs->rbx, regs->rcx);
  kprintf("RDX: %x   RSI: %x   RDI: %x\n", regs->rdx, regs->rsi, regs->rdi);
  kprintf("RBP: %x   RSP: %x\n", regs->rbp, regs->rsp);
  kprintf("Error Code: %x\n", regs->err_code);

  kprintf("------------------------------------------------------------------------------------------\n");
  kprintf("System halted\n");

  for(;;) {
    __asm__ volatile ("hlt");
  }
}
