#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>
#include <stdint.h>
#include <limine.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

void PutPixel(struct limine_framebuffer *fb, int x, int y, uint32_t color);

#ifdef __cplusplus
}
#endif

#endif
