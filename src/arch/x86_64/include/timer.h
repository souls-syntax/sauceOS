#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <isr.h>
void timer_handler(registers_t* regs);

uint64_t get_ticks();

void pit_init(uint32_t frequency);

#endif
