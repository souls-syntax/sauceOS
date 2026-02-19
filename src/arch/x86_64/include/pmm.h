
//bootinfo.h

#ifndef _PMM_H
#define _PMM_H 1

#include <sys/cdefs.h>
#include <stdint.h>
#include <limine.h>

#define EOF (-1)
#define BLOCK_SIZE 4096

#ifdef __cplusplus
extern "C" {
#endif


void PrintMemoryMaps();

#ifdef __cplusplus
}
#endif

#endif



