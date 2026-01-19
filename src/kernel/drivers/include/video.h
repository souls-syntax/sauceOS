#ifndef _VIDEO_H
#define _VIDEO_H 1

#include <sys/cdefs.h>
#include <stdint.h>
#include <limine.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

void PutPixel(struct limine_framebuffer *fb, int x, int y, uint32_t color);

void kputc(struct limine_framebuffer *fb, char c, uint32_t color);

void kprint(struct limine_framebuffer *fb, const char *str, uint32_t color);

#ifdef __cplusplus
}
#endif

#endif
