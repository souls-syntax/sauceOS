#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>
#include <stdint.h>
#include <limine.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

void kputc(char c);

void kprintf(const char *str);

#ifdef __cplusplus
}
#endif

#endif
