;gdt.s
global gdt_flush

global tss_flush

; In long mode we can't do far jump. Remember before trying to make it "efficient".
gdt_flush:
  ;Reload CS registers
  LGDT [RDI]
  PUSH 0x08
  LEA RAX, [rel .reload_CS]
  PUSH RAX
  RETFQ
.reload_CS:
  ;reload data segments registers
  MOV AX, 0x10
  MOV DS, AX
  MOV ES, AX
  MOV FS, AX
  MOV GS, AX
  MOV SS, AX
  RET


tss_flush:
  mov ax, 0x28      ; Index 5 * 8 = 40 (0x28)
  ltr ax            ; Load Task Register (Hardware checks GDT entry 5)
  ret
