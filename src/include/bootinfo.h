//bootinfo.h

#ifndef _BOOTINFO_H
#define _BOOTINFO_H 1

#include <sys/cdefs.h>
#include <stdint.h>
#include <limine.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

extern struct limine_framebuffer *g_framebuffer;
extern struct limine_memmap_response* memmap_info;

extern volatile uint64_t limine_base_revision[];

extern volatile struct limine_framebuffer_request framebuffer_request;

void bootinfoInit();

#ifdef __cplusplus
}
#endif

#endif
