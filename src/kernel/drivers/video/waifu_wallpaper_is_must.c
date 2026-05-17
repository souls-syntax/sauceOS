#include <stdint.h>
#include <video.h>
#include "waifu_img.h"
#include "bootinfo.h"
#include <stdio.h>
void writeImage(const uint8_t* src, int img_width, int img_height)
{
    for(int i = 0; i < img_height; i++) {
        for (int j = 0; j < img_width; j++) {
            int src_idx = ( i * img_width + j) * 4;
            uint8_t r = src[src_idx + 0];
            uint8_t g = src[src_idx + 1];
            uint8_t b = src[src_idx + 2];

            uint32_t color = (r << 16) | (g << 8) | b;
            PutPixelColor(j,i, color);
        }
    }
}

void wallpaperInit()
{
    writeImage(waifu_raw, g_framebuffer->width, g_framebuffer->height);
}
