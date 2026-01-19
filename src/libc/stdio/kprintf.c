//kprintf.c
#include <stdio.h>
#include <limine.h>

void kprintf(const char *str) {
  while(*str) {
    kputc(*str);
    str++;
  }
}

