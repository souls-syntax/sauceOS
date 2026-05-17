#include "bootinfo.h"
#include "paging.h"
#include "pmm.h"

#include <stdatomic.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static PageTable* pml4;

#define PAGE_SIZE 4096

extern struct limine_memmap_response* memmap_info;
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
    return val;
}

PageTable* init_PML4() {
    uint64_t cr3 = (uintptr_t) read_CRT();
    pml4 = (PageTable*) (((cr3 >> 12) << 12) + hhdm_request.response->offset);
    return pml4;
}

extern char kernel_start[];
extern char kernel_end[];

uint64_t kernel_phys_base;
uint8_t index_executable_and_module = 8;
static inline void temp_exec_and_mod_find(){
    atomic_bool flag = 0;
    for(size_t i= 0; i < memmap_info->entry_count; i++) {
        struct limine_memmap_entry* entry = memmap_info->entries[i];
        if (entry->type == LIMINE_MEMMAP_EXECUTABLE_AND_MODULES) {
            index_executable_and_module = i;
            flag = 1;
        }
    }
    if (!flag) {
        kprintf("index_executable_and_module Not found");
    }
    kernel_phys_base = memmap_info->entries[index_executable_and_module]->base;
}

void vmm_init() {

    init_PML4();

    PageTable* new_pml4 = (PageTable*)((uintptr_t)pmm_alloc_frame() 
            + hhdm_request.response->offset);
    memset(new_pml4, 0, PAGE_SIZE);

    for (int i = 256; i < 512; i++) {
        new_pml4->entries[i] = pml4->entries[i];
    }
    pml4 = new_pml4;
    uint64_t phys = (uintptr_t)new_pml4 - hhdm_request.response->offset;
    
    // Setting up frames
    temp_exec_and_mod_find();
    uintptr_t virt = (uintptr_t)kernel_start;
    uintptr_t kern_phys = kernel_phys_base;
    while (virt < (uintptr_t)kernel_end) {
        map_page((void*)virt, (void*)kern_phys, PTE_PRESENT | PTE_WRITABLE);
        virt += PAGE_SIZE;
        kern_phys += PAGE_SIZE;
    }

    __asm__ volatile("mov %0, %%cr3"::"r"(phys):"memory");
}

void set_page_table_entry(PageEntry* entry, uint64_t flag, uintptr_t physical_address )
{
    entry->present = (flag >> 0) & 1;
    entry->read_or_write = (flag >> 1) & 1;
    entry->user_accssable = (flag >> 2) & 1;
    entry->write_through = (flag >> 3) & 1;
    entry->cache_disabled = (flag >> 4) & 1;
    entry->accessed = (flag >> 5) & 1;
    entry->dirty = (flag >> 6) & 1;
    entry->page_attribute_table = (flag >> 7) & 1;
    entry->global = (flag >> 8) & 1;
    entry->avl1 = (flag >> 9) & 0x7;
    entry->physical_address = (physical_address >> 12);
    entry->avl2 = (flag >> 51) & 0x7F;
    entry->protection_key = (flag >> 58) & 0xF;
    entry->execute_disable = (flag >> 62) & 1;

}

static void allocate_entry(PageTable* table, size_t index, uint64_t flags)
{
    void* physical_address = pmm_alloc_frame();
    set_page_table_entry(&(table->entries[index]), flags, (uintptr_t) physical_address );
}

void map_page(void* virtual_address, void* physical_address, uint64_t flags)
{
    // Make sure that both addresses are page-aligned.
    uintptr_t virtual_address_int = (uintptr_t) virtual_address;
    uintptr_t physical_address_int = (uintptr_t) physical_address;

    uint64_t pt_index = (virtual_address_int >> 12) & 0x1FF;
    uint64_t pd_index = (virtual_address_int >> 21) & 0x1FF;
    uint64_t pdpt_index = (virtual_address_int >> 30) & 0x1FF;
    uint64_t pml4_index = (virtual_address_int >> 39) & 0x1FF;


    if (!pml4->entries[pml4_index].present) allocate_entry(pml4, pml4_index, flags);
    // TODO: Map pt pd and pdpt i guess.
    PageTable* page_directory_pointer = (PageTable*) (uint64_t) ((pml4->entries[pml4_index].physical_address << 12) + hhdm_request.response->offset);
    if(! page_directory_pointer->entries[pdpt_index].present) allocate_entry(page_directory_pointer, pdpt_index,flags);

    PageTable* page_directory = (PageTable*) (uint64_t) ((page_directory_pointer->entries[pdpt_index].physical_address << 12) + hhdm_request.response->offset);
    if(! page_directory->entries[pd_index].present) allocate_entry(page_directory, pd_index,flags);
    PageTable* page_table = (PageTable*) (uint64_t) ((page_directory->entries[pd_index].physical_address << 12) + hhdm_request.response->offset);

    set_page_table_entry(&(page_table->entries[pt_index]), flags, physical_address_int);
    flushTLB(virtual_address);
}
