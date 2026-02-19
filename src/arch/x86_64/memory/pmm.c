#include "pmm.h"
#include "bootinfo.h"
#include <stdio.h>
#include <string.h>
#include "bootinfo.h"

extern struct limine_memmap_response* memmap_info;
static struct limine_memmap_entry* memmap;
extern volatile struct limine_hhdm_request hhdm_request;

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

void SetMemoryMap(uint8_t section) {
    memmap = memmap_info->entries[section];
    if (hhdm_request.response != NULL) {
        uint64_t virtual_base = memmap->base + hhdm_request.response->offset;
        memset((void*)virtual_base,0,memmap->length);
        kprintf("Ready for allocation!\n");
    }
}

void* GetMemoryMapbase() {
    return (void*) memmap->base;
}

uint64_t GetMemoryMapLength() {
    return memmap->length;
}

static void* BMalloc(uint64_t* base, size_t length, size_t size) {
    if (length <=LOWEST_BLOCK_SIZE) {
        if (size + 1 <= length && *((uint64_t*) base) == 0) {
            *base = size;
            memset(base+1, 0, sizeof(void*) * size);
        } else {
            return NULL;
        }
    }

    size_t half = length >> 1;
    if (size + 1 <= half && *((uint64_t*) base) == 0) {
        *base = size;
        memset(base+1, 0, sizeof(void*) * size);
        return (void*) (base+1);
    } else if (half > size) {
        void* buddy = BMalloc(base, half, size);
        // If allocation was not possible search right
        if (buddy == NULL) {
            buddy = BMalloc(base + half, half, size);
        }
        return buddy;
    }

    return NULL;
}

void* KMalloc(size_t size) {
    if (hhdm_request.response == NULL) {
        return NULL;
    }
    
    uint64_t hhdm_offset = hhdm_request.response->offset;
    uint64_t virtual_base = memmap->base + hhdm_offset;
    

    return BMalloc((uint64_t*)virtual_base, memmap->length, size);
}

void KFree(void* base) {
    uint64_t size = *(((uint64_t*) base) - 1);
    memset(base, 0, size);
}
