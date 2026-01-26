# GDT
Used by intel x86 processor.
Defines the characteristics of various memory areas.

Base := Where the segment begins
Divided into three values.

Limit := is a 20bit values
Max size of the page

### Access byte
P: Present bit. Allows an entry to refer to a valid segment. Must be set (1) for any valid segment.

DPL: Descriptor privilege level field. Contains the CPU Privilege level of the segment. 0 = highest privilege (kernel), 3 = lowest privilege (user applications).

S: Descriptor type bit. If clear (0) the descriptor defines a system segment (eg. a Task State Segment). If set (1) it defines a code or data segment.

E: Executable bit. If clear (0) the descriptor defines a data segment. If set (1) it defines a code segment which can be executed from.

DC: Direction bit/Conforming bit.
We are setting it up to 0 for growing up

RW: Readable bit/Writable bit.

A: Accessed bit.
To check if nonconsensual touch was done to segment

### Flags

G: Granularity flag. set (1), the Limit is in 4 KiB blocks (page granularity).

DB: Size Flags

L: Long-mode code flag.set (1), the descriptor defines a 64-bit code segment.

---
```C
gdt_ptr.limit = (sizeof(struct gdt_entry_struct)*5) -1; // we are subtracting due to some memory offset. Will have to look later
```

