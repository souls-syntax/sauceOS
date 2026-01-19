//video.h
#ifndef _VIDEO_H
#define _VIDEO_H 1

#include <sys/cdefs.h>
#include <stdint.h>
#include <limine.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

void PutPixel(int x, int y);

extern struct limine_framebuffer *g_framebuffer;

void video_init(void);

void framebuffer_scroll(void);

#ifdef __cplusplus
}
#endif

#endif
