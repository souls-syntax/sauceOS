//gdt.c
#include <gdt.h>
#include <string.h>

extern void gdt_flush(uint64_t);
extern void tss_flush();

struct gdt_entry_struct gdt_entries[7];
struct gdt_ptr_struct gdt_ptr;
struct tss_entry_struct tss_entry;
void initGdt() {
  gdt_ptr.limit = (sizeof(struct gdt_entry_struct)*7) -1; // we are subtracting due to some memory offset. Will have to look later
  gdt_ptr.base = (uint64_t)&gdt_entries;
  
  setGdtGate(0,0,0,0,0); // Null segment
  setGdtGate(1,0,0xFFFFF, 0x9A, 0xAF); //Kernel code segment
  setGdtGate(2,0,0xFFFFF, 0x92, 0xCF); //Kernel data segment
  setGdtGate(3,0,0xFFFFF, 0xF2, 0xCF); //User data segment
  setGdtGate(4,0,0xFFFFF, 0xFA, 0xAF); //User code segment
  writeTSS(5,0x10,0x0);
  
  gdt_flush((uint64_t)&gdt_ptr);

  tss_flush();

}

void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0) {
  
  uint64_t base = (uint64_t)&tss_entry;
  uint64_t limit = sizeof(tss_entry);
  
  // Low descriptor
  setGdtGate(num, base, limit, 0xE9, 0x00);
  
  // High descriptor
  gdt_entries[num + 1].limit       = (base >> 32) & 0xFFFF; // bits 32-47
  gdt_entries[num + 1].base_low    = (base >> 48) & 0xFFFF; // bits 48-63
  gdt_entries[num + 1].base_middle = 0;
  gdt_entries[num + 1].access      = 0;
  gdt_entries[num + 1].flags       = 0;
  gdt_entries[num + 1].base_high   = 0;
  
  // Init the struct
  memset(&tss_entry,0,sizeof(tss_entry));
  tss_entry.rsp0 = esp0;
  tss_entry.iopb = sizeof(tss_entry);

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
