#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stddef.h>
typedef struct PageEntry {
    uint64_t present: 1;
    uint64_t read_or_write: 1;
    uint64_t user_accssable: 1;
    uint64_t write_through: 1;
    uint64_t cache_disabled: 1;
    uint64_t accessed: 1;
    uint64_t dirty: 1;
    uint64_t page_attribute_table: 1;
    uint64_t global: 1;
    uint64_t avl1: 3;
    uint64_t physical_address: 40;
    uint64_t avl2: 7;
    uint64_t protection_key: 4;
    uint64_t execute_disable: 1;
} PageEntry;

typedef struct PageTable {
    PageEntry entries[512];
} PageTable;

#define PTE_PRESENT       (1ULL << 0)
#define PTE_WRITABLE      (1ULL << 1)
#define PTE_USER          (1ULL << 2)
#define PTE_WRITE_THROUGH (1ULL << 3)
#define PTE_CACHE_DISABLE (1ULL << 4)
#define PTE_ACCESSED      (1ULL << 5)
#define PTE_DIRTY         (1ULL << 6)
#define PTE_HUGE_PAGE     (1ULL << 7)
#define PTE_GLOBAL        (1ULL << 8)
#define PTE_NO_EXECUTE    (1ULL << 63)



PageTable* init_PML4();


void set_page_table_entry(PageEntry* entry, uint64_t flag, uintptr_t physical_address );

void man_page(void* virtual_address, void* physical_address, uint64_t flags);

#endif 
