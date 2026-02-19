// bootinfo.c
#include <limine.h>
#include "bootinfo.h"
#include <stddef.h>


__attribute__((used, section(".limine_requests_start")))
volatile uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests")))
volatile uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(4);

__attribute__((used, section(".limine_requests")))
volatile struct limine_framebuffer_request framebuffer_request = {
  .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
  .revision = 0
};

__attribute__((used, section(".limine_requests")))
volatile struct limine_memmap_request memmap_request = {
  .id = LIMINE_MEMMAP_REQUEST_ID,
  .revision = 0
};

__attribute__((used, section(".limine_requests_end")))
volatile uint64_t limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

//=======================================================================================

struct limine_memmap_response* memmap_info;

void bootinfoInit() {
    if (memmap_request.response) {
        memmap_info = memmap_request.response;
    }
}

