//gdt.c
#include <gdt.h>

extern void gdt_flush(struct gdt_ptr_struct*);

struct gdt_entry_struct gdt_entries[5];
struct gdt_ptr_struct gdt_ptr;

void initGdt() {
  gdt_ptr.limit = (sizeof(struct gdt_entry_struct)*5) -1; // we are subtracting due to some memory offset. Will have to look later
  gdt_ptr.base = (uint64_t)&gdt_entries;
  
  setGdtGate(0,0,0,0,0); // Null segment
  setGdtGate(1,0,0xFFFFF, 0x9A, 0xAF); //Kernel code segment
  setGdtGate(2,0,0xFFFFF, 0x92, 0xCF); //Kernel data segment
  setGdtGate(3,0,0xFFFFF, 0xF2, 0xCF); //User data segment
  setGdtGate(4,0,0xFFFFF, 0xFA, 0xAF); //User code segment
  
  gdt_flush(&gdt_ptr);

}

void setGdtGate(uint32_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran) {
  
  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;

  gdt_entries[num].limit =  (limit & 0xFFFF);
  gdt_entries[num].flags =  (limit >> 16) & 0x0F;
  gdt_entries[num].flags |= (gran & 0xF0);

  gdt_entries[num].access = access;

}
