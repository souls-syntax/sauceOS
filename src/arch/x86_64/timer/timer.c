#include <timer.h>
#include <io.h>
#include <isr.h>
#include <stdint.h>


static uint64_t ticks = 0;

void timer_handler(registers_t* regs) {
    ticks++;
}

uint64_t get_ticks() {
    return ticks;
}

void pit_init(uint32_t frequency) {
    uint32_t divisor = 1193180 / frequency;
    outPortB(0x43, 0x36);
    outPortB(0x40, divisor & 0xFF);
    outPortB(0x40, (divisor >> 8) & 0xFF);
}
