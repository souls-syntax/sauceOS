#include "pmm.h"
#include "bootinfo.h"
#include <stdio.h>
#include <string.h>


extern struct limine_memmap_response* memmap_info;
// static struct limine_memmap_entry* memmap;

// // Constants for `type`
// #define LIMINE_MEMMAP_USABLE                 0
// #define LIMINE_MEMMAP_RESERVED               1
// #define LIMINE_MEMMAP_ACPI_RECLAIMABLE       2
// #define LIMINE_MEMMAP_ACPI_NVS               3
// #define LIMINE_MEMMAP_BAD_MEMORY             4
// #define LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE 5
// #define LIMINE_MEMMAP_EXECUTABLE_AND_MODULES 6
// #define LIMINE_MEMMAP_FRAMEBUFFER            7
// #define LIMINE_MEMMAP_ACPI_TABLES            8
//
// struct limine_memmap_entry {
//     uint64_t base;
//     uint64_t length;
//     uint64_t type;
// };

static const char* GetMemoryMapType(uint64_t type) {
    switch (type) {
        case 0x0:
            return "USABLE RAM";
        case 0x1:
            return "Reserved";
        case 0x2:
            return "ACPI reclaimable";
        case 0x3:
            return "ACPI NVS";
        case 0x4:
            return "Bad memory";
        case 0x5:
            return "Bootloader reclaimable";
        case 0x6:
            return "Executable and Modules";
        case 0x7:
            return "Framefuffer";
        case 0x8:
            return "ACPI tables";
        default:
            return "Unknown spec";
    }
} 

void PrintMemoryMaps() {
    for(size_t i= 0; i < memmap_info->entry_count; i++) {
        struct limine_memmap_entry* entry = memmap_info->entries[i];

        const char* type = GetMemoryMapType(entry->type);
        
        kprintf("    %d  ",i);
        kprintf(type);
        kprintf("\n");
    }
}







