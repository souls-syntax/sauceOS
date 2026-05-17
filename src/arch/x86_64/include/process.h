#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include <paging.h>

typedef enum {

    RUNNING,
    READY,
    BLOCKED,
    DEAD

} state_t;


typedef struct pcb{
    //Identity
    uint64_t pid;
    char name[32];

    //CPU state
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp;
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;

    uint64_t rip;
    uint64_t rflags;
    uint64_t cs;
    uint64_t ss;

    // Memory state
    PageTable* pml4;
    uint64_t stack_top;
    
    state_t current_state;

    uint64_t kernel_stack_top;
} pcb_t ;

#endif
