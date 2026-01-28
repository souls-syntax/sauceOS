BITS 64
extern exception_handler


; macro for exceptions that already push an error code (like page fault)
%macro isr_err_stub 1
isr_stub_%+%1:
  ; The CPU has already push error code, rip , cs, rflags, rsp, ss
  ; we push the interrupt number so the C code knows which interrupt this is.
  push %1 ; push the interrupt number
  jmp isr_common_stub
%endmacro

; Macro for exceptions that do not push the error code like divide by zero
%macro isr_no_err_stub 1
isr_stub_%+%1:
  ; The CPU pusherd RIP, CS.. but no Error Code.
  ; We push a "dummy" error code (0) to keep the stack structure identical
  push 0

  ;Push the interrupt number
  push %1
  jmp isr_common_stub
%endmacro



; The common stub for both type of error

isr_common_stub:
  ; stack structure [ SS, RSP, RFLAGS, CS, RIP, ErrorCode, IntNo ]
  
  ; 1. save all to general purpose registers
  ; We push them in reverse order of the registers_t struct we will make later.
  push r15
  push r14
  push r13
  push r12
  push r11
  push r10
  push r9
  push r8
  push rbp
  push rdi
  push rsi
  push rdx
  push rcx
  push rbx
  push rax
  
  ;2 Prepare the argument for C
  ; We want to pass a pointer to the stack so C can read our saved regs.

  mov rdi, rsp

  ;3
  call exception_handler

  ;4 restore registers.
  pop rax
  pop rbx
  pop rcx
  pop rdx
  pop rsi
  pop rdi
  pop rbp
  pop r8
  pop r9
  pop r10
  pop r11
  pop r12
  pop r13
  pop r14
  pop r15
  

  ;5 cleanup the erro and Int No
  ; We pushed extra 64-bit values at the start
  add rsp, 16 ; Move the stack pointer down 16 bytes( 2 * 8 )

  ; 6. return from interrupt
  iretq ; manual says in 64 bit use iretq

; The stub table
; creates an array of pointers to the stubs above

; Macros for each of the interrupts
; Some have error codes, some don't. This list is standard x86.

isr_no_err_stub 0  ; Divide by Zero
isr_no_err_stub 1  ; Debug
isr_no_err_stub 2  ; NMI
isr_no_err_stub 3  ; Breakpoint
isr_no_err_stub 4  ; Overflow
isr_no_err_stub 5  ; Bound Range
isr_no_err_stub 6  ; Invalid Opcode
isr_no_err_stub 7  ; Device Not Available
isr_err_stub    8  ; Double Fault (HAS ERROR CODE)
isr_no_err_stub 9  ; Coprocessor Segment Overrun
isr_err_stub    10 ; Invalid TSS (HAS ERROR CODE)
isr_err_stub    11 ; Segment Not Present (HAS ERROR CODE)
isr_err_stub    12 ; Stack-Segment Fault (HAS ERROR CODE)
isr_err_stub    13 ; General Protection Fault (HAS ERROR CODE)
isr_err_stub    14 ; Page Fault (HAS ERROR CODE)
isr_no_err_stub 15 ; Reserved
isr_no_err_stub 16 ; x87 FPU Error
isr_err_stub    17 ; Alignment Check (HAS ERROR CODE)
isr_no_err_stub 18 ; Machine Check
isr_no_err_stub 19 ; SIMD Exception
isr_no_err_stub 20 ; Virtualization
isr_no_err_stub 21 ; Reserved...
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30 ; Security Exception (HAS ERROR CODE)
isr_no_err_stub 31



global isr_stub_table
isr_stub_table:
%assign i 0
%rep 32
  dq isr_stub_%+i ; 'dq' is critical for 64-bit pointers
%assign i i+1
%endrep



