
/*
 * Port I/O helpers
 *
 * x86 port addresses are always 16-bit.
 * Data width depends on the instruction variant:
 *  - outb: 8-bit value
 *  - outw: 16-bit value
 *  - outl: 32-bit value
 *
 * Note:
 * IRQs above 31 are currently masked.
 * They will be unmasked once IRQ handlers are installed.
 */

```C
void outb(uint16_t port, uint8_t value);
void outw(uint16_t port, uint16_t value);
void outl(uint16_t port, uint32_t value);
```


NOTE:
Kernel-mode interrupts do not have a real SS/RSP frame.
We synthesize one here to unify the C handler ABI.
This is intentional and must be revisited if:
- user/kernel GS is used
- stack walking is added
- SMP is enabled

