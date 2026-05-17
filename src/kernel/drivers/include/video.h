//video.h
#ifndef _VIDEO_H
#define _VIDEO_H 1

#include <sys/cdefs.h>
#include <stdint.h>
#include <limine.h>
#include <stdint.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

void PutPixel(int x, int y);

void PutPixelColor(int x, int y, uint32_t color);

void video_init(void);

void framebuffer_scroll(void);

void wallpaperInit();
#ifdef __cplusplus
}
#endif

#endif
