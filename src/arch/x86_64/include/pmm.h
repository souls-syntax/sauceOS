
//bootinfo.h

#ifndef _PMM_H
#define _PMM_H 1

#include <sys/cdefs.h>
#include <stdint.h>
#include <stddef.h>
#include <limine.h>

#define EOF (-1)
#define LOWEST_BLOCK_SIZE 4096

#ifdef __cplusplus
extern "C" {
#endif


void PrintMemoryMaps();

void SetMemoryMap(uint8_t section);

void* GetMemoryMapbase();

void* KMalloc(size_t size);
uint64_t GetMemoryMapLength();

#ifdef __cplusplus
}
#endif

#endif



