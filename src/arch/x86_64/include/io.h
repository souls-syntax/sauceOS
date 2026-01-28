//io.h
#ifndef _IO_H
#define _IO_H 1

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void outPortB(uint16_t port, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif
