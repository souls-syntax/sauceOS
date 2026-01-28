//kprintf.c
#include <stdio.h>
#include <limine.h>
#include <stdarg.h>
#include <stddef.h>

void kputs(const char *str) {
    while(*str) {
        kputc(*str);
        str++;
    }
}

void kprint_hex(uint64_t n) {
    kputs("0x");
    if (n == 0) {
        kputs("0");
        return;
    }

    char buffer[20]; // Big enough for 64-bit int (16 chars)
    int i = 0;
    
    // Process nibbles (4 bits)
    while (n > 0) {
        int nibble = n % 16;
        if (nibble < 10) {
            buffer[i++] = nibble + '0';
        } else {
            buffer[i++] = nibble - 10 + 'A';
        }
        n /= 16;
    }

    // Print in reverse
    while (i > 0) {
        kputc(buffer[--i]);
    }
}

void kprint_dec(int64_t n) {
    if (n == 0) {
        kputc('0');
        return;
    }

    if (n < 0) {
        kputc('-');
        n = -n;
    }

    char buffer[20];
    int i = 0;

    while (n > 0) {
        buffer[i++] = (n % 10) + '0';
        n /= 10;
    }

    while (i > 0) {
        kputc(buffer[--i]);
    }
}


void kprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++; // Move past '%'
            
            switch (*fmt) {
                case 's': { // String
                    const char* s = va_arg(args, const char*);
                    if (!s) s = "(null)";
                    kputs(s);
                    break;
                }
                case 'd': { // Decimal (Signed)
                    int64_t d = va_arg(args, int64_t); // Use int64 for safety
                    kprint_dec(d);
                    break;
                }
                case 'u': { // Unsigned Decimal (Treat as same for simple kprintf)
                    uint64_t u = va_arg(args, uint64_t);
                    kprint_dec((int64_t)u); 
                    break;
                }
                case 'x':   // Hex (Lower case)
                case 'X':   // Hex (Upper case - we treat same for now)
                case 'p': { // Pointer
                    uint64_t x = va_arg(args, uint64_t);
                    kprint_hex(x);
                    break;
                }
                case 'c': { // Char
                    // Note: char is promoted to int in va_arg
                    char c = (char)va_arg(args, int); 
                    kputc(c);
                    break;
                }
                case '%': { // Escaped '%'
                    kputc('%');
                    break;
                }
                default: {
                    // Unknown specifier, print it literally
                    kputc('%');
                    kputc(*fmt);
                    break;
                }
            }
        } else {
            kputc(*fmt);
        }
        fmt++;
    }

    va_end(args);
}
