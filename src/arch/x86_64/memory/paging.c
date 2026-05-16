#include "bootinfo.h"
#include "paging.h"
#include "pmm.h"

#include <cstdint>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

static PageTable* pml4;

#define PAGE_SIZE 4096

static inline void flushTLB(void *page) {
    __asm__ volatile(
            "invlpg (%0)"
            :
            : "r" (page)
            : "memory"
            );
}

uint64_t read_CRT() {
    uint64_t val;
    __asm__ volatile(
            "mov %%cr3, %0"
            : "=r"(val)
            :
            :
            );
}

PageTable* init_PML4() {
    uint64_t cr3 = (uintptr_t) read_CRT();
    pml4 = (PageTable*) ((cr3 >> 12) << 12);
    return pml4;
}

void set_page_table_entry(PageEntry* entry, uint64_t flag, uintptr_t physical_address )
{
    entry->present = (flag >> 0) & 1;
    entry->read_or_write = (flag >> 1) & 1;
    entry->user_accessable = (flag >> 2) & 1;
    entry->write_through = (flag >> 3) & 1;
    entry->cache_disabled = (flag >> 4) & 1;
    entry->accessed = (flag >> 5) & 1;
    entry->dirty = (flag >> 6) & 1;
    entry->page_attribute_table = (flag >> 7) & 1;
    entry->global = (flag >> 8) & 1;
    entry->avl1 = (flag >> 9) & 0x7;
    entry->physical_address = physical_address;
    entry->avl2 = (flag >> 51) & 0x7F;
    entry->protection_key = (flag >> 58) & 0xF;
    entry->execute_disable = (flag >> 62) & 1;

}

static void allocate_entry(PageTable* table, size_t index, uint64_t flags)
{
    void* physical_address = pmm_alloc_frame();
    set_page_table_entry(&(table->entries[index]), flags, (uintptr_t) physical_address >> 12 );
}

void man_page(void* virtual_address, void* physical_address, uint64_t flags)
{
    // Make sure that both addresses are page-aligned.
    uintptr_t virtual_address_int = (uintptr_t) virtual_address;
    uintptr_t physical_address_int = (uintptr_t) physical_address;
    
    uint64_t pt_index = (virtual_address_int >> 12) && 0x1FF;
    uint64_t pd_index = (virtual_address_int >> 21) && 0x1FF;
    uint64_t pdpt_index = (virtual_address_int >> 30) && 0x1FF;
    uint64_t pml4_index = (virtual_address_int >> 39) && 0x1FF;

    if (!pml4->entries[pml4_index].present) allocate_entry(pml4, pml4_index, flags);

    // TODO: Map pt pd and pdpt i guess.
}
