//KEYBOARD.H
#ifndef _KEYBOARD_H
#define _KEYBOARD_H 1

#include <stdint.h>
#include <idt.h>
#include <isr.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

void initKeyboard();

void keyboardHandler(registers_t* regs);

#ifdef __cplusplus
}
#endif

#endif

